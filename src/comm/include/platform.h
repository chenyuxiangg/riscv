#ifndef PLATFORM_H
#define PLATFORM_H

// ============ sys =============
#define MAX_CPUS 	8

// ============ uart ============
#define UART0_IRQ	10

// ============ timer ===========
#define TIMER_DEFAULT_INTERVAL 1000000

// ============ macro ===========
#define GET_BIT(val, n)		(((val) >> (n)) & 1)

#endif
