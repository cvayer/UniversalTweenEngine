// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#include "targetver.h"

#include ".\Tools\TweenTypeDefs.h"

//#define NDEBUG // Un comment to remove asserts
#include <assert.h>

#include <math.h>
#include <vector>

#ifdef DEBUG
#define TWEEN_ASSERT(COND, ...)   if (!(COND)){\
	char    mes[512], final[512];\
	sprintf_s(mes, 512, __VA_ARGS__);\
	sprintf_s(final, 512, "%s : %s%s",__FUNCTION__, mes, "\n");\
	printf(final);\
	assert(COND);}
#else
#define TWEEN_ASSERT(COND, ...)	
#endif
