//
//  CPop3.h
//  MailSystem
//
//  Created by Meteor on 16/5/9.
//  Copyright © 2016年 MeteorKL. All rights reserved.
//

#ifndef CPOP3_H_
#define CPOP3_H_

#include <iostream>
#include "CSock.h"
#include "Transcoding.h"
#include "CMail.h"

using  namespace std;
class CPop3
{
public:
    CPop3(string strAccount, string strPassword, bool bIsDebug){
        this->strPop3 = "pop3.163.com";
        this->strMailAddress = strAccount;
        this->strMailPassword = strPassword;
        this->bIsDebug = bIsDebug;};
    ~CPop3(){
        sockReceiveMail.~CSock();};
    
    // 登录pop3服务器
    // 返回登录是否成功
	bool bfLoginPop3();
    
    // 接收邮件
    // 返回邮件类指针
    // &ulRevMailNum: 邮件数量，输入输出参数
	CMail *pmailfReceiveMail(size_t &ulRevMailNum);
    
private:
    bool bIsDebug; // 是否输出调试信息
    string strMailAddress; // 邮箱地址
    string strMailPassword; // 邮箱密码
    string strPop3; // smtp服务器地址
    CSock sockReceiveMail; // 接收邮件的套接字
};
#endif /* CPop3.h */
