//
//  CSmtp.h
//  MailSystem
//
//  Created by Meteor on 16/5/9.
//  Copyright © 2016年 MeteorKL. All rights reserved.
//

#ifndef CSMTP_H_
#define CSMTP_H_

#include <iostream>
#include "CSock.h"
#include "Transcoding.h"

using  namespace std;
class CSmtp
{
public:
    CSmtp(string strAddress, string strAassword, bool bIsDebug);
    ~CSmtp(){
        sockSendMail.~CSock();};
    
    // 登录smtp服务器
    // 返回登录是否成功
	bool bfLoginSmtp();
    // 发送邮件
    // 返回发送邮件是否成功
    // strFromName: 发件人昵称
    // strToMailAddress: 发件人地址
    // strTitle: 邮件标题
    // strContent: 邮件内容
	bool bfSendMail(string strFromName, string strToMailAddress, string strTitle, string strContent);
    
private:
    bool bIsDebug; // 是否输出调试信息
    string strMailAddress; // 邮箱地址
    string strMailPassword; // 邮箱密码
    string strSmtp; // smtp服务器地址
    int16_t sSmtpPort; // smtp服务器端口号
    CSock sockSendMail; // 发送邮件的套接字
};
#endif /* CSmtp.h */
