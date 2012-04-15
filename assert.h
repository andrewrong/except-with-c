#ifndef ASSERT_INCLUDE
#define ASSERT_INCLUDE
#undef assert

#ifdef NDEBUG
#define assert(e) (void(0))
#else
#include "except.h"
#define assert(e) ((void)((e) || (RAISE(Assert_Failed),0)))
#endif

#endif
