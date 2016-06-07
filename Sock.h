/*
 * sock.h
 *
 *  Created on: 2016年5月9日
 *      Author: Meteor
 */

#ifndef __SOCK_H__
#define __SOCK_H__

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdexcept>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h> 
#include <iostream>

class Sock
{
public:
    inline Sock(){
        num = 0;
        hp = (struct hostent *) 0;
        sock= socket(AF_INET, SOCK_STREAM, 0);
        if(sock == -1)
            throw std::runtime_error("socketinit error\n");};
    bool Connect(const char *host_id, const int &port);
    inline void send_socket(const char *s){
        send(sock, s, strlen(s), 0);};
    
    long recvline_socket();
    
    inline long recv_socket(){
        memset(recvbuf,0,BUFSIZ);
        return recv(sock, recvbuf, BUFSIZ, 0);};
    
    inline const char *get_recvbuf(){
        return recvbuf;};
    
    inline ~Sock(){
        close(sock);};
private:
    char recvbuf[BUFSIZ];
    int sock;
    int num;
    struct sockaddr_in server;
    struct hostent *hp;
};
#endif  /* Header_h */
