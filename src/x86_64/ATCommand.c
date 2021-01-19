#include "common.h"
#include "serialcommu.h"

void AT()
{
	char ATCommand[64];
	sprintf(ATCommand, "AT\n");
	SendATCommand(ATCommand);
}

void ATI()
{
	char ATCommand[64];
	sprintf(ATCommand, "ATI\n");
	SendATCommand(ATCommand);
}

void AT_CWLAP()
{
	char ATCommand[64];
	sprintf(ATCommand, "AT+CWLAP\n");
	SendATCommand(ATCommand);
}

void AT_CWJAP(char* ssid, char* password)
{
	char* ATCommand[64];
	sprintf(ATCommand, "AT+CWJAP=%s,%s\n", ssid, password);
	SendATCommand(ATCommand);
}

void AT_CWAAP()
{
	char ATCommand[64];
	sprintf(ATCommand, "AT+CWAAP\n");
	SendATCommand(ATCommand);
}

void AT_CWDAP()
{
	char ATCommand[64];
	sprintf(ATCommand, "AT+CWDAP\n");
	SendATCommand(ATCommand);
}

void AT_CWSQ()
{
	char ATCommand[64];
	sprintf(ATCommand, "AT+CWSQ\n");
	SendATCommand(ATCommand);
}

void AT_ACCS(char* con_str)
{
	char ATCommand[256];
	sprintf(ATCommand, "AT+ACCS=%s\n", con_str);
	SendATCommand(ATCommand);
}

void AT_ACWR(char* msg)
{
	char ATCommand[64];
	sprintf(ATCommand, "AT+ACWR=%s\n", msg);
	SendATCommand(ATCommand);
}

void AT_ACRV() 
{
	ReceiveMessages();
}