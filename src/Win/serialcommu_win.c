#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

char  serial_port[32] = "COM0";
HANDLE port;

void print_error(const char * context)
{
	DWORD error_code = GetLastError();
	char buffer[256];
	DWORD size = FormatMessageA(
	FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_MAX_WIDTH_MASK,
	NULL, error_code, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
	buffer, sizeof(buffer), NULL);
	if (size == 0) { buffer[0] = 0; }
	fprintf(stderr, "%s: %s\n", context, buffer);
}

HANDLE open_serial_port(const char * device, uint32_t baud_rate)
{
	HANDLE port = CreateFileA(device, GENERIC_READ | GENERIC_WRITE, 0, NULL,
	OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (port == INVALID_HANDLE_VALUE)
	{
		print_error(device);
		return INVALID_HANDLE_VALUE;
	}

	// Flush away any bytes previously read or written.
	BOOL success = FlushFileBuffers(port);
	if (!success)
	{
		print_error("Failed to flush serial port");
		CloseHandle(port);
		return INVALID_HANDLE_VALUE;
	}

	// Configure read and write operations to time out after 100 ms.
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 0;
	timeouts.ReadTotalTimeoutConstant = 100;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 100;
	timeouts.WriteTotalTimeoutMultiplier = 0;

	success = SetCommTimeouts(port, &timeouts);
	if (!success)
	{
		print_error("Failed to set serial timeouts");
		CloseHandle(port);
		return INVALID_HANDLE_VALUE;
	}

	DCB state;
	state.DCBlength = sizeof(DCB);
	success = GetCommState(port, &state);

	if (!success)
	{
		print_error("Failed to get serial settings");
		CloseHandle(port);
		return INVALID_HANDLE_VALUE;
	}

	state.BaudRate = baud_rate;

	success = SetCommState(port, &state);
	if (!success)
	{
		print_error("Failed to set serial settings");
		CloseHandle(port);
		return INVALID_HANDLE_VALUE;
	}

	return port;
}

void SendATCommand(const char* dataToSend)
{
	port = open_serial_port(serial_port, 115200);
  	if (port == INVALID_HANDLE_VALUE) 
  	{ 
  		printf("Port open error.\n");
  	}

	write_port(port, dataToSend, strlen(dataToSend));

	ReceiveATCommand(dataToSend);
	
	if( strstr(dataToSend, "AT+ACCS") || strstr(dataToSend, "AT+ACWR") )
		CheckStatus();
	
	CloseHandle(port);
}

void ReceiveATCommand(const char* dataToSend)
{
	uint8_t received_buff[256];

	if( strstr(dataToSend, "AT+CWLAP"))
	{
		while(1)
		{
			memset(&received_buff, '\0', sizeof(received_buff));

			SSIZE_T num_bytes = read_port(port, received_buff, sizeof(received_buff));

			// n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
			if (num_bytes < 0) 
			{
			    printf("Error reading: %s", strerror(errno));
			}

			printf("%s", received_buff);

			if(strstr(received_buff, "OK\r\n"))
				break;
		}
	}
	else
	{
		memset(&received_buff, '\0', sizeof(received_buff));

		SSIZE_T num_bytes = read_port(port, received_buff, sizeof(received_buff));

		// n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
		if (num_bytes < 0) 
		{
		    printf("Error reading: %s", strerror(errno));
		}

		printf("%s", received_buff);
	}	
}

void ReceiveMessages()
{
	uint8_t received_buff[256];

	port = open_serial_port(serial_port, 115200);
  	if (port == INVALID_HANDLE_VALUE) 
  	{ 
  		printf("Port open error.\n");
  	}

	while(1)
	{
		memset(&received_buff, '\0', sizeof(received_buff));

		SSIZE_T num_bytes = read_port(port, received_buff, sizeof(received_buff));

		// n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
		if (num_bytes < 0) 
		{
		    printf("Error reading: %s", strerror(errno));
		}

		printf("%s", received_buff);

		if( strstr(received_buff, "+ACRECV"))
			break;
	}	

	CloseHandle(port);
}

void CheckStatus()
{
	uint8_t received_buff[256];

	while(1)
	{
		memset(&received_buff, '\0', sizeof(received_buff));

		SSIZE_T num_bytes = read_port(port, received_buff, sizeof(received_buff));

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
	sprintf(serial_port, "\\\\.\\%s", dev_node);
}
char* getSerialPort()
{
	return serial_port;
}

int write_port(HANDLE port, uint8_t * buffer, size_t size)
{
	DWORD written;
	BOOL success = WriteFile(port, buffer, size, &written, NULL);

	if (!success)
	{
		print_error("Failed to write to port");
		return -1;
	}
	if (written != size)
	{
		print_error("Failed to write all bytes to port");
		return -1;
	}
	return 0;
}
 
// Reads bytes from the serial port.
// Returns after all the desired bytes have been read, or if there is a
// timeout or other error.
// Returns the number of bytes successfully read into the buffer, or -1 if
// there was an error reading.
int read_port(HANDLE port, uint8_t * buffer, size_t size)
{
	DWORD received;
	BOOL success = ReadFile(port, buffer, size, &received, NULL);

	if (!success)
	{
		print_error("Failed to read from port");
		return -1;
	}

	return received;
}