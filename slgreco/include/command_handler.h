#ifndef CMDHNDLR_H_
#define CMDHNDLR_H_

#define CMD_AUTHOR 		"AUTHOR"
#define CMD_IP			"IP"
#define CMD_PORT		"PORT"
#define CMD_LOGIN		"LOGIN"
#define CMD_BROADCAST 	"BROADCAST"
#define CMD_EXIT 		"EXIT"

extern int STRLEN_AUTHOR, STRLEN_BROADCAST, STRLEN_IP, STRLEN_PORT, STRLEN_LOGIN;

void get_IP_and_Hostname(char **hostName, char **IP);
int handleCommand(char *command_str, int fd);
int handleServerCommand(char *command_str, int fd);
#endif
