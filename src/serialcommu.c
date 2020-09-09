#include "common.h"

struct termios tty;
char  serial_port[32] = "/dev/ttyUSB0";

int    _openport;

void Init_Serial()
{
	// Read in existing settings, and handle any error
	if(tcgetattr(_openport, &tty) != 0) {
	    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
	}
	
	tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
	tty.c_cflag |= CS8; // 8 bits per byte (most common)

	tty.c_lflag &= ~ECHO; // Disable echo

	tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
	tty.c_cc[VMIN] = 1;

	// Set in/out baud rate to be 115200
	cfsetispeed(&tty, B115200);
	cfsetospeed(&tty, B115200);

	if (tcsetattr(_openport, TCSAFLUSH, &tty) != 0) 
	{
    	printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
	}
}

void SendATCommand(const char* dataToSend)
{
	_openport = open(serial_port, O_RDWR);

	tcflush(_openport,TCIOFLUSH);

	Init_Serial();

	printf("%d\n", strlen(dataToSend));

	write(_openport, dataToSend, strlen(dataToSend));

	ReceiveATCommand();

	if( strstr(dataToSend, "AT+ACCS") || strstr(dataToSend, "AT+ACWR") )
		CheckStatus();

	close(_openport);
}

void ReceiveATCommand()
{
	char received_buff[256];

	while(1)
	{
		memset(&received_buff, '\0', sizeof(received_buff));

		int num_bytes = read(_openport, &received_buff, sizeof(received_buff));

		// n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
		if (num_bytes < 0) 
		{
		    printf("Error reading: %s", strerror(errno));
		    break;
		}

		// printf("Read %i bytes. Received message: %s", num_bytes, received_buff);
		printf("%s", received_buff);

		if(!strcmp(received_buff, "OK\n"))
			break;
		if(!strcmp(received_buff, "+CME ERROR : unknown\n"))
			break;
	}	
}

void ReceiveMessages()
{
	char received_buff[256];

	_openport = open(serial_port, O_RDWR);

	tcflush(_openport,TCIOFLUSH);

	Init_Serial();

	while(1)
	{
		memset(&received_buff, '\0', sizeof(received_buff));

		int num_bytes = read(_openport, &received_buff, sizeof(received_buff));

		// n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
		if (num_bytes < 0) 
		{
		    printf("Error reading: %s", strerror(errno));
		    break;
		}

		// printf("Read %i bytes. Received message: %s", num_bytes, received_buff);
		printf("%s", received_buff);

		if( strstr(received_buff, "+ACRECV"))
			break;
	}	

	close(_openport);
}

void CheckStatus()
{
	char received_buff[256];

	while(1)
	{
		memset(&received_buff, '\0', sizeof(received_buff));

		int num_bytes = read(_openport, &received_buff, sizeof(received_buff));

		// n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
		if (num_bytes < 0) 
		{
		    printf("Error reading: %s", strerror(errno));
		    break;
		}

		// printf("Read %i bytes. Received message: %s", num_bytes, received_buff);
		printf("%s", received_buff);

		if( strstr(received_buff, "IOTHUB_CLIENT_CONFIRMATION_BECAUSE_DESTROY") || strstr(received_buff, "IOTHUB_CLIENT_CONFIRMATION_MESSAGE_TIMEOUT") || strstr(received_buff, "IOTHUB_CLIENT_CONFIRMATION_ERROR"))
			break;
		if( strstr(received_buff, "IOTHUB_CLIENT_CONNECTION_EXPIRED_SAS_TOKEN") || strstr(received_buff, "IOTHUB_CLIENT_CONNECTION_DEVICE_DISABLED") || strstr(received_buff, "IOTHUB_CLIENT_CONNECTION_BAD_CREDENTIAL") || strstr(received_buff, "IOTHUB_CLIENT_CONNECTION_RETRY_EXPIRED") || strstr(received_buff, "IOTHUB_CLIENT_CONNECTION_NO_NETWORK") || strstr(received_buff, "IOTHUB_CLIENT_CONNECTION_COMMUNICATION_ERROR"))
			break;
		if( strstr(received_buff, "IOTHUB_CLIENT_CONFIRMATION_OK") )
			break;
		if( strstr(received_buff, "IOTHUB_CLIENT_CONNECTION_OK") )
			break;
	}
}

void setSerialPort(char* dev_node)
{
	sprintf(serial_port, "%s", dev_node);
}
char* getSerialPort()
{
	return serial_port;
}