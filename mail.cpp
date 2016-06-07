//
//  mail.cpp
//  testcpp
//
//  Created by Meteor on 16/5/30.
//  Copyright © 2016年 meteor. All rights reserved.
//

#include "mail.h"

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