#include "mainwindow_2.h"
#include "ui_mainwindow_2.h"
#include <iostream>
#include "pop3.h"

void MainWindow_2::init()
{
    std::cout << "init...\n";
    this->show();
    revMail();
}

void MainWindow_2::revMail()
{
    std::cout << "revMail...\n";
    ui->revMail_list->clear();
    long n = 0, i;
    bool IsDebug = true;
    pop3 pop3Test("pop3.163.com", "qqq1051814353@163.com", "qqq1051814353");
    if ( pop3Test.LoginPop3(IsDebug) )
        this->mailRev = pop3Test.ReceiveMail(IsDebug, n);
    for (i=0; i<n; i++) {
        std::cout << QString(QString::fromLocal8Bit(this->mailRev[i].info().c_str())).toStdString();
        ui->revMail_list->addItem(QString(QString::fromLocal8Bit(this->mailRev[i].info().c_str())));
    }
}

void MainWindow_2::showRevMail()
{
    ui->revMail_text->clear();
    mail currentMail = this->mailRev[ui->revMail_list->currentRow()];
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
    emit sWriteMail();
}

MainWindow_2::MainWindow_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_2)
    {
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
