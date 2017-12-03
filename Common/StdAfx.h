/*! @file stdafx.h

*  @brief 
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



#define __STDC_LIMIT_MACROS
#include <stdint.h>

#include <stddef.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#include <stdio.h>
#include <stdarg.h>

#if defined(_WINDOWS) || defined(_WIN32) || defined(__WIN32__)

// Windows header files
#include <windows.h>

// Includes required for Visual Studio 2005 (not required for Visual Studio 2003)
#include <tchar.h>

#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#else

#include <libgen.h>
#include <pthread.h>
#include <semaphore.h>

#endif

// The encoder and thread pools use the vector data type from the standard template library
#include <vector>

// The encoder job queue uses a deque from the standard template library
#include <deque>

// The message queue for the worker threads uses a queue from the standard template library
#include <queue>

// TODO: reference additional headers your program requires here
