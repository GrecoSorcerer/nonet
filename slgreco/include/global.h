
#ifndef GLOBAL_H_
#define GLOBAL_H_

#define HOSTNAME_LEN 128
#define PATH_LEN 256

#define TRUE 1
#define MSG_SIZE 256
#define BUFFER_SIZE 256
#define BACKLOG 5
#define STDIN 0
#define CMD_SIZE 100


char* reliableget_IP(void);
int handleCommand(char *command_str, int fd);

int server(int _port);
int client(char *ip, int port);

extern int PORT;
extern char *CON_IP;

#endif


