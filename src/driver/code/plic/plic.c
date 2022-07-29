#include "plic.h"
#include "riscv.h"

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
