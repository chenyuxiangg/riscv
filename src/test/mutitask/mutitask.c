#include "drv_uart.h"
#include "cooperation.h"

void task_test()
{
	uart_puts("task_test created!\n");
	yeild();
	uart_puts("I am task0\n");
}

void task_test1()
{
	uart_puts("task_test1 created!\n");
	yeild();
	uart_puts("I am task1\n");
}

void span_main(void)
{
	uart_init();
	schedule_init();
	uart_puts("Hello, RISC-V\n");
	new_task((void*)task_test);
	new_task((void*)task_test1);
	schedule();
}
