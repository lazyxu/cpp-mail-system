#ifndef MAINWINDOW_2_H
#define MAINWINDOW_2_H

#include <QMainWindow>
#include "mail.h"
#include <iostream>
#include "QMessageBox"
#include "pop3.h"

namespace Ui {
class MainWindow_2;
}

class MainWindow_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_2(QWidget *parent = 0);
    ~MainWindow_2();
signals:
    void sWriteMail(std::string strAccount, std::string strPassword, bool bIsDebug);
private slots:
    void init(std::string strAccount, std::string strPassword, bool bIsDebug);
    void revMail();
    void writeMail();
    void showRevMail();
private:
    Ui::MainWindow_2 *ui;
    mail *mailRev;
    unsigned long mailRevN;
    bool bIsDebug;
    std::string account;
    std::string password;
};

#endif // MAINWINDOW_2_H
