/*-----------------------------------------------------------------------------
/
/
/
/
/
/
/----------------------------------------------------------------------------*/

#include <avr/pgmspace.h>

// Send a string to the USB serial port.  The string must be in flash memory, using PSTR
void send_str(const char *s);