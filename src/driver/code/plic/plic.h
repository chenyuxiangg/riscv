#ifndef PLIC_H
#define PLIC_H
#include "type.h"
#include "platform.h"

#define PLIC_BASE_ADDR 			0xc000000
#define PLIC_PRIORITY(id) 		(*((uint32_t*)(PLIC_BASE_ADDR + (id)*4)))
#define PLIC_ENABLE(hartid, offset)	(*((uint32_t*)(PLIC_BASE_ADDR + 0x2000 + (hartid) * 0x80 + (offset))))
#define PLIC_THRESHOLD(hartid)		(*((uint32_t*)(PLIC_BASE_ADDR + 0x200000 + 0x1000 * (hartid))))
#define PLIC_CLAIM(hartid)		(*((uint32_t*)(PLIC_BASE_ADDR + 0x200004 + 0x1000 * (hartid))))
#define PLIC_COMPLETE(hartid)		(*((uint32_t*)(PLIC_BASE_ADDR + 0x200004 + 0x1000 * (hartid))))

void plic_init(void);
uint32_t plic_claim(void);
void plic_complete(uint32_t irq);

#endif
