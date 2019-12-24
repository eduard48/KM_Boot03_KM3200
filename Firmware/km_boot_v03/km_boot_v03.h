/************************************************************************
* Заголовок для boot_v2_mkm.c
* Здесь определяю то что необходимо для компиляции проекта
* для ATmega168PA и контроллера КМ01-3200.М
************************************************************************/
#ifndef BOOT_V2_H
#define BOOT_V2_H

// Основные определения типа контроллера

#include <avr/io.h>

#if defined (SPMCSR)
#define SPM_REG SPMCSR
#elif defined (SPMCR)
#define SPM_REG SPMCR
#else
#error "AVR processor does not provide bootloader support!"
#endif

#define APP_END (FLASHEND - (BOOTSIZE * 2))

#if (SPM_PAGESIZE > UINT8_MAX)
typedef uint16_t pagebuf_t;
#else
typedef uint8_t pagebuf_t;
#endif

/* Определения для ATmega 168P Part-Code
  I (M. Thomas) could not find an official Boot-ID 
   for the ATmega168P so pretend it's an ATmega16 */
/* Part-Code ISP */
#define DEVTYPE_ISP     0x74
/* Part-Code Boot */
#define DEVTYPE_BOOT    0x75

#define SIG_BYTE1	0x1E
#define SIG_BYTE2	0x94
#define SIG_BYTE3	0x06
//--------------------------------------------------
// Определения для работы с UART0 (используем только его для заливки программ)
/* UART 0 */
#define UART_BAUD_HIGH	UBRR0H
#define UART_BAUD_LOW	UBRR0L
#define UART_STATUS	    UCSR0A
#define UART_TXREADY	UDRE0
#define UART_RXREADY	RXC0
#define UART_DOUBLE	    U2X0
#define UART_CTRL	    UCSR0B
#define UART_CTRL_DATA	((1<<TXEN0) | (1<<RXEN0))
#define UART_CTRL2	    UCSR0C
#define UART_CTRL2_DATA	( (1<<UCSZ01) | (1<<UCSZ00))
#define UART_DATA	    UDR0

#define WDT_OFF_SPECIAL

static inline void bootloader_wdt_off(void)
{
	cli();
	wdt_reset();
	/* Clear WDRF in MCUSR */
	MCUSR &= ~(1<<WDRF);
	/* Write logical one to WDCE and WDE */
	/* Keep old prescaler setting to prevent unintentional time-out */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Turn off WDT */
	WDTCSR = 0x00;
}

// ---------------------------------------------------


#endif
/************************************** END **************************/