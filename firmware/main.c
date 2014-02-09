/*-----------------------------------------------------------------------------
/ Small memory & high performance USB serial example based on Teensy USB
/ library.
/------------------------------------------------------------------------------
/ Sends raw bytes rather than human-readable strings over USB serial line.
/------------------------------------------------------------------------------
/ ihsan Kehribar - 2014
/----------------------------------------------------------------------------*/
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "./teensy_usb_serial/usb_serial.h"
#include "./teensy_usb_serial/usb_serial_helper.h"

int main(void)
{
	int16_t tmp;
	uint8_t i = 0;

	usb_init();

	while (!usb_configured());

	while (!(usb_serial_get_control() & USB_SERIAL_DTR));	

	while(usb_serial_available() != 1);

	tmp = usb_serial_getchar();

	if(tmp == 0xAA)
	{
		while (1) 
		{
			usb_serial_putchar(i++);
			
			_delay_ms(100);		
		}
	}
	else
	{
		while(1);
	}

	return 0;
}

