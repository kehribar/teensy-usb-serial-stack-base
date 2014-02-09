/*-----------------------------------------------------------------------------
/ Reads raw single-byte messages from USB serial line and prints to standart 
/ output.
/------------------------------------------------------------------------------
/ This example is based on PJRC's serial_listen USB benchmark application.
/------------------------------------------------------------------------------
/ ihsan Kehribar - 2014
/----------------------------------------------------------------------------*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	int n;
	int port;
	int flags;
	unsigned char buf[16384];
	struct termios settings;

	if (argc < 2) 
	{
		printf("Example: serial_listen [port_path]\n");
		return -1;
	}

	// Open the serial port
	port = open(argv[1], O_RDWR);
	if (port < 0) 
	{
		printf("Unable to open %s\n", argv[1]);
		return -1;
	}

	// Configure the port
	flags = fcntl(port, F_GETFL, 0);
	fcntl(port, F_SETFL, flags | O_NONBLOCK);
	tcgetattr(port, &settings);
	cfmakeraw(&settings);
	tcsetattr(port, TCSANOW, &settings);

	// write an initial byte
	buf[0] = 0xAA;
	write(port,buf,1);
	
	while (1) 
	{
		// try to read a single byte
		n = read(port, buf, 1);
		
		if (n < 1) 
		{
			// do some other things ...
		}
		else
		{
			// new valid data
			printf("%u\n",buf[0]);
		}

	}

	return 0;
}
