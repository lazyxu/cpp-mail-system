//
//  CSmtp.cpp
//  MailSystem
//
//  Created by Meteor on 16/5/9.
//  Copyright © 2016年 MeteorKL. All rights reserved.
//

#include "CSmtp.h"

string strSmtpGetDomainName(string strAccount)
{
    size_t ulStart;
    ulStart = strAccount.find('@') + 1;
    return strAccount.substr(ulStart, strAccount.length());
}

CSmtp::CSmtp(string strAddress, string strAassword, bool bIsDebug)
{
    this->strMailAddress = strAddress;
    this->strMailPassword = strAassword;
    this->bIsDebug = bIsDebug;
    string strDomainName = strSmtpGetDomainName(strAddress);
    strSmtp = "smtp."+strDomainName;
    if ( strDomainName.compare("exmail.qq.com")==0 ||
        strDomainName.compare("gmail.com")==0) {
        sSmtpPort = 587;
    }
    else
        sSmtpPort = 25; // smtp协议专用端口
}

bool CSmtp::bfLoginSmtp()
{
	if ( bIsDebug ) std::cout<< strSmtp << sSmtpPort;
    
    // 连接服务器
	if(sockSendMail.Connect(strSmtp.c_str(), sSmtpPort) == false)
		return false;
	sockSendMail.recv_socket();
	if ( bIsDebug ) std::cout<< "Client : connected! \nServer :"
                            << sockSendMail.get_recvbuf() <<std::endl;

	// EHLO指令是必须首先发的，相当于和服务器说hello
	sockSendMail.send_socket("EHLO hello\r\n"); // hello可以被替换为其它字符串
	sockSendMail.recv_socket();
	if ( bIsDebug ) std::cout<< "Client : send helo \nServer :"
                            <<sockSendMail.get_recvbuf() << std::endl;

	// 发送 auth login 指令，告诉服务器要登录邮箱
	sockSendMail.send_socket("auth login\r\n");
	sockSendMail.recv_socket();
	if ( bIsDebug ) std::cout<< "Client : send auth login \nServer :"
	                        <<sockSendMail.get_recvbuf() << std::endl;

	// 告诉服务器要登录后，接着就是把经过了base64编码的用户名发过去了
	if ( bIsDebug ) std::cout<< pcfBase64Encode(strMailAddress.c_str());
	sockSendMail.send_socket(pcfBase64Encode(strMailAddress.c_str())); // 经过base64编码后的邮箱用户名
	sockSendMail.send_socket("\r\n");
	sockSendMail.recv_socket();
	if ( bIsDebug ) std::cout<< "Client : send name \nServer :"
	                        <<sockSendMail.get_recvbuf() << std::endl;

	// 用户名发过去后接着就是经过了base64编码的用户密码了 或者 授权码 "cTEwNTE4MTQzNTM="
	if ( bIsDebug ) std::cout<< pcfBase64Encode(strMailPassword.c_str());
	sockSendMail.send_socket(pcfBase64Encode(strMailPassword.c_str()));
	sockSendMail.send_socket("\r\n");
	sockSendMail.recv_socket();
    const char *kpcRev = sockSendMail.get_recvbuf();
	if ( bIsDebug ) std::cout<< "Client : send password \nServer :"
	                        << kpcRev << std::endl;
    if (strcmp(kpcRev, "235 Authentication successful\r\n")==0)
        return true;
    else
        return false;
}

bool CSmtp::bfSendMail(string strFromName, string strToMailAddress, string strTitle, string strContent)
{
	// 发送 mail from 指令，相当于填写发件人
    sockSendMail.send_socket(( string("MAIL FROM: <")+strMailAddress+string(">") ).c_str());
    sockSendMail.send_socket("\r\n");
    sockSendMail.recv_socket();
    if ( bIsDebug ) std::cout<< "Client: send mail from \nServer :"
    <<sockSendMail.get_recvbuf() << std::endl;

    // 发送 rcpt to 指令，就是填写收件人了
    sockSendMail.send_socket(( string("RCPT TO: <")+strToMailAddress+string(">") ).c_str());
    sockSendMail.send_socket("\r\n");
    sockSendMail.recv_socket();
    if ( bIsDebug ) std::cout<< "Client : send rcpt to \nServer"
    <<sockSendMail.get_recvbuf() << std::endl;

    // 发送data,标志着后面开始发送邮件的主题部分
    sockSendMail.send_socket("data\r\n");
    sockSendMail.recv_socket();
    if ( bIsDebug ) std::cout<< "Client : send data \nServer :"
    <<sockSendMail.get_recvbuf() << std::endl;
    
    // 发送邮件主题（subject）
    sockSendMail.send_socket(( string("From: ")+strFromName+string("<")+strMailAddress+string(">")+string("\r\n") ).c_str());
    sockSendMail.send_socket(( string("To: ")+strToMailAddress+string("\r\n") ).c_str());
    sockSendMail.send_socket(( string("Subject: ")+strTitle+string("\r\n\r\n") ).c_str());
    
//    sockSendMail.send_socket("MIME-Version: 1.0\r\n");
    
    // 发送邮件内容
    sockSendMail.send_socket(( strContent+string("\r\n \r\n") ).c_str());
    sockSendMail.send_socket(".\r\n");
    sockSendMail.recv_socket();
    const char *kpcRev = sockSendMail.get_recvbuf();
    if ( bIsDebug ) std::cout<< "Client : send content \nServer :"
                            << kpcRev <<std::endl;
    // 断开和服务器的连接
    sockSendMail.send_socket("quit\r\n");
    sockSendMail.recv_socket();
    if ( bIsDebug ) std::cout<< "Client : send quit \nServer :"
                            << sockSendMail.get_recvbuf() <<std::endl;
//    if (strncmp(kpcRev, "250 Mail OK", 11)==0)
//        return true;
//    else
//        return false;
    return true;
}
