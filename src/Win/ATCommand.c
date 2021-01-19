#include "common.h"
#include "serialcommu_win.h"

void AT()
{
	char ATCommand[64];
	memset(&ATCommand, '\0', sizeof(ATCommand));
	sprintf(ATCommand, "AT\n");
	SendATCommand(ATCommand);
}

void ATI()
{
	char ATCommand[64];
	memset(&ATCommand, '\0', sizeof(ATCommand));
	sprintf(ATCommand, "ATI\n");
	SendATCommand(ATCommand);
}

void AT_CWLAP()
{
	char ATCommand[64];
	memset(&ATCommand, '\0', sizeof(ATCommand));
	sprintf(ATCommand, "AT+CWLAP\n");
	SendATCommand(ATCommand);
}

void AT_CWJAP(char* ssid, char* password)
{
	char* ATCommand[64];
	memset(&ATCommand, '\0', sizeof(ATCommand));
	sprintf(ATCommand, "AT+CWJAP=%s,%s\n", ssid, password);
	SendATCommand(ATCommand);
}

void AT_CWAAP()
{
	char ATCommand[64];
	memset(&ATCommand, '\0', sizeof(ATCommand));
	sprintf(ATCommand, "AT+CWAAP\n");
	SendATCommand(ATCommand);
}

void AT_CWDAP()
{
	char ATCommand[64];
	memset(&ATCommand, '\0', sizeof(ATCommand));
	sprintf(ATCommand, "AT+CWDAP\n");
	SendATCommand(ATCommand);
}

void AT_CWSQ()
{
	char ATCommand[64];
	memset(&ATCommand, '\0', sizeof(ATCommand));
	sprintf(ATCommand, "AT+CWSQ\n");
	SendATCommand(ATCommand);
}

void AT_ACCS(char* con_str)
{
	char ATCommand[256];
	memset(&ATCommand, '\0', sizeof(ATCommand));
	sprintf(ATCommand, "AT+ACCS=%s\n", con_str);
	SendATCommand(ATCommand);
}

void AT_ACWR(char* msg)
{
	char ATCommand[64];
	memset(&ATCommand, '\0', sizeof(ATCommand));
	sprintf(ATCommand, "AT+ACWR=%s\n", msg);
	SendATCommand(ATCommand);
}

void AT_ACRV() 
{
	ReceiveMessages();
}