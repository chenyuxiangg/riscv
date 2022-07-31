#ifndef RISCV_H
#define RISCV_H
#include "type.h"

#define MIE_MEIE 	(1 << 11)
#define MIE_MTIE	(1 << 7)
#define MSTATUS_MIE 	(1 << 3)

static inline reg_t read_tp()
{
	reg_t val = 0;
	asm volatile("mv %0, tp" : "=r"(val) :);
	return val;
}

static inline uint32_t read_mhartid(void)
{
	uint32_t hartid = 0;
	asm volatile("csrr %0, mhartid" : "=r"(hartid) :);
	return hartid;
}

static inline void write_mtvec(reg_t val)
{
	asm volatile("csrw mtvec, %0" : : "r"(val));
}

static inline void write_mepc(reg_t val)
{
	asm volatile("csrw mepc, %0" : : "r"(val));
}

static inline void write_mie(reg_t mie)
{
	asm volatile("csrw mie, %0" : : "r"(mie));
}

static inline reg_t read_mie()
{
	reg_t val = 0;
	asm volatile("csrr %0, mie" : "=r"(val) :);
	return val;
}

static inline void write_mstatus(reg_t mstatus)
{
	asm volatile("csrw mstatus, %0" : : "r"(mstatus));
}

static inline reg_t read_mstatus()
{
	reg_t val = 0;
	asm volatile("csrr %0, mstatus" : "=r"(val) :);
	return val;
}

#endif
