#ifndef zz_h
#define zz_h

// Created by jmpews on 2017/5/3.
//
#define PROGRAM_NAME "zz"
#define PROGRAM_VER "1.0.0"
#define PROGRAM_AUTHOR "jmpews@gmail.com"

#include <stdint.h>


// --- custom type ---

// 1. zpointer and zaddr is different

#define DEBUG_MODE 0

#ifndef zz_type
#define zz_type

typedef void *zpointer;
typedef unsigned long zsize;
typedef unsigned long zaddr;
typedef unsigned long zuint;
typedef long zint;
typedef unsigned char zbyte;

#endif

#if defined(false)
#else
#define false 0
#define true 1
#endif

// --- log configuration ---

#define GLOBAL_DEBUG 0
#define GLOBAL_INFO 0
#define SYSLOG 0
#define COLOR_LOG 0

#if (COLOR_LOG)
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"
#else
#define RED ""
#define GRN ""
#define YEL ""
#define BLU ""
#define MAG ""
#define CYN ""
#define WHT ""
#define RESET ""
#endif

#include <stdio.h>
#include <sys/syslog.h>

// Important!!!
// STDERR before STDOUT, because sync

#if (SYSLOG)
#define Xinfo(fmt, ...)                                                        \
  do {                                                                         \
    if (GLOBAL_INFO)                                                           \
      syslog(LOG_WARNING, RESET fmt, __VA_ARGS__);                             \
  } while (0)
#define Sinfo(MSG) Xinfo("%s", MSG)
#define Xdebug(fmt, ...)                                                       \
  do {                                                                         \
    if (GLOBAL_DEBUG)                                                          \
      syslog(LOG_WARNING, RESET fmt, __VA_ARGS__);                               \
  } while (0)
#define Sdebug(MSG) Xdebug("%s", MSG)
#define Xerror(fmt, ...)                                                       \
  do {                                                                         \
    syslog(LOG_DEBUG,                                                          \
           RED "[!] "                                                          \
               "%s:%d:%s(): " fmt RESET "\n",                                  \
           __FILE__, __LINE__, __func__, __VA_ARGS__);                         \
  } while (0)

#define Serror(MSG) Xerror("%s", MSG)
#else
#define Xinfo(fmt, ...)                                                        \
  do {                                                                         \
    if (GLOBAL_INFO)                                                           \
      fprintf(stdout, RESET fmt "\n", __VA_ARGS__);                            \
  } while (0)
#define Sinfo(MSG) Xinfo("%s", MSG)

#define Xdebug(fmt, ...)                                                       \
  do {                                                                         \
    if (GLOBAL_DEBUG)                                                          \
      fprintf(stdout, RESET fmt "\n", __VA_ARGS__);                            \
  } while (0)
#define Sdebug(MSG) Xdebug("%s", MSG)
#define Xerror(fmt, ...)                                                       \
  do {                                                                         \
    fprintf(stderr,                                                            \
            RED "[!] "                                                         \
                "%s:%d:%s(): " fmt RESET "\n",                                 \
            __FILE__, __LINE__, __func__, __VA_ARGS__);                        \
  } while (0)

#define Serror(MSG) Xerror("%s", MSG)
#endif

//#define xinfo(str) printf(GRN "[*] " "%s" "\n" RESET, str)
//#define xinfo(X) {printf(RESET "[*] "); X; printf("\n");}
// #define Xinfo(fmt, ...) \
//         do { fprintf(stderr, RESET "[*] " fmt "\n", \
//         __VA_ARGS__); } while (0)
// #define Sinfo(MSG) Xinfo("%s", MSG)

#endif