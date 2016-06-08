#include "mainwindow_3.h"
#include "ui_mainwindow_3.h"

void MainWindow_3::slotInit(std::string strAccount, std::string strPassword)
{
    if (bIsDebug) std::cout << "init...\n";
    this->strAccount = strAccount;
    this->strPassword = strPassword;
    ui->fromMail->setText(QString(QString::fromLocal8Bit(strAccount.c_str())));
    ui->toMail->setText("1051814353@qq.com");
    ui->title->setText("这不是垃圾邮件");
    ui->content->setText("这不是垃圾邮件");
    ui->fromMail->setEnabled(false);
    ui->fromMail->setFocusPolicy(Qt::NoFocus);
    show();
}

void MainWindow_3::slotSendMail()
{
    if (bIsDebug) std::cout << "send mail...\n";
    string strFromName, strToMailAddress, strTitle, strContent;
    strFromName = strAccount;
    strToMailAddress = ui->toMail->text().toStdString();
    strTitle = ui->title->text().toStdString();
    strContent = ui->content->toPlainText().toStdString();
    if (bIsDebug) std::cout << strAccount << endl
        << strPassword << endl
        << strFromName << endl
        << strToMailAddress << endl
        << strToMailAddress << endl
        << strTitle << endl
        << strContent << endl;
    CSmtp smtpTest(strAccount, strPassword, bIsDebug);
    if ( smtpTest.bfLoginSmtp() ) {
        if ( smtpTest.bfSendMail(strFromName, strToMailAddress, strTitle, strContent) )
            QMessageBox::about(this, tr("Ok"), tr("发送邮件成功！"));
        else
            QMessageBox::warning(this, tr("Waring"), tr("发送邮件失败！"), QMessageBox::Yes);
    }
    else
        QMessageBox::warning(this, tr("Waring"), tr("与服务器的连接断开！"), QMessageBox::Yes);
}

MainWindow_3::MainWindow_3(bool bIsDebug, QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow_3)
{
    this->bIsDebug = bIsDebug;
    ui->setupUi(this);
    QObject::connect( ui->sendMail_button, SIGNAL(clicked()), this, SLOT(slotSendMail()) );
}

MainWindow_3::~MainWindow_3()
{
    delete ui;
}
