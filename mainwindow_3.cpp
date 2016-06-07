#include "mainwindow_3.h"
#include "ui_mainwindow_3.h"
#include "QMessageBox"
#include <iostream>
#include "smtp.h"
void MainWindow_3::init(std::string strAccount, std::string strPassword, bool bIsDebug)
{
    std::cout << "init...\n";
    this->account = strAccount;
    this->password = strPassword;
    this->bIsDebug = bIsDebug;
    ui->fromMail->setText(QString(QString::fromLocal8Bit(this->account.c_str())));
    ui->toMail->setText("1051814353@qq.com");
    ui->title->setText("这不是垃圾邮件");
    ui->content->setText("这不是垃圾邮件");
    ui->fromMail->setEnabled(false);
    ui->fromMail->setFocusPolicy(Qt::NoFocus);
    this->show();
}

void MainWindow_3::sendMail()
{
    std::cout << "send mail...\n";
    string strFromName, strToMailAddress, strTitle, strContent;
    strFromName = this->account;
    strToMailAddress = ui->toMail->text().toStdString();
    strTitle = ui->title->text().toStdString();
    strContent = ui->content->toPlainText().toStdString();
    std::cout << this->account << endl
        << this->password << endl
        << strFromName << endl
        << strToMailAddress << endl
        << strToMailAddress << endl
        << strTitle << endl
        << strContent << endl;
    smtp smtpTest(this->account, this->password);
    if ( smtpTest.bfLoginSmtp(bIsDebug) ) {
        if ( smtpTest.bfSendMail(strFromName, strToMailAddress, strTitle, strContent, bIsDebug) )
            QMessageBox::about(this, tr("Ok"), tr("发送邮件成功！"));
        else
            QMessageBox::warning(this, tr("Waring"), tr("发送邮件失败！"), QMessageBox::Yes);
    }
}

MainWindow_3::MainWindow_3(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow_3)
{
    ui->setupUi(this);
    QObject::connect( ui->sendMail_button, SIGNAL(clicked()), this, SLOT(sendMail()) );
//    lineEdit->setEnabled(false);
//    setFocusPolicy(Qt::NoFocus);
}

MainWindow_3::~MainWindow_3()
{
    delete ui;
}
