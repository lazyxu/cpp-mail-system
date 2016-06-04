//
//  mail.cpp
//  testcpp
//
//  Created by Meteor on 16/5/30.
//  Copyright © 2016年 meteor. All rights reserved.
//

#include "mail.hpp"
mail::mail(){
    this->from = "(无)";
    this->Date = "(无)";
    this->title = "(无)";
    this->to = "(无)";
    this->content = "(无)";
    this->size = 0;
}

string mail::info()
{
    string ret;
    if (from.c_str()[0]!=0)
        ret += from + "\n";
    if (Date.c_str()[0]!=0)
        ret += Date + "\n";
    if (title.c_str()[0]!=0)
        ret += title + "\n";
    return ret;
}

string mail::fullInfo()
{
    string ret;
    if (type.compare("text/html")==0) {
        if (from.c_str()[0]!=0)
            ret += "发件人："+ from + "<br>";
        if (to.c_str()[0]!=0)
            ret += "收件人："+ to + "<br>";;
        if (Date.c_str()[0]!=0)
            ret += "日期："+ Date + "<br>";
        if (title.c_str()[0]!=0)
            ret += "标题："+ title + "<br>";
        if (content.c_str()[0]!=0)
            ret += "正文：<br>" + content + "<br>";
    }
    else {
        if (from.c_str()[0]!=0)
            ret += "发件人："+ from + "\n";
        if (to.c_str()[0]!=0)
            ret += "收件人："+ to + "\n";;
        if (Date.c_str()[0]!=0)
            ret += "日期："+ Date + "\n";
        if (title.c_str()[0]!=0)
            ret += "标题："+ title + "\n";
        if (content.c_str()[0]!=0)
            ret += "正文：\n" + content + "\n";
    }
    return ret;
}

string mail::getType()
{
    return type;
}

void mail::setMail(string from, string to, string title, string content, string Date, string type, long size)
{
    if (from.c_str()[0]!=0)
        this->from = from;
    if (Date.c_str()[0]!=0)
        this->Date = Date;
    if (title.c_str()[0]!=0)
        this->title = title;
    if (to.c_str()[0]!=0)
        this->to = to;
    if (content.c_str()[0]!=0)
        this->content = content;
    this->type = type;
    this->size = size;
}

void mail::showMail()
{
    cout << "from: " << from << endl
         << "to: " << to << endl
         << "Date: " << Date << endl
         << "size: " << size << " byte" << endl
         << "title: " << title << endl
    << "content: " << endl << content << endl << endl;
}