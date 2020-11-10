#ifndef __COMMON_H__
#define __COMMON_H__
#include <stdint.h>
#include <limits.h>
#include <signal.h>



#ifdef NULL
#undef NULL
#endif
#define NULL ((void*)0)
#define bool _Bool
#define true 1
#define false 0
#define assert(x) \
	do{ \
		if (!(x)){ \
			printf("%s: Line %u (%s): %s: Assertion Failed\n",__FILE__,__LINE__,__func__,#x); \
			raise(SIGABRT); \
		} \
	} while (0)
#define INFO(f,...) printf("[INFO]  " f,__VA_ARGS__)
#define WARN(f,...) printf("[WARN]  " f,__VA_ARGS__)
#define ERROR(f,...) fprintf(stderr,"[ERROR] " f,__VA_ARGS__)



#endif
