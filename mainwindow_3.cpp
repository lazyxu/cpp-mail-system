#include "mainwindow_3.h"
#include "ui_mainwindow_3.h"
#include "QMessageBox"
#include <iostream>
#include "smtp.h"
void MainWindow_3::init(std::string strAccount, std::string strPassword)
{
    if (bIsDebug) std::cout << "init...\n";
    this->account = strAccount;
    this->password = strPassword;
    ui->fromMail->setText(QString(QString::fromLocal8Bit(account.c_str())));
    ui->toMail->setText("1051814353@qq.com");
    ui->title->setText("这不是垃圾邮件");
    ui->content->setText("这不是垃圾邮件");
    ui->fromMail->setEnabled(false);
    ui->fromMail->setFocusPolicy(Qt::NoFocus);
    show();
}

void MainWindow_3::sendMail()
{
    if (bIsDebug) std::cout << "send mail...\n";
    string strFromName, strToMailAddress, strTitle, strContent;
    strFromName = account;
    strToMailAddress = ui->toMail->text().toStdString();
    strTitle = ui->title->text().toStdString();
    strContent = ui->content->toPlainText().toStdString();
    if (bIsDebug) std::cout << account << endl
        << password << endl
        << strFromName << endl
        << strToMailAddress << endl
        << strToMailAddress << endl
        << strTitle << endl
        << strContent << endl;
    smtp smtpTest(account, password);
    if ( smtpTest.bfLoginSmtp(bIsDebug) ) {
        if ( smtpTest.bfSendMail(strFromName, strToMailAddress, strTitle, strContent, bIsDebug) )
            QMessageBox::about(this, tr("Ok"), tr("发送邮件成功！"));
        else
            QMessageBox::warning(this, tr("Waring"), tr("发送邮件失败！"), QMessageBox::Yes);
    }
}

MainWindow_3::MainWindow_3(bool bIsDebug, QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow_3)
{
    this->bIsDebug = bIsDebug;
    ui->setupUi(this);
    QObject::connect( ui->sendMail_button, SIGNAL(clicked()), this, SLOT(sendMail()) );
}

MainWindow_3::~MainWindow_3()
{
    delete ui;
}
