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
    inline mail(){
        this->strFrom = "(无)";
        this->strDate = "(无)";
        this->strTitle = "(无)";
        this->strTo = "(无)";
        this->strContent = "(无)";
        this->ulSize = 0;};
    inline string info(){
        string strMailInfo;
        if (strFrom.c_str()[0]!=0)
            strMailInfo += strFrom + "\n";
        if (strDate.c_str()[0]!=0)
            strMailInfo += strDate + "\n";
        if (strTitle.c_str()[0]!=0)
            strMailInfo += strTitle + "\n";
        return strMailInfo;};
    string fullInfo();
    inline string getType(){
        return strType;};
    void setMail(string from, string to, string title, string content, string Date, string type, size_t size);
    inline void showMail(){
        cout << "from: " << strFrom << endl
        << "to: " << strTo << endl
        << "Date: " << strDate << endl
        << "size: " << ulSize << " byte" << endl
        << "title: " << strTitle << endl
        << "content: " << endl << strContent << endl << endl;};
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
