#ifndef TIMER_H
#define TIMER_H
#include "type.h"

#define CLINT_BASE_ADDR 	0x2000000
#define TIMER_DEFAULT_INTERVAL	0x1000000
#define MTIMER			(*((uint64_t*)(CLINT_BASE_ADDR+0xbff8)))
#define MTIMERCMP(hartid)	(*((uint64_t*)(CLINT_BASE_ADDR+0x4000+0x8*(hartid))))

void timer_init(void);
void timer_load(uint64_t interval);

#endif
