//============================================================================
// Name        : MailSystem.cpp
// Author      : meteor
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
// Xcode for Qt project.
// Generated by create_qt_xcode_project.sh, Laohyx.

//#include "CMail.h"
#include "smtp.h"
#include "pop3.h"
#include <iostream>
#include <QApplication>
#include <QLabel>
#include "mainwindow.h"
#include "mainwindow_2.h"
#include "mainwindow_3.h"
//#include "../qt_lib/QtWidgets.framework/Versions/5/Headers/QApplication"
//#include "../qt_lib/QtWidgets.framework/Versions/5/Headers/QLabel"
using namespace std;

int main(int argc, char *argv[])
{
//    size_t n;
//    bool IsDebug = true;
//    pop3 pop3Test("qqq1051814353@163.com", "qqq1051814353");
//    if ( pop3Test.bfLoginPop3(IsDebug) )
//        pop3Test.pmailReceiveMail(IsDebug, n);
    QApplication a(argc, argv);
    bool bIsDebug = true;
    MainWindow wLoginWindow(bIsDebug);
    wLoginWindow.show();
    MainWindow_2 wMainWindow;
    MainWindow_3 wSendMailWindow;
    QObject::connect(&wLoginWindow, SIGNAL(loginSuccessful(std::string, std::string, bool)),
                     &wMainWindow, SLOT(init(std::string, std::string, bool)));
    QObject::connect(&wLoginWindow, SIGNAL(loginSuccessful(std::string, std::string, bool)),
                     &wLoginWindow, SLOT(close()));
    QObject::connect(&wMainWindow, SIGNAL(sWriteMail(std::string, std::string, bool)),
                     &wSendMailWindow, SLOT(init(std::string, std::string, bool)));
    return a.exec();
    
//    int choice;
//    scanf("%d", &choice);
//    switch (choice) {
//        case 1:
//            smtpConnect(IsDebug);
//            break;
//        case 2:
//            pop3Connect(IsDebug);
//            break;
//        default:
//            break;
//    }
    
//    CMail TestMail("smtp.163.com", "pop3.163.com", "q1051814353@163.com", "q1051814353");//smtp服务器，账号，密码/授权码
//    if ( TestMail.LoginMail(IsDebug) ) {
//    	//发件人昵称，收件人邮箱地址，邮件标题，邮件内容
//    	//TestMail.SendMail("Meteor", "1051814353@qq.com", "Hello meteor", "My name is Meteor", IsDebug);
//    	TestMail.ReceiveMail(IsDebug);
//    }
//    else {
//    	std::cout << "login failed";
//    }
}

