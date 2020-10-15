#ifndef CMDHNDLR_H_
#define CMDHNDLR_H_

#define CMD_AUTHOR 		"AUTHOR"
#define CMD_IP			"IP"
#define CMD_PORT		"PORT"
#define CMD_BROADCAST 	"BROADCAST"

extern int STRLEN_AUTHOR, STRLEN_BROADCAST, STRLEN_IP, STRLEN_PORT;

void get_IP_and_Hostname(char **hostName, char **IP);
int handleCommand(char *command_str, int fd);

#endif
