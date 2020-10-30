//
//	SERVER
//

 /**
  * @server
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
  * This file contains the server init and main while loop for tha application.
  * Uses the select() API to multiplex between network I/O and STDIN.
  *
  *
  * @param  argc Number of arguments
  * @param  argv The argument list
  * @return 0 EXIT_SUCCESS
  **/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

//#include "../include/chatapp.h"
#include "../include/global.h"
#include "../include/command_handler.h"
#include "../include/server.h"
#include "../include/logger.h"

struct cli_con
{
char name[100];
char ip[50];
char port[10];
};
extern struct cli_con cli[5];

void clist()
{
        struct  cli_con cli[5];
        for (int i=0,j=1;i<5;i++,j++)
                printf("%-5d %-35s %-20s %-8s \n",j,cli[i].name,cli[i].ip,cli[i].port);
        printf("hhhsgdshd");
        exit(-1);
};


int server(int _port)
{
	
    PORT = _port;
    int port, server_socket, head_socket, selret, sock_index, fdaccept = 0, caddr_len;
    struct sockaddr_in server_addr, client_addr;
    fd_set master_list, watch_list;
	
    /* Socket */
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
        perror("Cannot create socket");

    /* Fill up sockaddr_in struct */
    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    /* Bind */
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        perror("Bind failed");

    /* Listen */
    if (listen(server_socket, BACKLOG) < 0)
        perror("Unable to listen on port");

    /* ---------------------------------------------------------------------------- */

    /* Zero select FD sets */
    FD_ZERO(&master_list);
    FD_ZERO(&watch_list);

    /* Register the listening socket */
    FD_SET(server_socket, &master_list);
    /* Register STDIN */
    FD_SET(STDIN, &master_list);

    head_socket = server_socket;

    while (TRUE) {
        memcpy(&watch_list, &master_list, sizeof(master_list));

        printf("\n[PA1-Server@CSE489/589]$ ");
        fflush(stdout);

        /* select() system call. This will BLOCK */
        selret = select(head_socket + 1, &watch_list, NULL, NULL, NULL);
        if (selret < 0)
            perror("select failed.");

        /* Check if we have sockets/STDIN to process */
        if (selret > 0) {
            /* Loop through socket descriptors to check which ones are ready */
            for (sock_index = 0; sock_index <= head_socket; sock_index += 1) {

                if (FD_ISSET(sock_index, &watch_list)) {

                    /* Check if new command on STDIN */
                    if (sock_index == STDIN) {
                        char* cmd = (char*)malloc(sizeof(char) * CMD_SIZE);

                        memset(cmd, '\0', CMD_SIZE);
                        if (fgets(cmd, CMD_SIZE - 1, stdin) == NULL) //Mind the newline character that will be written to cmd
                            exit(-1);

                        printf("\nI got: %s\n", cmd);
			fflush(stdout);
			//
			// HANDLE PROJECT COMMANDS HERE
			//
			/*-----------------------------------------------------------------------------------------added 30th oct-----------*/
			if (!strncmp(cmd,"LIST",strlen("LIST")))
                        	clist();

                        handleCommand(cmd,selret);
	
                        free(cmd);
                    }
                    /* Check if new client is requesting connection */
                    else if (sock_index == server_socket) {
                        caddr_len = sizeof(client_addr);
                        fdaccept = accept(server_socket, (struct sockaddr*)&client_addr, &caddr_len);
                        if (fdaccept < 0)
                            perror("Accept failed.");

                        printf("\nRemote Host connected!\n");

                        /* Add to watched socket list */
                        FD_SET(fdaccept, &master_list);
			
			/*----------------------------------------------------------------------------added 30th oct----------*/    
                        FD_SET(fdaccept, &master_list);
                       	// printf("\n %d\n",fdaccept);
                        char *nip = inet_ntoa(client_addr.sin_addr);
                        printf("\n%s\n",nip);
                        printf("\n%d \n",ntohs(client_addr.sin_port));
                        int prt = ntohs(client_addr.sin_port);
        		getnameinfo((struct sockaddr*)&client_addr,caddr_len,hostname,sizeof(hostname),service,sizeof(service),NI_NAMEREQD);
                        printf("\n%-35s\n",hostname);
                        prt = (char)prt;
                        struct cli_con cli[5];
                        for (int i=0;i<4;i++)
                        {
				//struct cli_con cli[5];
                                //cli[i] = {hostname,nip,(char *)prt};
                                memcpy(cli[i].name,hostname, strlen(hostname));
                                memcpy(cli[i].ip,nip, strlen(nip));
                                memcpy(cli[i].port,prt,strlen(prt));

				//printf("%-35s    %s   %s",cli[i].name,cli[i].ip,cli[i].port);
                        }

                        if (fdaccept > head_socket) head_socket = fdaccept;
                    }
                    /* Read from existing clients */
                    else {
                        /* Initialize buffer to receieve response */
                        char* buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
                        memset(buffer, '\0', BUFFER_SIZE);

                        if (recv(sock_index, buffer, BUFFER_SIZE, 0) <= 0) {
                            close(sock_index);
                            printf("Remote Host terminated connection!\n");

                            /* Remove from watched list */
                            FD_CLR(sock_index, &master_list);
                        }
                        else {
                            //Process incoming data from existing clients here ...

                            printf("\nClient sent me: %s\n", buffer);
                            printf("ECHOing it back to the remote host %i selret: %i ... ",fdaccept,selret);
                            if (send(fdaccept, buffer, strlen(buffer), 0) == strlen(buffer))
                                printf("Done!\n");
				fflush(stdout);
                        }
			fflush(stdout);
                        free(buffer);
                    }
                }
            }
        }
    }

    return 0;
}

//
// END SERVER
//
