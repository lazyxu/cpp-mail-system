/*  smtp.cpp
 *
 *  Created on: 2016年5月9日
 *      Author: Meteor
 */

#include "smtp.h"

smtp::smtp(string smtp, string address, string password)
{
	strSmtp = smtp;
	strMailAddress = address;
	strMailPassword = password;
}
bool smtp::LoginSmtp(bool IsDebug)
{
	if ( IsDebug ) std::cout<< strSmtp.c_str();
	int smtpPort = 25;//smtp协议专用端口
	if(sockSendMail.Connect(strSmtp.c_str(), smtpPort) == false)
		return false;
	sockSendMail.recv_socket();
	if ( IsDebug ) if ( IsDebug ) std::cout<< "Client : connected! \nServer :"
	<< sockSendMail.get_recvbuf() <<std::endl;

	/*EHLO指令是必须首先发的，相当于和服务器说hello*/
	sockSendMail.send_socket("EHLO hello\r\n");//hello可以被替换为其它字符串
	sockSendMail.recv_socket();
	if ( IsDebug ) std::cout<< "Client : send helo \nServer :"
	<<sockSendMail.get_recvbuf() << std::endl;

	/*发送 auth login 指令，告诉服务器要登录邮箱*/
	sockSendMail.send_socket("auth login\r\n");
	sockSendMail.recv_socket();
	if ( IsDebug ) std::cout<< "Client : send auth login \nServer :"
	<<sockSendMail.get_recvbuf() << std::endl;

	/*告诉服务器要登录后，接着就是把用户名发过去了.
	 不过这个用户名是经过了base64编码的，smtp也支持
	 明文传送，至于具体有什么区别上网上找资料看看就知道了*/
	if ( IsDebug ) std::cout<< base64_encode(strMailAddress.c_str());
	sockSendMail.send_socket(base64_encode(strMailAddress.c_str()));//经过base64编码后的邮箱用户名
	sockSendMail.send_socket("\r\n");
	sockSendMail.recv_socket();
	if ( IsDebug ) std::cout<< "Client : send name \nServer :"
	<<sockSendMail.get_recvbuf() << std::endl;

	/*用户名发过去后接着就是用户密码了，当然也是经过base64编码后的*/
	if ( IsDebug ) std::cout<< base64_encode(strMailPassword.c_str());
	sockSendMail.send_socket(base64_encode(strMailPassword.c_str()));// 授权码 "cTEwNTE4MTQzNTM="
	sockSendMail.send_socket("\r\n");
	sockSendMail.recv_socket();
	if ( IsDebug ) std::cout<< "Client : send password \nServer :"
	<<sockSendMail.get_recvbuf() << std::endl;

	return true;
}

bool smtp::SendMail(string strFromName, string strToMailAddress, string strTitle, string strContent, bool IsDebug)
{
	/*发送 mail from 指令，相当于填写发件人*/
    sockSendMail.send_socket(( string("MAIL FROM: <")+strMailAddress+string(">") ).c_str());
    sockSendMail.send_socket("\r\n");
    sockSendMail.recv_socket();
    if ( IsDebug ) std::cout<< "Client: send mail from \nServer :"
    <<sockSendMail.get_recvbuf() << std::endl;

    /*发送 rcpt to 指令，就是填写收件人了 */
    sockSendMail.send_socket(( string("RCPT TO: <")+strToMailAddress+string(">") ).c_str());
    sockSendMail.send_socket("\r\n");
    sockSendMail.recv_socket();
    if ( IsDebug ) std::cout<< "Client : send rcpt to \nServer"
    <<sockSendMail.get_recvbuf() << std::endl;

    /*发送data,标志着后面开始发送邮件的主题部分*/
    sockSendMail.send_socket("data\r\n");
    sockSendMail.recv_socket();
    if ( IsDebug ) std::cout<< "Client : send data \nServer :"
    <<sockSendMail.get_recvbuf() << std::endl;
    /*发送邮件主体部分，先是邮件主题（subject）,后面是邮件内容。
     下面就是发送主体的格式*/
    sockSendMail.send_socket(( string("From: ")+strFromName+string("<")+strMailAddress+string(">")+string("\r\n") ).c_str());
    sockSendMail.send_socket(( string("To: ")+strToMailAddress+string("\r\n") ).c_str());
    sockSendMail.send_socket(( string("Subject: ")+strTitle+string("\r\n\r\n") ).c_str());
    sockSendMail.send_socket(( strContent+string("\r\n \r\n") ).c_str());
    sockSendMail.send_socket(".\r\n");
    sockSendMail.recv_socket();
    if ( IsDebug ) std::cout<< "Client : send content \nServer :"
    << sockSendMail.get_recvbuf() <<std::endl;

    sockSendMail.send_socket("quit\r\n");
    sockSendMail.recv_socket();
    if ( IsDebug ) std::cout<< "Client : send quit \nServer :"
    << sockSendMail.get_recvbuf() <<std::endl;
    return true;
}
