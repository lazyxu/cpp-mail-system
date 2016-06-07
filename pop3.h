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
#include "Transcoding.h"
#include "mail.h"

using  namespace std;
class pop3
{
public:
    inline pop3(string strAccount, string strPassword){
        this->strPop3 = "pop3.163.com";
        this->strMailAddress = strAccount;
        this->strMailPassword = strPassword;};
	bool bfLoginPop3(bool IsDebug);
	mail *pmailReceiveMail(bool IsDebug, unsigned long &n);
private:
    string strMailAddress;//邮箱地址
    string strMailPassword;//邮箱密码
    string strPop3;//smtp服务器地址
    Sock sockReceiveMail;
};
#endif /* POP3_H_ */
