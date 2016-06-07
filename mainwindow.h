#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include "CPop3.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(bool bIsDebug, QWidget *parent = 0);
    ~MainWindow();
    
signals:
    // 登录成功的信号
    // strAccount: 账号
    // strPassword: 密码
    void sigLoginSuccessful(std::string strAccount, std::string strPassword);
    
private slots:
    // 判断是否登录的槽
    void slotLoginCheck();
    
    // 关闭界面的槽
    void slotClose();
    
private:
    Ui::MainWindow *ui; // 界面元素指针
    bool bIsDebug; // 是否输出调试信息
};

#endif // MAINWINDOW_H
