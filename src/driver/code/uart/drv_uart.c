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
	WRITE_REG_BYTE(UART_BASE_ADDR, UART_DLL, 0x3);
	WRITE_REG_BYTE(UART_BASE_ADDR, UART_DML, 0x0);

	config = 0;
	config |= 0x3;	
	WRITE_REG_BYTE(UART_BASE_ADDR, UART_LCR, config);

	// enable recv interrupt
	uint8_t ier = 0;
	READ_REG_BYTE(UART_BASE_ADDR, UART_IER, ier);
	WRITE_REG_BYTE(UART_BASE_ADDR, UART_IER, ier | 0x1);	
}

static int uart_putc(char c)
{
	WRITE_REG_BYTE(UART_BASE_ADDR, UART_THR, c);
	return 1;
}

static int uart_getc(void)
{
	uint32_t value = 0;
	READ_REG_BYTE(UART_BASE_ADDR, UART_LSR, value);
	if(value & 0x1) {
		READ_REG_BYTE(UART_BASE_ADDR, UART_RHR, value);
		return value;
	} else {
		return -1;
	}
}

void uart_recvback(void)
{
	while(1) {
		int val = uart_getc();
		if (val == -1) {
			break;
		}
		uart_putc((char)val);
	}
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
