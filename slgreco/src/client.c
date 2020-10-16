/**
 * @client
 * @author  Swetank Kumar Saha <swetankk@buffalo.edu>, Salvatore Leon Greco <slgreco@buffalo.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This file contains the client.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>

//#include "../include/chatapp.h"
#include "../include/global.h"
#include "../include/command_handler.h"
#include "../include/client.h"
#include "../include/logger.h"

// EXTERN Variables defined in header file
int CLIENTPORT = -1; // No listening port set
int LOGGINSTATE = 0; // User not logged in 
int SERVER = -1; // fd value
int CON_PORT = -1;
char *CON_IP = "0.0.0.0";

int client(char *ip, int listen_port)
{
	PORT = listen_port;
	
	int server_port = -1; // -1 if not set

	while(!LOGGINSTATE) 
	{
		printf("\n[PA1-Client@CSE489/589]$ ");
		fflush(stdout);

		char* msg = (char*)malloc(sizeof(char) * MSG_SIZE);
		memset(msg, '\0', MSG_SIZE);

		if (fgets(msg, MSG_SIZE - 1, stdin) == NULL) //Mind the newline character that will be written to msg
			exit(-1);

		//handle_client_command(msg);
		handleCommand(msg, -1);

	}


	while(TRUE){
		printf("\n[PA1-Client@CSE489/589]$ ");
		fflush(stdout);
		
		char *msg = (char*) malloc(sizeof(char)*MSG_SIZE);
    	memset(msg, '\0', MSG_SIZE);

    	
		if(fgets(msg, MSG_SIZE-1, stdin) == NULL) //Mind the newline character that will be written to msg
			exit(-1);

		handleCommand(msg, SERVER);
		
		
		//printf("I got: %s(size:%d chars)", msg, strlen(msg));
		printf("\nSENDing it to the remote server %i ... ", SERVER);
		if(send(SERVER, msg, strlen(msg), 0) == strlen(msg))
		{
			printf("Done!\n");
			fflush(stdout);
		}
		
		
		/* Initialize buffer to receieve response */
		char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
		memset(buffer, '\0', BUFFER_SIZE);
		
		if(recv(SERVER, buffer, BUFFER_SIZE, 0) >= 0)
		{
			printf("Server %i responded: %s", SERVER, buffer);
			fflush(stdout);
		} else {
			printf("Waiting on response from  server.\n");
			fflush(stdout);
		}
		
		
	}
}

int connect_to_host(char *server_ip, int server_port)
{
    int fdsocket, len;
    struct sockaddr_in remote_server_addr;

    fdsocket = socket(AF_INET, SOCK_STREAM, 0);
    if(fdsocket < 0)
       perror("Failed to create socket");

    bzero(&remote_server_addr, sizeof(remote_server_addr));
    remote_server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip, &remote_server_addr.sin_addr);
    remote_server_addr.sin_port = htons(server_port);

    if(connect(fdsocket, (struct sockaddr*)&remote_server_addr, sizeof(remote_server_addr)) < 0)
        perror("Connect failed");

    return fdsocket;
}
