
#include <stdio.h>
//#include "../include/chatapp.h"
#include <strings.h>
#include <string.h>
#include "../include/global.h"
#include "../include/command_handler.h"
#include "../include/logger.h"

int STRLEN_AUTHOR	 = strlen(CMD_AUTHOR);
int STRLEN_BROADCAST = strlen(CMD_BROADCAST);
int STRLEN_IP 		 = strlen(CMD_IP);
int STRLEN_PORT		 = strlen(CMD_PORT);

char* reliableget_IP(void)
{

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
		
		cse4589_print_and_log("[%s:ERROR]\n", command_str);
		cse4589_print_and_log("[%s:END]\n",command_str);
		
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

