/*
 * CMail.h
 *
 *  Created on: 2016年5月9日
 *      Author: Meteor
 */

#ifndef CMAIL_H_
#define CMAIL_H_
#include <iostream>
#include "base64.h"
#include "Sock.h"
#include "Transcoding.hpp"
#include "mail.hpp"

using  namespace std;
class CMail
{
public:
	CMail(string smtp="", string pop3="", string address="", string password="");
	bool LoginMail(bool IsDebug);
	bool SendMail(string strFromName, string strToMailAddress, string strTitle, string strContent, bool IsDebug);
	bool ReceiveMail(bool IsDebug);
private:
    string strMailAddress;//邮箱地址
    string strMailPassword;//邮箱密码
    string strSmtp,strPop3;//smtp服务器地址
    Sock sockSendMail, sockReceiveMail;
};
#endif /* CMAIL_H_ */
