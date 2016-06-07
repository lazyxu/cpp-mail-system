/*
 * smtp.h
 *
 *  Created on: 2016年5月9日
 *      Author: Meteor
 */

#ifndef SMTP_H_
#define SMTP_H_
#include <iostream>
#include "Sock.h"
#include "Transcoding.h"

using  namespace std;
class smtp
{
public:
	smtp(string address, string password);
	bool bfLoginSmtp(bool IsDebug);
	bool bfSendMail(string strFromName, string strToMailAddress, string strTitle, string strContent, bool IsDebug);
private:
    string strMailAddress;//邮箱地址
    string strMailPassword;//邮箱密码
    string strSmtp;//smtp服务器地址
    Sock sockSendMail;
};
#endif /* SMTP_H_ */
