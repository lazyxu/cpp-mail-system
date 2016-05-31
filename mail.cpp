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

void mail::setMail(string from, string to, string title, string content, string Date, long size)
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