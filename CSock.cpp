//
//  CSock.cpp
//  MailSystem
//
//  Created by Meteor on 16/5/9.
//  Copyright © 2016年 MeteorKL. All rights reserved.
//

#include "CSock.h"

bool CSock::Connect(const char *host_id, const int &port)
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
long CSock::recvline_socket()
{
    memset(recvbuf,0,BUFSIZ);
    long i = 0;
    while (1) {
        i += recv(sock, &recvbuf[i], 1, 0);
        if (i == BUFSIZ - 1) { // 如果接收信息大小等于recvbuf数组大小，则break
            recvbuf[i] = 0;
            break;
        }
        if (recvbuf[i-1] == '\r') {
            i += recv(sock, &recvbuf[i], 1, 0); // 每次接收一个字符，直到连续两个字符为\r\n（即一行结束的标志）break
            if (recvbuf[i-1] == '\n') {
                break;
            }
        }
    }
    return i;
}
