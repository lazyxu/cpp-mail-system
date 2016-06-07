//
//  mail.cpp
//  testcpp
//
//  Created by Meteor on 16/5/30.
//  Copyright © 2016年 meteor. All rights reserved.
//

#include "mail.h"
mail::mail(){
    this->strFrom = "(无)";
    this->strDate = "(无)";
    this->strTitle = "(无)";
    this->strTo = "(无)";
    this->strContent = "(无)";
    this->ulSize = 0;
}

string mail::info()
{
    string strMailInfo;
    if (strFrom.c_str()[0]!=0)
        strMailInfo += strFrom + "\n";
    if (strDate.c_str()[0]!=0)
        strMailInfo += strDate + "\n";
    if (strTitle.c_str()[0]!=0)
        strMailInfo += strTitle + "\n";
    return strMailInfo;
}

string mail::fullInfo()
{
    string strMailFullInfo;
    if (strType.compare("text/html")==0) {
        if (strFrom.c_str()[0]!=0)
            strMailFullInfo += "发件人："+ strFrom + "<br>";
        if (strTo.c_str()[0]!=0)
            strMailFullInfo += "收件人："+ strTo + "<br>";;
        if (strDate.c_str()[0]!=0)
            strMailFullInfo += "日期："+ strDate + "<br>";
        if (strTitle.c_str()[0]!=0)
            strMailFullInfo += "标题："+ strTitle + "<br>";
        if (strContent.c_str()[0]!=0)
            strMailFullInfo += "正文：<br>" + strContent + "<br>";
    }
    else {
        if (strFrom.c_str()[0]!=0)
            strMailFullInfo += "发件人："+ strFrom + "\n";
        if (strTo.c_str()[0]!=0)
            strMailFullInfo += "收件人："+ strTo + "\n";;
        if (strDate.c_str()[0]!=0)
            strMailFullInfo += "日期："+ strDate + "\n";
        if (strTitle.c_str()[0]!=0)
            strMailFullInfo += "标题："+ strTitle + "\n";
        if (strContent.c_str()[0]!=0)
            strMailFullInfo += "正文：\n" + strContent + "\n";
    }
    return strMailFullInfo;
}

string mail::getType()
{
    return strType;
}

void mail::setMail(string strFrom, string strTo, string strTitle, string strContent, string strDate, string strType, size_t ulSize)
{
    if (strFrom.c_str()[0]!=0)
        this->strFrom = strFrom;
    if (strDate.c_str()[0]!=0)
        this->strDate = strDate;
    if (strTitle.c_str()[0]!=0)
        this->strTitle = strTitle;
    if (strTo.c_str()[0]!=0)
        this->strTo = strTo;
    if (strContent.c_str()[0]!=0)
        this->strContent = strContent;
    this->strType = strType;
    this->ulSize = ulSize;
}

void mail::showMail()
{
    cout << "from: " << strFrom << endl
         << "to: " << strTo << endl
         << "Date: " << strDate << endl
         << "size: " << ulSize << " byte" << endl
         << "title: " << strTitle << endl
    << "content: " << endl << strContent << endl << endl;
}