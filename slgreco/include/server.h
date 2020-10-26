#ifndef SERVER_H_
#define SERVER_H_

struct Connection {
	struct addrinfo *client_info;
	int isLoggedIn; // defaults to 0 when new obj is created. Set this to 1 when client connects, and 0 when it diconnects. Setting to 0 would its space in the array of connections to be overwriten.
} conn;

struct Connection LOGGED_IN[5];

int server(int _port);

#endif

