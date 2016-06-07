#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include "pop3.h"

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
    void loginSuccessful(std::string account, std::string password);
private slots:
    void loginCheck();
    void close();
private:
    Ui::MainWindow *ui;
    bool bIsDebug;
};

#endif // MAINWINDOW_H
