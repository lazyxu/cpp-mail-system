//
//  mail.hpp
//  testcpp
//
//  Created by Meteor on 16/5/30.
//  Copyright © 2016年 meteor. All rights reserved.
//

#ifndef mail_hpp
#define mail_hpp
#include <iostream>
using  namespace std;
class mail
{
public:
    mail();
    string info();
    string fullInfo();
    string getType();
    void setMail(string from, string to, string title, string content, string Date, string type, size_t size);
    void showMail();
private:
    string strFrom;
    string strTo;
    string strTitle;
    string strContent;
    string strDate;
    string strType;
    size_t ulSize;
};
#endif /* mail_hpp */
