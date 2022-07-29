#include "trap.h"
#include "drv_uart.h"
#include "plic.h"

extern void trap_vector(void);

void write_mtvec(reg_t val)
{
	asm volatile("csrw mtvec, %0" : : "r"(val));
}

void write_mepc(reg_t val)
{
	asm volatile("csrw mepc, %0" : : "r"(val));
}

void trap_init(void)
{
	write_mtvec((reg_t)trap_vector);
}

void external_handle()
{
	reg_t irq = plic_claim();
	if(irq == UART0_IRQ) {
		uart_recvback();
	}

	if(irq) {
		plic_complete(irq);
	}
}

void other_handle()
{
	reg_t irq = plic_claim();
	plic_complete(irq);
}

void int_handle(reg_t mepc, reg_t mcause)
{
	(void)mepc;
	uint8_t cause_code = mcause & 0xfff;
	switch(cause_code) {
		case 11:
			external_handle();
			break;
		default:
			other_handle();
			break;
	}
}

void exception_handle(reg_t mepc, reg_t mcause)
{
	// Store/AMO access fault
	if((mcause&0x7fffffff) == 7) {
		uart_puts("Store or AMO access fault\n");
		mepc += 4;
		write_mepc(mepc);
	}
}

void trap_handle(reg_t mepc, reg_t mcause)
{
	if(mcause & 0x80000000) {
		int_handle(mepc, mcause);
	} else {
		exception_handle(mepc, mcause);
	}	
}
