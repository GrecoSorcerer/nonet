
#include <stdio.h>
//#include "../include/chatapp.h"
#include <strings.h>
#include <string.h>
#include "../include/global.h"
#include "../include/command_handler.h"
#include "../include/logger.h"

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
		cse4589_print_and_log("[%s:SUCCESS]\n",command_str);
		cse4589_print_and_log("I, %s, have read and understood the course academic integrity policy.\n", "slgreco");
		cse4589_print_and_log("[%s:END]\n",command_str);
	}
	else if (!strncmp(command_str,CMD_IP,STRLEN_IP))
	{
		
		cse4589_print_and_log("[%s:ERROR]\n", command_str);
		cse4589_print_and_log("[%s:END]\n",command_str);
		
	}
	else if (!strncmp(command_str,CMD_PORT,STRLEN_PORT))
	{
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
	
}

