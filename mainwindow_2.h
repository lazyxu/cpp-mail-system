#ifndef MAINWINDOW_2_H
#define MAINWINDOW_2_H

#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include "CMail.h"
#include "CPop3.h"
#include "Transcoding.h"

namespace Ui {
    class MainWindow_2;
}

class MainWindow_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_2(bool bIsDebug, QWidget *parent = 0);
    ~MainWindow_2();
    
signals:
    // 写邮件的信号
    // strAccount: 账号
    // strPassword: 密码
    void sigWriteMail(std::string strAccount, std::string strPassword);
    
private slots:
    // 初始化该类的槽
    // strAccount: 账号
    // strPassword: 密码
    void slotInit(std::string strAccount, std::string strPassword);
    
    // 收信的槽，显示接收到的邮件列表
    void slotRevMail();
    
    // 写信的槽
    void slotWriteMail();
    
    // 显示邮件内容的槽
    void slotShowRevMail();
    
private:
    Ui::MainWindow_2 *ui; // 界面元素指针
    bool bIsDebug; // 是否输出调试信息
    std::string strAccount; // 邮箱账号
    std::string strPassword; // 邮箱密码
    CMail *pmailRev; // 接收到的邮件类指针
    size_t ulMailRevN; // 接收到的邮件数量
};

#endif // MAINWINDOW_2_H
