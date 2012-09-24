/**
 * 
 */

#include "soc-hw.h"

int main()
{
	// Say Hello!
	uart_putstr( "** Hello World **\n" );

	uart_putstr("Entering Echo Test...\n");
	while (1) {
	   uart_putchar(uart_getchar());
	}
}

