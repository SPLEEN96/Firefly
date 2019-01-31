#pragma once

#include "Firefly/Logger.h"

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;

typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t  uint8;

#define FFLY_ASSERT_ENABLED
#ifdef FFLY_ASSERT_ENABLED
#define FFLY_ASSERT(x, ...)                                                    \
    {                                                                          \
        if (!x) {                                                              \
            FFLY_LOG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);         \
            __builtin_trap();                                                  \
        }                                                                      \
    }
#else
#define FFLY_ASSERT(x, ...)                                                    \
    { x; }
#endif

#define BIT(x) (1 << x)