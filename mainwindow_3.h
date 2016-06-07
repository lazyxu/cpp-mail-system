#ifndef MAINWINDOW_3_H
#define MAINWINDOW_3_H

#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include "CSmtp.h"

namespace Ui {
    class MainWindow_3;
}

class MainWindow_3 : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow_3(bool bIsDebug, QWidget *parent = 0);
    ~MainWindow_3();
    
private slots:
    
    // 初始化该类的槽
    // strAccount: 账号
    // strPassword: 密码
    void slotInit(std::string strAccount, std::string strPassword);
    
    // 发送邮件的槽
    void slotSendMail();
    
private:
    Ui::MainWindow_3 *ui; // 界面元素指针
    bool bIsDebug; // 是否输出调试信息
    std::string strAccount; // 邮箱账号
    std::string strPassword; // 邮箱密码
};

#endif // MAINWINDOW_3_H
