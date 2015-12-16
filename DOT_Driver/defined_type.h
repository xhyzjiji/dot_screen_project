#ifndef __DEFINED_TYPE_H__
#define __DEFINED_TYPE_H__

//#include "stm32f10x.h"

#define uint8_t unsigned char
#define int8_t  signed char
#define uint16_t unsigned short int
#define int16_t  signed short int
#define uint32_t unsigned int
#define int32_t  signed int

typedef enum {
	false = 0,
	true = ~false
}bool;

#endif