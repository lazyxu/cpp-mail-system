#include "mainwindow_2.h"
#include "ui_mainwindow_2.h"


void MainWindow_2::init(std::string strAccount, std::string strPassword, bool bIsDebug)
{
    std::cout << "init...\n";
    this->account = strAccount;
    this->password = strPassword;
    this->bIsDebug = bIsDebug;
    ui->account_label->setText("当前登录账号："+QString(QString::fromLocal8Bit(this->account.c_str())));
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
    unsigned long ulIndex;
    pop3 pop3Test(this->account, this->password);
    if ( pop3Test.bfLoginPop3(this->bIsDebug) )
        this->mailRev = pop3Test.pmailReceiveMail(this->bIsDebug, this->mailRevN);
    for (ulIndex=0; ulIndex<this->mailRevN; ulIndex++) {
        std::cout << QString(QString::fromLocal8Bit(this->mailRev[ulIndex].info().c_str())).toStdString();
        ui->revMail_list->addItem(QString(QString::fromLocal8Bit(this->mailRev[ulIndex].info().c_str())));
    }
}

void MainWindow_2::showRevMail()
{
    ui->revMail_text->clear();
    unsigned long n = ui->revMail_list->currentRow();
    if ( n >= this->mailRevN ) {
        return;
    }
    mail mailCurrent = this->mailRev[n];
    if (mailCurrent.getType().compare("text/html")==0 ) {
        ui->revMail_text->setHtml(QString(QString::fromLocal8Bit(mailCurrent.fullInfo().c_str())));
    }
    else
        ui->revMail_text->setText(QString(QString::fromLocal8Bit(mailCurrent.fullInfo().c_str())));
    
}

void MainWindow_2::writeMail()
{
    std::cout << "writeMail...\n";
    emit sWriteMail(this->account, this->password, this->bIsDebug);
}

MainWindow_2::MainWindow_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_2)
    {
        this->mailRev = NULL;
        ui->setupUi(this);
        QFont fontMailList;
        fontMailList.setPointSize(9); // 设置字号
        ui->revMail_list->setFont(fontMailList);
        //ui->account_label->setFont(font);
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
