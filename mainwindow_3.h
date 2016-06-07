#ifndef MAINWINDOW_3_H
#define MAINWINDOW_3_H

#include <QMainWindow>
#include <iostream>
#include "QMessageBox"
#include "smtp.h"

namespace Ui {
    class MainWindow_3;
}

class MainWindow_3 : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow_3(QWidget *parent = 0);
    ~MainWindow_3();
private slots:
    void init(std::string strAccount, std::string strPassword, bool bIsDebug);
    void sendMail();
    //void sendMail(std::string name, std::string address, std::string password);
private:
    Ui::MainWindow_3 *ui;
    bool bIsDebug;
    std::string account;
    std::string password;
};

#endif // MAINWINDOW_3_H
