/**
 *  Copyleft (C) 2015 Maurizio Dominici <dominicimaurizio@gmail.com>
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

// edit these values accorging to your preferences
char default_board[25]   = "nano";  // default board name
char default_cpu[25]     = "atmega328"; // default cpu
char default_port[25]    = "/dev/ttyUSB0"; // default serial port
char empty_location[100] = "~/Documents/Programming/Arduino/sketches/empty/empty.ino"; //location of empty sketch (it should be placed in a directory with its same name)

void compile(char *board, char *cpu, char *port, char *upload);

int main(int argc, char** argv){
    int option_char;
	bool board_flag    = false;
	bool cpu_flag      = false;
	bool port_flag     = false;
	bool upload_flag   = false;
    bool empty_flag    = false;
	char *board_value  = NULL;
	char *cpu_value    = NULL;
	char *port_value   = NULL;
	char *upload_value = NULL;
	char *empty_value  = NULL;

    while((option_char = getopt(argc, argv, "b:c:p:u:e")) != EOF){
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

            case('e'):
                empty_value = optarg;
                empty_flag = true;
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

    if(empty_flag){
        upload_value = *(&empty_location);
        upload_flag  = true;
        printf("Writing EMPTY sketch: %s\n", upload_value);
    }

    if(!upload_flag){
        printf("The Upload option (-u) is mandatory\n");
        return 1;
    }
    if(!board_flag){
        board_value = *(&default_board);
    }
    if(!cpu_flag){
        cpu_value = *(&default_cpu);

    }
    if(!port_flag){
        port_value = *(&default_port);
    }
    compile(board_value, cpu_value, port_value, upload_value);
}

void compile(char *board, char *cpu, char *port, char *upload){
    char cmd[350];
    strcpy(cmd, "arduino --board arduino:avr:");
    strcat(cmd, board);
    strcat(cmd, ":cpu=");
    strcat(cmd, cpu);
    strcat(cmd, " --port ");
    strcat(cmd, port);
    strcat(cmd, " --upload ");
    strcat(cmd, upload);
    strcat(cmd, "\0");
    std::cout << system(cmd) << std::endl;
    //printf("COMMAND: %s\n", cmd);
}
