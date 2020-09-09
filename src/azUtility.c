#include "common.h"
#include "ATCommand.h"
#include "serialcommu.h"

void display_help (void)
{
    printf("Usage: azUtility [-d] [-s dev_node] [--AT] [--ATI] [-S] [-D] [-A] [--SSID ssid --PSK psk -J] [-C connect_string] [-h] [-v]\n"
           "        --AT                 Send AT Check\n"
           "        --ATI                Send ATI Check\n"
           "  -d,   --setPort            Set serial port device node\n"
           "  -s,   --defPort            Use default serial port device node (/dev/ttyUSB0)\n"
           "  -S,   --AT_CWLAP           Scan Access Point\n"
           "  -D,   --AT_CWDAP           Delete all stored AP info\n"
           "  -A,   --AT_CWAAP           List all stored AP info\n"           
           "  -J,   --AT_CWJAP           Add AP info ( Input AP info using --SSID & --PSK )\n"
           "  -C,   --AT_ACCS            Setup Connection String\n"
           "  -Q,   --AT_CWSQ            Setup Connection String\n"
           "  -C,   --AT_ACWR            Send Message to Azure IoT Hub\n"
           "  -h,   --help               Display this help and exit\n"
           "  -v,   --version            Output version information and exit\n\n"
           );
    exit (0);
}

void display_version (void)
{
    printf( "Version %s \n\n"
            "Copyright ((c)) 2020 EMBUX International Co., Ltd\n\n"
            "This application secrets of EMBUX International Co., Ltd.\n"
            "No part may be reproduced or transmitted in any form by any means or\n"
            "for any purpose without the express written permission of\n"
            "EMBUX International Co., Ltd.\n\n",Utility_VERSION);

    exit (0);
}

void process_options( int argc, char *argv[] )
{
    int ch, option_index;
    bool _isSSID = false;
    bool _isPSK = false;
    char SSID[32] = "";
    char PSK[32] = "";
    static const char* short_options="vhSDAJQRC:W:s:d";
    static const struct option long_options[] =
    {
        {"version", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {"AT", no_argument, 0, 'AT'},
        {"ATI", no_argument, 0, 'ATI'},
        {"AT_CWLAP", no_argument, 0, 'S'},
        {"AT_CWDAP", no_argument, 0, 'D'},
        {"AT_CWAAP", no_argument, 0, 'A'},
        {"AT_CWJAP", no_argument, 0, 'J'},
        {"AT_CWSQ", no_argument, 0, 'Q'},
        {"AT_ACRV", no_argument, 0, 'R'},
        {"AT_ACCS", required_argument, 0, 'C'},
        {"AT_ACWR", required_argument, 0, 'W'},
        {"SSID", required_argument, 0, 'ssid'},
        {"PSK", required_argument, 0, 'psk'},
        {"setPort", required_argument, 0, 's'},
        {"defPort", no_argument, 0, 'd'},
        {0,0,0,0},
    };

    if (argc != 1) {
        
        while ((ch = getopt_long(argc, argv, short_options, long_options, &option_index)) >= 0) {
            switch (ch) {
            case 's':
                setSerialPort(optarg);
                printf("Use Set Com port: %s.\n\n", getSerialPort());
                break;
            case 'd':
                setSerialPort("/dev/ttyUSB0");
                printf("Use default Com port: %s.\n\n", getSerialPort());
                break;
            case 'ssid':
                printf("set ssid\n");
                sprintf(SSID, "%s", optarg);
                _isSSID = true;
                break;
            case 'psk':
                printf("set psk\n");
                sprintf(PSK, "%s", optarg);
                _isPSK = true;
                break;
            default:
                break;
            }
        }

        optind = 1;

        while ((ch = getopt_long(argc, argv, short_options, long_options, &option_index)) >= 0) {
            switch (ch) {
            case 'AT':
                AT();
                break;
            case 'ATI':
                ATI();
                break;
            case 'Q':
                AT_CWSQ();
                break;
            case 'A':
                AT_CWAAP();
                break;
            case 'D':
                AT_CWDAP();
                break;
            case 'S':
                AT_CWLAP();
                break;
            case 'J':
                if( _isSSID == true && _isPSK == true)
                {
                    printf("Connecting to AP\n");
                    AT_CWJAP(SSID, PSK);
                }                    
                else if( _isSSID == false )
                    printf("Require SSID for connection\n");
                else if( _isPSK == false )
                    printf("Require Password for connection\n");
                break;
            case 'C':
                printf("%s\n", optarg);
                AT_ACCS(optarg);
                break;
            case 'W':
                AT_ACWR(optarg);
                break;
            case 'R':
                AT_ACRV();
                break;
            case 'v':
                display_version();
                break;
            case 'h':
                display_help();
                break;
            default:                
                break;
            }
        }
    }
}


int main(int argc, char* argv[])
{
	process_options(argc, argv);
	return 0;
}