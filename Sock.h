/*
 * sock.h
 *
 *  Created on: 2016年5月9日
 *      Author: Meteor
 */

#ifndef __SOCK_H__
#define __SOCK_H__

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdexcept>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h> 

class Sock
{
public:
    Sock();
    bool Connect(const char *host_id, const int &port);
    void send_socket(const char *s);
    long recvline_socket();
    long recv_socket();
    const char * get_recvbuf();
    ~Sock();
private:
    char recvbuf[BUFSIZ];
    int sock;
    int num;
    struct sockaddr_in server;
    struct hostent *hp;
};
#endif  /* Header_h */
