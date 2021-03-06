/**
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef _SVCBATCH_H_INCLUDED_
#define _SVCBATCH_H_INCLUDED_

/**
 * Disable or reduce the frequency of...
 *   C4100: unreferenced formal parameter
 *   C4702: unreachable code
 *   C4244: int to char/short - precision loss
 */
#if defined(_MSC_VER)
# pragma warning(disable: 4100 4244 4702)
#endif

#define SVCBATCH_NAME           "SvcBatch"
#define SVCBATCH_SVCNAME        "SvcBatch Service"
/**
 * Version info
 */
#define SVCBATCH_MAJOR_VERSION  0
#define SVCBATCH_MINOR_VERSION  9
#define SVCBATCH_PATCH_VERSION  6

/**
 * Set to zero for non dev versions
 */
#define SVCBATCH_ISDEV_VERSION  1

/**
 * ABI version info
 *
 * 20201201   (0.9.1-dev)       Initial version
 * 20201205   (0.9.3-dev)       Add parent signaling support
 * 20201207   (0.9.4-dev)       Drop parent signaling support
 * 20201209   (0.9.5-dev)       Increase maxlog to SvcBatch.log.4
 *                              Allow to specify log directory
 *
 */
#define SVCBATCH_VERSION_ABI    "20201209"


/**
 * Maximum number of SvcBatch.log.N files
 */
#define SVCBATCH_MAX_LOGS       4

#define BBUFSIZ                 512
#define SBUFSIZ                 1024
#define MBUFSIZ                 2048
#define HBUFSIZ                 8192

/**
 * Custom SCM control code that
 * sends CTRL_BREAK_EVENT to the child processes.
 *
 * This option has to be enabled on install
 * by adding /b switch.
 *
 * eg. C:\>sc control SvcBatchServiceName 233
 * will cause java.exe to dump thread stack
 * if running inside batch file.
 *
 * Programs that do not handle CTRL_BREAK_EVENT
 * will cause SvcBatch to fail or hang
 */
#define SVCBATCH_CTRL_BREAK     233
/**
 * This signal will rotate log files
 * in the same way as on service startup
 *
 * eg. C:\>sc control SvcBatchServiceName 234
 *
 * Check documentation for more details
 */
#define SVCBATCH_CTRL_ROTATE    234

#define SVCBATCH_START_HINT     5000
#define SVCBATCH_STOP_HINT      20000
#define SVCBATCH_STOP_WAIT      30000
#define SVCBATCH_PENDING_WAIT   1000

#define MS_IN_DAY               86400000
#define MS_IN_SECOND            1000
#define MS_IN_MINUTE            60000
#define MS_IN_HOUR              3600000

/**
 * Helper macros
 */
#define IS_INVALID_HANDLE(_h)   (((_h) == 0) || ((_h) == INVALID_HANDLE_VALUE))
#define IS_VALID_HANDLE(_h)     (((_h) != 0) && ((_h) != INVALID_HANDLE_VALUE))
#define IS_EMPTY_WCS(_s)        ((_s == 0)   || (*(_s) == L'\0'))
#define DSIZEOF(_s)             ((DWORD)sizeof(_s))

#define SAFE_CLOSE_HANDLE(_h)                                       \
    if (((_h) != 0) && ((_h) != INVALID_HANDLE_VALUE)) {            \
        CloseHandle((_h));                                          \
        (_h) = INVALID_HANDLE_VALUE;                                \
    } else (void)0

#define XENDTHREAD(_r)          ExitThread(_r); return (_r)
#define WAIT_OBJECT_1          (WAIT_OBJECT_0 + 1)
#define WAIT_OBJECT_2          (WAIT_OBJECT_0 + 2)


/**
 * Helper macros for properly quoting a value as a
 * string in the C preprocessor
 */
#define CPP_TOSTR_HELPER(n)     #n
#define CPP_TOSTR(n)            CPP_TOSTR_HELPER(n)

#define CPP_WIDEN_HELPER(n)     L ## n
#define CPP_WIDEN(n)            CPP_WIDEN_HELPER(n)


/**
 * Construct build stamp
 */
#if defined(_MSC_VER)
# define SVCBATCH_BUILD_CC      "msc " CPP_TOSTR(_MSC_FULL_VER) "."     \
                                CPP_TOSTR(_MSC_BUILD)
#elif defined(__GNUC__)
# define SVCBATCH_BUILD_CC      "gcc " CPP_TOSTR(__GNUC__) "."          \
                                CPP_TOSTR(__GNUC_MINOR__) "."           \
                                CPP_TOSTR(__GNUC_PATCHLEVEL__)
#else
# define SVCBATCH_BUILD_CC      "unknown"
#endif
#define SVCBATCH_BUILD_STAMP    "(" __DATE__ " " __TIME__ " " SVCBATCH_BUILD_CC ")"

#if SVCBATCH_ISDEV_VERSION
# define SVCBATCH_VERSION_SFX   "-dev"
#else
# define SVCBATCH_VERSION_SFX   ""
#endif

/**
 * Macro for .rc files using numeric csv representation
 */
#define SVCBATCH_VERSION_CSV    SVCBATCH_MAJOR_VERSION,                 \
                                SVCBATCH_MINOR_VERSION,                 \
                                SVCBATCH_PATCH_VERSION

#define SVCBATCH_VERSION_STR \
                                CPP_TOSTR(SVCBATCH_MAJOR_VERSION) "."   \
                                CPP_TOSTR(SVCBATCH_MINOR_VERSION) "."   \
                                CPP_TOSTR(SVCBATCH_PATCH_VERSION)       \
                                SVCBATCH_VERSION_SFX

#define SVCBATCH_DESCRIPTION \
    "Run batch files as Windows Services"

#define SVCBATCH_COPYRIGHT \
    "Copyright (c) 1964-2020 The Acme Corporation or its "              \
    "licensors, as applicable."

#define SVCBATCH_COMPANY_NAME "Acme Corporation"

#define SVCBATCH_LICENSE \
    "Licensed under the Apache License, Version 2.0 (the ""License""); "        \
    "you may not use this file except in compliance with the License. "         \
    "You may obtain a copy of the License at\r\n\r\n"                           \
    "http://www.apache.org/licenses/LICENSE-2.0\r\n\r\n"                        \
    "Unless required by applicable law or agreed to in writing, software "      \
    "distributed under the License is distributed on an ""AS IS"" BASIS, "      \
    "WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. " \
    "See the License for the specific language governing permissions and "      \
    "limitations under the License."


#endif /* _SVCBATCH_H_INCLUDED_ */
