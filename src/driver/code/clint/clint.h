#include "type.h"

#define CLINT_BASE_ADDR 	0x2000000
#define MTIMER			(*((uint32_t*)(CLINT_BASE_ADDR+0xbff8)))
#define MTIMERCMP(hartid)	(*((uint32_t*)(CLINT_BASE_ADDR+0x4000+0x8*(hartid))))
#define MSIP(id)		(*((uint32_t*)(CLINT_BASE_ADDR+4*(id))))
