#include "type.h"
#include "comm.h"
#include "drv_uart.h"

void uart_init(void)
{
	uint8_t config = 0;
	WRITE_REG_BYTE(UART_BASE_ADDR, UART_IER, 0x0);
	READ_REG_BYTE(UART_BASE_ADDR, UART_LCR,config);

	config |= (1 << 7);
	WRITE_REG_BYTE(UART_BASE_ADDR, UART_LCR, config);
	WRITE_REG_BYTE(UART_BASE_ADDR, UART_DLL, 0x1);
	WRITE_REG_BYTE(UART_BASE_ADDR, UART_DML, 0x0);

	config = 0;
	config |= 0x3;	
	WRITE_REG_BYTE(UART_BASE_ADDR, UART_LCR, config);
	
}

static int uart_putc(char c)
{
	WRITE_REG_BYTE(UART_BASE_ADDR, UART_THR, c);
	return 1;
}

int uart_puts(const char* s)
{
	int count = 0;
	const char* cps = s;
	while (*cps != '\0') {
		uart_putc(*cps);
		count++;
		cps++;
	}
	return count;
}
