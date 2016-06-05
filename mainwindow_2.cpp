#include "mainwindow_2.h"
#include "ui_mainwindow_2.h"
#include <iostream>
#include "pop3.h"

void MainWindow_2::init(std::string account, std::string password)
{
    std::cout << "init...\n";
    this->account = account;
    this->password = password;
    this->show();
    //revMail();
}

void MainWindow_2::revMail()
{
    std::cout << "revMail...\n";
    if (this->mailRev != NULL) {
        delete[] this->mailRev;
        this->mailRev = NULL;
    }
    ui->revMail_list->clear();
    this->mailRevN = 0;
    unsigned long i;
    bool IsDebug = true;
    pop3 pop3Test("pop3.163.com", this->account, this->password);
    if ( pop3Test.LoginPop3(IsDebug) )
        this->mailRev = pop3Test.ReceiveMail(IsDebug, this->mailRevN);
    for (i=0; i<this->mailRevN; i++) {
        std::cout << QString(QString::fromLocal8Bit(this->mailRev[i].info().c_str())).toStdString();
        ui->revMail_list->addItem(QString(QString::fromLocal8Bit(this->mailRev[i].info().c_str())));
    }
}

void MainWindow_2::showRevMail()
{
    ui->revMail_text->clear();
    unsigned long n = ui->revMail_list->currentRow();
    if ( n >= this->mailRevN ) {
        return;
    }
    mail currentMail = this->mailRev[n];
    if (currentMail.getType().compare("text/html")==0 ) {
//        QUrl url;
//        url.setUrl("http://mimg.126.net");
//        ui->revMail_text->setSource(url);
        ui->revMail_text->setHtml(QString(QString::fromLocal8Bit(currentMail.fullInfo().c_str())));
    }
    else
        ui->revMail_text->setText(QString(QString::fromLocal8Bit(currentMail.fullInfo().c_str())));
    
}

void MainWindow_2::writeMail()
{
    std::cout << "writeMail...\n";
    emit sWriteMail(account, password);
}

MainWindow_2::MainWindow_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_2)
    {
        this->mailRev = NULL;
        //ui->account_label->setText(QString(QString::fromLocal8Bit(this->account.c_str())));
        ui->setupUi(this);
        QFont font;
        font.setPointSize(9); // 设置字号
        ui->revMail_list->setFont(font);
        QObject::connect( ui->revMail_button, SIGNAL(clicked()), this, SLOT(revMail()) );
        QObject::connect( ui->revMail_list, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
                          this, SLOT(showRevMail()));
        
        QObject::connect( ui->writeMail_button, SIGNAL(clicked()), this, SLOT(writeMail()) );
    }

MainWindow_2::~MainWindow_2()
{
    delete ui;
    exit(0);
}
