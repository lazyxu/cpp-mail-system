/*
 * sock.cpp
 *
 *  Created on: 2016年5月9日
 *      Author: Meteor
 */

#include "Sock.h"

Sock::Sock()
{
    num = 0;
    hp = (struct hostent *) 0;
	sock= socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        throw std::runtime_error("socketinit error\n");
    }
}
Sock::~Sock()
{
    close(sock);
}
bool Sock::Connect(const char *host_id, const int &port)
{
    server.sin_family = AF_INET;
    hp = gethostbyname(host_id);
    if(hp == (struct hostent *) 0)
    {
        std::cerr << "服务器地址获取失败！" << std::endl;
        return false;
    }
    memcpy((char *)&server.sin_addr,
           (char *)hp->h_addr, hp->h_length);
    server.sin_port = htons(port);
    if(connect(sock, (sockaddr *) &server,sizeof server) == -1)
    {
        std::cerr << "连接服务器失败！" << std::endl;
        return false;
    }
    else
        return true;
}
long Sock::recvline_socket()
{
    memset(recvbuf,0,BUFSIZ);
    long i = 0;
    while (1) {
        i += recv(sock, &recvbuf[i], 1, 0);
        if (recvbuf[i-1] == '\r') {
            i += recv(sock, &recvbuf[i], 1, 0);
            if (recvbuf[i-1] == '\n') {
                break;
            }
        }
    }
    return i;
}

void Sock::send_socket(const char *s)
{
    send(sock, s, strlen(s), 0);
}
long Sock::recv_socket()
{
    memset(recvbuf,0,BUFSIZ);
    return recv(sock, recvbuf, BUFSIZ, 0);
}
const char * Sock::get_recvbuf()
{
    return recvbuf;
}
