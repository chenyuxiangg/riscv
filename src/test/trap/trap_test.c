#include "drv_uart.h"
#include "cooperation.h"
#include "trap.h"

void task_test()
{
	uart_puts("task_test created!\n");
	*(int*)0x00000000 = 100;
	uart_puts("I am task0\n");
	while(1) {}
}

void span_main(void)
{
	uart_init();
	schedule_init();
	trap_init();
	uart_puts("Hello, RISC-V\n");
	new_task((void*)task_test);
	schedule();
}
