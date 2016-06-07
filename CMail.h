//
//  CMail.h
//  MailSystem
//
//  Created by Meteor on 16/5/30.
//  Copyright © 2016年 MeteorKL. All rights reserved.
//

#ifndef CMAIL_H
#define CMAIL_H

#include <iostream>

using  namespace std;

class CMail
{
public:
    CMail(){};
    ~CMail(){};
    inline string strfInfo(){
        string strMailInfo;
        strMailInfo += strFrom + "\n";
        strMailInfo += strDate + "\n";
        strMailInfo += strTitle + "\n";
        return strMailInfo;};
    
    // 返回邮件简要信息
    string strfFullInfo();
    
    // 返回邮件正文编码类型 plain  html
    inline string strfGetType(){
        return strType;};
    
    // 设置该类的一些成员变量
    // from: 发件人
    // to: 收件人
    // title: 邮件标题
    // content: 邮件正文
    // Date: 邮件发送日期
    // type: 邮件正文编码类型 plain  html
    // size: 邮件大小
    void vSetMail(string from, string to, string title, string content, string Date, string type, size_t size);
    
    // 显示邮件内容
    inline void vShowMail(){
        cout << "from: " << strFrom << endl
        << "to: " << strTo << endl
        << "Date: " << strDate << endl
        << "size: " << ulSize << " byte" << endl
        << "title: " << strTitle << endl
        << "content: " << endl << strContent << endl << endl;};
    
private:
    string strFrom; // 发件人
    string strTo; // 收件人
    string strTitle; // 邮件标题
    string strContent; // 邮件正文
    string strDate; // 邮件发送日期
    string strType; // 邮件正文编码类型 plain  html
    size_t ulSize; // 邮件大小
};
#endif /* CMail.h */
