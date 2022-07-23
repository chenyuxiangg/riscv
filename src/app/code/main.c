#include "drv_uart.h"
#include "cooperation.h"

void task_test()
{
	uart_puts("task_test created!\n");
	while(1) {
		uart_puts("task_test is running\n");
		delay(1000);
	}
}
void span_main(void)
{
	uart_init();
	schedule_init();
	uart_puts("Hello, RISC-V\n");
	new_task((void*)task_test);
	schedule();
}
