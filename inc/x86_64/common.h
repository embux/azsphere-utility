#ifndef COMMON_H
#define COMMON_H

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/file.h>
#include <getopt.h>
#include <asm/types.h>
#include <sys/time.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <asm/ioctls.h>
#include <linux/serial.h>
#include <termios.h>
#include <dirent.h>
#include <errno.h>
#include <net/if.h>
#include <limits.h>

#define AZUTILITY_NAME      "AZUTILITY"
#define Utility_VERSION     "0.0.1"

#define OUI_SIZE 3

#endif