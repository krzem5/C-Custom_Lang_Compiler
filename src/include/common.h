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
		} \
	} while (0)



#endif
