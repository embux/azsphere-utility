void  SendATCommand(const char* dataToSend);
void  ReceiveMessage();
void  setSerialPort(char* dev_node);
char* getSerialPort();
int write_port(HANDLE port, uint8_t * buffer, size_t size);
int read_port(HANDLE port, uint8_t * buffer, size_t size);
