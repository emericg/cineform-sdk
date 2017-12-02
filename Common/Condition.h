/*! @file Condition.h

*  @brief Threading tools
*
*  @version 1.0.0
*
*  (C) Copyright 2017 GoPro Inc (http://gopro.com/).
*
*  Licensed under either:
*  - Apache License, Version 2.0, http://www.apache.org/licenses/LICENSE-2.0  
*  - MIT license, http://opensource.org/licenses/MIT
*  at your option.
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*/

#pragma once

#ifndef _MSVC_VER
#include "pthread.h"
#endif
#include "Lock.h"

// Control use of the new Windows condition variable primitives
//#define _CONDITION_VARIABLE

/*!
	@Brief Use a condition variable to wait until some predicate is true
*/
class ConditionVariable
{
	static const unsigned long DEFAULT_TIMEOUT = 100;

public:
#ifdef _CONDITION_VARIABLE
	ConditionVariable()
	{
		InitializeConditionVariable(&condition);
	}
#elif defined(_WINDOWS) || defined(_WIN32) || defined(__WIN32__)
	ConditionVariable() :
		handle(NULL)
	{
		// Use an automatic reset event to implement a condition variable
		handle = CreateEvent(NULL, FALSE, FALSE, NULL);
		assert(handle != NULL);
	}

	~ConditionVariable()
	{
		CloseHandle(handle);
		handle = NULL;
	}
#else
	ConditionVariable() 
	{
		pthread_cond_init(&cond, NULL);
	}
#endif

	bool Wait(CSimpleLock &mutex, unsigned long timeout = DEFAULT_TIMEOUT)
	{
#ifdef _CONDITION_VARIABLE
		return SleepConditionVariableCS(&condition, &mutex.lock, timeout);
#elif defined(_WINDOWS) || defined(_WIN32) || defined(__WIN32__)
		mutex.Unlock();
		DWORD result = WaitForSingleObject(handle, timeout);
		mutex.Lock();
		return (result == WAIT_OBJECT_0);
#else
		return pthread_cond_wait(&cond, &mutex.lock);
#endif
	}

	void Wake()
	{
#ifdef _CONDITION_VARIABLE
		WakeConditionVariable(&condition);
#elif defined(_WINDOWS) || defined(_WIN32) || defined(__WIN32__)
		SetEvent(handle);
#else
		pthread_cond_signal(&cond);
#endif
	}

private:

#ifdef _CONDITION_VARIABLE
	CONDITION_VARIABLE condition;
#elif defined(_WINDOWS) || defined(_WIN32) || defined(__WIN32__)
	HANDLE handle;
#else
	pthread_cond_t cond;
#endif

};
