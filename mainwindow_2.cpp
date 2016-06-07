#include "mainwindow_2.h"
#include "ui_mainwindow_2.h"


void MainWindow_2::init(std::string strAccount, std::string strPassword)
{
    if (bIsDebug) std::cout << "init...\n";
    this->account = strAccount;
    this->password = strPassword;
    ui->account_label->setText("当前登录账号："+QString(QString::fromLocal8Bit(account.c_str())));
    show();
}

void MainWindow_2::revMail()
{
    if (bIsDebug) std::cout << "revMail...\n";
    if (mailRev != NULL) {
        delete[] mailRev;
        mailRev = NULL;
    }
    ui->revMail_list->clear();
    mailRevN = 0;
    unsigned long ulIndex;
    pop3 pop3Test(account, password, bIsDebug);
    if ( pop3Test.bfLoginPop3() )
        mailRev = pop3Test.pmailReceiveMail(mailRevN);
    for (ulIndex=0; ulIndex<mailRevN; ulIndex++) {
        if (bIsDebug) std::cout << QString(QString::fromLocal8Bit(mailRev[ulIndex].info().c_str())).toStdString();
        ui->revMail_list->addItem(QString(QString::fromLocal8Bit(mailRev[ulIndex].info().c_str())));
    }
}

void MainWindow_2::showRevMail()
{
    ui->revMail_text->clear();
    unsigned long n = ui->revMail_list->currentRow();
    if ( n >= mailRevN ) {
        return;
    }
    mail mailCurrent = mailRev[n];
    if (mailCurrent.getType().compare("text/html")==0 ) {
        ui->revMail_text->setHtml(QString(QString::fromLocal8Bit(mailCurrent.fullInfo().c_str())));
    }
    else
        ui->revMail_text->setText(QString(QString::fromLocal8Bit(mailCurrent.fullInfo().c_str())));
    
}

void MainWindow_2::writeMail()
{
    std::cout << "writeMail...\n";
    emit sWriteMail(account, password);
}

MainWindow_2::MainWindow_2(bool bIsDebug, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_2)
    {
        this->bIsDebug = bIsDebug;
        mailRev = NULL;
        ui->setupUi(this);
        QFont fontMailList;
        fontMailList.setPointSize(9); // 设置字号
        ui->revMail_list->setFont(fontMailList);
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
