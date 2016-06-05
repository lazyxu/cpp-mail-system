/*
 * pop3.h
 *
 *  Created on: 2016年5月9日
 *      Author: Meteor
 */

#ifndef POP3_H_
#define POP3_H_
#include <iostream>
#include "Sock.h"
#include "Transcoding.hpp"
#include "mail.hpp"

using  namespace std;
class pop3
{
public:
	pop3(string pop3="", string address="", string password="");
	bool LoginPop3(bool IsDebug);
	mail *ReceiveMail(bool IsDebug, unsigned long &n);
private:
    string strMailAddress;//邮箱地址
    string strMailPassword;//邮箱密码
    string strPop3;//smtp服务器地址
    Sock sockReceiveMail;
};
#endif /* POP3_H_ */
