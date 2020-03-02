#ifndef _SOCKET_H_
#define _SOCKET_H_

#define PORT "3000"
#define BACKLOG 10


void sigchld_handler(int);

void *get_in_addr(struct sockaddr *);

#endif
