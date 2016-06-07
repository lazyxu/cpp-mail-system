//
//  CMail.cpp
//  MailSystem
//
//  Created by Meteor on 16/5/30.
//  Copyright © 2016年 MeteorKL. All rights reserved.
//

#include "CMail.h"

string CMail::strfFullInfo()
{
    string strMailFullInfo;
    if (strType.compare("text/html")==0) {
        strMailFullInfo += "发件人："+ strFrom + "<br>";
        strMailFullInfo += "收件人："+ strTo + "<br>";;
        strMailFullInfo += "日期："+ strDate + "<br>";
        strMailFullInfo += "标题："+ strTitle + "<br>";
        strMailFullInfo += "正文：<br>" + strContent + "<br>";
    }
    else {
        strMailFullInfo += "发件人："+ strFrom + "\n";
        strMailFullInfo += "收件人："+ strTo + "\n";;
        strMailFullInfo += "日期："+ strDate + "\n";
        strMailFullInfo += "标题："+ strTitle + "\n";
        strMailFullInfo += "正文：\n" + strContent + "\n";
    }
    return strMailFullInfo;
}

void CMail::vSetMail(string strFrom, string strTo, string strTitle, string strContent, string strDate, string strType, size_t ulSize)
{
    this->strFrom = strFrom;
    this->strDate = strDate;
    this->strTitle = strTitle;
    this->strTo = strTo;
    this->strContent = strContent;
    this->strType = strType;
    this->ulSize = ulSize;
}