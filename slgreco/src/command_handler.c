
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include "../include/chatapp.h"
#include <strings.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../include/global.h"
#include "../include/command_handler.h"
#include "../include/logger.h"
#include "../include/server.h"
#include "../include/client.h"

int STRLEN_AUTHOR	 = strlen(CMD_AUTHOR);
int STRLEN_BROADCAST = strlen(CMD_BROADCAST);
int STRLEN_LOGIN	 = strlen(CMD_LOGIN);
int STRLEN_IP 		 = strlen(CMD_IP);
int STRLEN_PORT		 = strlen(CMD_PORT);

void get_IP_and_Hostname(char **hostName, char **IP)
{

	/* Programmed using the instructions provided here: (unreliable method)
	 * (link)
	 */
	
	char *_IP;
	char host[256];
	struct hostent *host_entry;
	int hostname;
	hostname = gethostname(host, sizeof(host));
	host_entry = gethostbyname(host);

	_IP = inet_ntoa( *( (struct in_addr*) host_entry->h_addr_list[0] ) );
	
	*IP = _IP;
	*hostName = host;
}

int handleCommand(char *command_str, int fd)
{
	// trim newline
	int len = strlen(command_str);
	if(command_str[len-1] == '\n')
	{
		command_str[len-1] = '\0';
	}
	
	if (!strncmp(command_str,CMD_AUTHOR,STRLEN_AUTHOR))
	{
		// 0 Points, Required for grading

		cse4589_print_and_log("[%s:SUCCESS]\n",command_str);
		cse4589_print_and_log("I, %s, have read and understood the course academic integrity policy.\n", "slgreco");
		cse4589_print_and_log("[%s:END]\n",command_str);
	}
	else if (!strncmp(command_str,CMD_IP,STRLEN_IP))
	{
		// 5 Points

		char *hostName;
		char *IP = "-1.-1.-.1";

		get_IP_and_Hostname(&hostName,&IP);
		if(!strcmp(IP,"-1.-1.-.1"))
		{
			cse4589_print_and_log("[%s:ERROR]\n", command_str);
			cse4589_print_and_log("[%s:END]\n",command_str);
		} else {

			cse4589_print_and_log("[%s:SUCCESS]\n",command_str);
			cse4589_print_and_log("IP:%s\n", IP);
			cse4589_print_and_log("[%s:END]\n",command_str);
		}
	}
	else if (!strncmp(command_str,CMD_PORT,STRLEN_PORT))
	{
		// 2.5 Points
		
		if (PORT != -1)
		{
			cse4589_print_and_log("[%s:SUCCESS]\n",command_str);
			cse4589_print_and_log("PORT:%i\n", PORT);
			cse4589_print_and_log("[%s:END]\n",command_str);
		}
		else
		{
			cse4589_print_and_log("[%s:ERROR]\n", command_str);
			cse4589_print_and_log("[%s:END]\n",command_str);
		}
	}
	else if (!strncmp(command_str, CMD_LOGIN, STRLEN_LOGIN))
	{
		// 15 Points
		char* tok;
		char* ip;
		int port = -1;

		tok = strtok(command_str, " "); // Gets the command token
		tok = strtok(NULL, " "); // Gets the ip token
		if (tok != NULL) 
		{
			ip = tok;
		} 

		tok = strtok(NULL, " "); // Gets the port token
		if (tok != NULL)
		{
			port = atoi(tok);
		}
		CON_IP = ip;
		CON_PORT = port;

		
		
		SERVER = connect_to_host(CON_IP, CON_PORT);
		
		LOGGINSTATE = 1;
		printf("attempting connection on\nIP: %s\nPort: %i\n",CON_IP,CON_PORT);
		
	} else if (!strncmp(command_str, CMD_BROADCAST, STRLEN_BROADCAST)) {

		if(send(SERVER, command_str, strlen(command_str), 0) == strlen(command_str))
		{
			printf("Done!\n");
			fflush(stdout);
		}
	}

	/*
	 * Command: grader points
	 * LIST: 10
	 * LOGIN: 15
	 * REFRESH: 5
	 * SEND: 15
	 * BROADCAST: 10
	 * BLOCK: 5
	 * BLOCKED: 5
	 * UNBLOCK: 2.5
	 * LOGOUT: 2.5
	 * EXIT: 2.5
	 * STATISTICS: 2.5
	 * BONUS(P2P file): 20
	 * */
	
}

