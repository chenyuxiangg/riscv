#include "plic.h"

#define MIE_MEIE 	(1 << 11)
#define MSTATUS_MIE 	(1 << 3)

static reg_t read_tp()
{
	reg_t val = 0;
	asm volatile("mv %0, tp" : "=r"(val) :);
	return val;
}

static uint32_t read_hartid(void)
{
	uint32_t hartid = 0;
	asm volatile("csrr %0, mhartid" : "=r"(hartid) :);
	return hartid;
}

static void write_mie(reg_t mie)
{
	asm volatile("csrw mie, %0" : : "r"(mie));
}

static reg_t read_mie()
{
	reg_t val = 0;
	asm volatile("csrr %0, mie" : "=r"(val) :);
	return val;
}

static void write_mstatus(reg_t mstatus)
{
	asm volatile("csrw mstatus, %0" : : "r"(mstatus));
}

static reg_t read_mstatus()
{
	reg_t val = 0;
	asm volatile("csrr %0, mstatus" : "=r"(val) :);
	return val;
}

void plic_init(void)
{
	uint32_t hartid = read_tp();
	PLIC_ENABLE(hartid, 0) = (1 << UART0_IRQ);
	PLIC_PRIORITY(UART0_IRQ) = 1;
	PLIC_THRESHOLD(hartid) = 0;

	write_mie(read_mie() | MIE_MEIE);
	write_mstatus(read_mstatus() | MSTATUS_MIE);
}

void plic_complete(uint32_t irq)
{
	uint32_t hartid = read_tp();
	PLIC_COMPLETE(hartid) = irq;
}

uint32_t plic_claim(void)
{
	uint32_t hartid = read_tp();
	return PLIC_CLAIM(hartid);
}
