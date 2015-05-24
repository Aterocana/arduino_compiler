#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //http://man7.org/linux/man-pages/man3/getopt.3.html
#include <iostream>
#include <string.h>

const char* default_board = "arduino:avr:nano";
const char* default_cpu   = ":cpu=atmega328";
const char* default_port  = "/dev/ttyUSB0";

int main(int argc, char** argv){
    int option_char;
	bool board_flag    = false;
	bool cpu_flag      = false;
	bool port_flag     = false;
	bool upload_flag   = false;
	char *board_value  = NULL;
	char *cpu_value    = NULL;
	char *port_value   = NULL;
	char *upload_value = NULL;

    while((option_char = getopt(argc, argv, "b:c:p:u:")) != EOF){
		switch(option_char) {
            case('b') :
				board_value = optarg;
				board_flag = true;
				break;

            case('c') :
                cpu_value = optarg;
                cpu_flag = true;
                break;

            case('p') :
                port_value = optarg;
                port_flag = true;
                break;

            case('u') :
                upload_value = optarg;
                upload_flag = true;
                break;

            case ('?') :
                switch (optopt) {
                    case ('b'):
                        fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                        break;

                    case ('c'):
                        fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                        break;

                    case ('p'):
                        fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                        break;

                    case ('u'):
                        fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                        break;

                    default:
                        if(isprint(optopt)){
                            fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                        }
                        else{
        					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        			    	return 1;
        				}
                }

            default:
                return 1;
        }
    }

    if(!upload_flag){
        printf("The Upload option (-u) is mandatory\n");
        return 1;
    }
    if(!board_flag){
        board_value = (char *)"arduino:avr:nano";
    }
    if(!cpu_flag){
        cpu_value = (char *)":cpu=atmega328";
    }
    if(!port_flag){
        port_value = (char *)"/dev/ttyUSB0";
    }

    char cmd[350];
    strcpy(cmd, "arduino --board ");
    strcat(cmd, board_value);
    strcat(cmd, cpu_value);
    strcat(cmd, " --port ");
    strcat(cmd, port_value);
    strcat(cmd, " --upload ");
    strcat(cmd, upload_value);
    strcat(cmd, "\0");
    //printf("COMMAND: %s\n", cmd);
    std::cout << system(cmd);
    }
