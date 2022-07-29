#ifndef DRV_UART_H
#define DRV_UART_H

#define UART_BASE_ADDR 0x10000000

#define UART_RHR 0x0
#define UART_THR 0x0
#define UART_DLL 0x0
#define UART_DML 0x1
#define UART_IER 0x1
#define UART_ISR 0x2
#define UART_FCR 0x2
#define UART_LCR 0x3
#define UART_MCR 0x4
#define UART_LSR 0x5
#define UART_MSR 0x6
#define UART_SPR 0x7

void uart_init(void);
int uart_puts(const char*);
void uart_recvback(void);

#endif
