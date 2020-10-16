#ifndef CLIENT_H_
#define CLIENT_H_

extern int CLIENTPORT, LOGGINSTATE, SERVER, CON_PORT;
extern char* CON_IP;

int client(char *ip, int port);
int connect_to_host(char *server_ip, int server_port);

#endif
