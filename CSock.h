//
//  CSock.h
//  MailSystem
//
//  Created by Meteor on 16/5/9.
//  Copyright © 2016年 MeteorKL. All rights reserved.
//

#ifndef __CSOCK_H__
#define __CSOCK_H__

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

class CSock
{
public:
    CSock(){
        hp = (struct hostent *) 0;
        sock= socket(AF_INET, SOCK_STREAM, 0);
        if(sock == -1)
            throw std::runtime_error("socketinit error\n");};
    ~CSock(){
        close(sock);};
    
    // sock套接字连接
    // 返回是否连接成功
    // host_id: 连接目标的ip地址
    // port: 连接目标的端口号
    bool Connect(const char *host_id, const int &port);
    
    // 发送信息
    // s: 发送信息内容
    inline void send_socket(const char *s){
        send(sock, s, strlen(s), 0);};
    
    // 接收一行字符串
    // 返回字符串长度
    long recvline_socket();
    
    // 接收一次信息
    // 返回接受信息长度
    inline long recv_socket(){
        memset(recvbuf,0,BUFSIZ);
        return recv(sock, recvbuf, BUFSIZ, 0);};
    
    // 返回接受信息内容
    inline const char *get_recvbuf(){
        return recvbuf;};
    
private:
    char recvbuf[BUFSIZ]; // 接收信息内容
    int sock; // 套接字连接
    struct sockaddr_in server; // 服务器地址信息
    struct hostent *hp; // 本机信息
};
#endif  /* CSock.h */
