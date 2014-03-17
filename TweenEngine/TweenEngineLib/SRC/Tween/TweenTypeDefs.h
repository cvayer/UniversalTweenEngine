#ifndef __TWEENTYPEDEFS__H__
#define __TWEENTYPEDEFS__H__

namespace Tween
{

// Base Types
typedef signed char             int8;             
typedef unsigned char           uint8;  
typedef short int               int16;
typedef unsigned short int      uint16;
typedef signed long int         int32; 
typedef unsigned long int       uint32;  
typedef signed long long int    int64; 
typedef unsigned long long int  uint64; 
typedef int32 TweenType;

static const int Infinity = -1;
static const TweenType InvalidType = -1;

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
} // Namespace Tween

#endif