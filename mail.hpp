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
    void setMail(string from, string to, string title, string content, string Date, long size);
    void showMail();
private:
    string from;
    string to;
    string title;
    string content;
    string Date;
    long size;
};
#endif /* mail_hpp */
