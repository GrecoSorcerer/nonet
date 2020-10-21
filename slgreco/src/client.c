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
		printf("\n%i [PA1-Client@CSE489/589]$ ",STDIN);
		fflush(stdout);

		char* msg = (char*)malloc(sizeof(char) * MSG_SIZE);
		memset(msg, '\0', MSG_SIZE);

		if (fgets(msg, MSG_SIZE - 1, stdin) == NULL) //Mind the newline character that will be written to msg
			exit(-1);

		//handle_client_command(msg);
		handleCommand(msg, -1);

	}

	int head_socket, client_socket, selret, sock_index, fdaccept = 0, caddr_len;
	struct sockaddr_in lclient_addr, rclient_addr;
	fd_set master_list, watch_list;

		
	// Socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0)
		perror("Cannot create socket!");

	lclient_addr.sin_family = AF_INET;
	lclient_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	lclient_addr.sin_port = htons(PORT);
		
	// Bind 
	if (bind(client_socket, (struct sockaddr*)&lclient_addr, sizeof(lclient_addr)) < 0)
		perror("Bind failed\n");
		
	// Listen 
	if (listen(client_socket, BACKLOG) < 0)
		perror("Unable to listen on port!");

	FD_ZERO(&master_list);
	FD_ZERO(&watch_list);

	// Register the listening socket
    FD_SET(client_socket, &master_list);  // Not used, not yet implementing p2p
    // Register STDIN 
	FD_SET(STDIN, &master_list);
	// Register the server
	FD_SET(SERVER, &master_list);
	head_socket = client_socket;
		
	printf("\n$$$\n");
	fflush(stdout);

	while(TRUE){
		memcpy(&watch_list, &master_list, sizeof(master_list));
		// select() system call. This will BLOCK
		// Zero select FD sets 
		// struct timeval tv;
		// tv.tv_sec = 5;
		
        selret = select(head_socket + 1, &watch_list, NULL, NULL, NULL);
        if (selret < 0) {
            perror("select failed.");
		}


        // Check if we have sockets/STDIN to process
        if (selret > 0) {
			printf("\n[PA1-Client@CSE489/589]$ ");
			fflush(stdout);

            // Loop through socket descriptors to check which ones are ready 
            for (sock_index = 0; sock_index <= head_socket; sock_index += 1) {
                if (FD_ISSET(sock_index, &watch_list)) {
					
					
                    // Check if new command on STDIN 
                    if (sock_index == STDIN) {
		
						char* cmd = (char*)malloc(sizeof(char) * CMD_SIZE);

                        memset(cmd, '\0', CMD_SIZE);
                        if (fgets(cmd, CMD_SIZE - 1, stdin) == NULL)//Mind the newline character that will be written to cmd
                            exit(-1);

                        printf("I got: %s\n", cmd);

						handleCommand(cmd,selret);

						free(cmd);
                    }
                    // Check if remote client is requesting connection to this client
                    else if (sock_index == client_socket) {
                        
                        printf("\nRemote Host wanted to connect, refused!\n");
						fflush(stdout);
						
                        
                    }
                    */
                    // Read from existing connections 
                    else {
                        // Initialize buffer to receieve response 
                        char* buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
                        memset(buffer, '\0', BUFFER_SIZE);

                        if (recv(sock_index, buffer, BUFFER_SIZE, 0) <= 0) {
                            close(sock_index);
                            printf("Remote Host terminated connection!\n");

                            // Remove from watched list 
                            FD_CLR(sock_index, &master_list);
                        }
                        else {
                            //Process incoming data here ...

                            printf("This process was sent: %s\n", buffer);
                                       
                        }
						fflush(stdout);
                        free(buffer);
                    }
				}
			}
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


/*
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
		
		
		// Initialize buffer to receieve response
		char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
		memset(buffer, '\0', BUFFER_SIZE);
		
		if(recv(SERVER, buffer, BUFFER_SIZE, 0) >= 0)
		{
			printf("Server %i responded: %s", SERVER, buffer);
			fflush(stdout);
		} else {
			printf("Waiting on response from  server.\n");
			fflush(stdout);
		}*/
