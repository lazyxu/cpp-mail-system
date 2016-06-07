#ifndef MAINWINDOW_3_H
#define MAINWINDOW_3_H

#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include "smtp.h"

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
    void init(std::string strAccount, std::string strPassword);
    void sendMail();
private:
    Ui::MainWindow_3 *ui;
    bool bIsDebug;
    std::string account;
    std::string password;
};

#endif // MAINWINDOW_3_H
