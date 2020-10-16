#ifndef CLIENT_H_
#define CLIENT_H_

extern int CLIENTPORT, LOGGINSTATE, SERVER;

extern int CON_PORT;
extern char* CON_IP;

int client(char *ip, int port);

#endif
