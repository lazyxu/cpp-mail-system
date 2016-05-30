//============================================================================
// Name        : MailSystem.cpp
// Author      : meteor
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "CMail.h"
#include <iostream>
using namespace std;

int main()
{
    Sock sock;
    bool IsDebug = true;
    CMail TestMail("smtp.163.com", "pop3.163.com", "q1051814353@163.com", "q1051814353");//smtp服务器，账号，密码/授权码
    if ( TestMail.LoginMail(IsDebug) ) {
    	//发件人昵称，收件人邮箱地址，邮件标题，邮件内容
    	//TestMail.SendMail("Meteor", "1051814353@qq.com", "Hello meteor", "My name is Meteor", IsDebug);
    	TestMail.ReceiveMail(IsDebug);
    }
    else {
    	std::cout << "login failed";
    }

}
