#include "mainwindow_2.h"
#include "ui_mainwindow_2.h"

void MainWindow_2::slotInit(std::string strAccount, std::string strPassword)
{
    if (bIsDebug) std::cout << "init...\n";
    this->strAccount = strAccount;
    this->strPassword = strPassword;
    ui->account_label->setText("当前登录账号："+QString(QString::fromLocal8Bit(strAccount.c_str())));
    show();
}

void MainWindow_2::slotRevMail()
{
    if (bIsDebug) std::cout << "revMail...\n";
    if (pmailRev != NULL) {
        delete[] pmailRev;
        pmailRev = NULL;
    }
    ui->revMail_list->clear();
    pmailRev = 0;
    size_t ulIndex;
    CPop3 pop3Test(strAccount, strPassword, bIsDebug);
//    if ( pop3Test.bfLoginPop3() ) {
//        size_t *ulRevMailSize = pop3Test.pmailfRevMailNumSize(ulMailRevN);
//        pmailRev = new CMail[ulMailRevN]; // 邮件类指针
//        char acTemp1[10], acTemp2[10];
//        for (ulIndex=0; ulIndex<ulMailRevN; ulIndex++) {
//            pop3Test.bfReceiveMailContent(pmailRev, ulRevMailSize, (int32_t)ulIndex);
//            if (bIsDebug) std::cout << QString(QString::fromLocal8Bit(pmailRev[ulIndex].strfInfo().c_str())).toStdString();
//            ui->revMail_list->addItem(QString(QString::fromLocal8Bit(pmailRev[ulIndex].strfInfo().c_str())));
//            ulfItoa(ulIndex, acTemp1);
//            ulfItoa(ulMailRevN, acTemp2);
//            ui->revMailnum_lable->setText("读取邮件中："+(QString)acTemp1+"/"+(QString)acTemp2);
//        }
//        delete [] ulRevMailSize;
//        pop3Test.vfDisConnect();
//    }
    if ( pop3Test.bfLoginPop3() )
        pmailRev = pop3Test.pmailfReceiveMail(ulMailRevN);
    for (ulIndex=0; ulIndex<ulMailRevN; ulIndex++) {
        if (bIsDebug) std::cout << QString(QString::fromLocal8Bit(pmailRev[ulIndex].strfInfo().c_str())).toStdString();
        ui->revMail_list->addItem(QString(QString::fromLocal8Bit(pmailRev[ulIndex].strfInfo().c_str())));
    }
    ui->revMailnum_lable->setText("读取邮件完毕");
}

void MainWindow_2::slotShowRevMail()
{
    ui->revMail_text->clear();
    size_t n = ui->revMail_list->currentRow();
    if ( n >= ulMailRevN ) {
        return;
    }
    CMail mailCurrent = pmailRev[n];
    char acTemp1[10], acTemp2[10];
    ulfItoa(n+1, acTemp1);
    ulfItoa(ulMailRevN, acTemp2);
    ui->revMailnum_lable->setText("当前选中邮件："+(QString)acTemp1+"/"+(QString)acTemp2);
    if (mailCurrent.strfGetType().compare("text/html")==0 ) {
        ui->revMail_text->setHtml(QString(QString::fromLocal8Bit(mailCurrent.strfFullInfo().c_str())));
    }
    else
        ui->revMail_text->setText(QString(QString::fromLocal8Bit(mailCurrent.strfFullInfo().c_str())));
    
}

void MainWindow_2::slotWriteMail()
{
    std::cout << "writeMail...\n";
    emit sigWriteMail(strAccount, strPassword);
}

MainWindow_2::MainWindow_2(bool bIsDebug, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_2)
    {
        this->bIsDebug = bIsDebug;
        pmailRev = NULL;
        ui->setupUi(this);
        QFont fontMailList;
        fontMailList.setPointSize(9); // 设置字号
        ui->revMail_list->setFont(fontMailList);
        QObject::connect( ui->revMail_button, SIGNAL(clicked()), this, SLOT(slotRevMail()) );
        QObject::connect( ui->revMail_list, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
                          this, SLOT(slotShowRevMail()));
        
        QObject::connect( ui->writeMail_button, SIGNAL(clicked()), this, SLOT(slotWriteMail()) );
    }

MainWindow_2::~MainWindow_2()
{
    delete ui;
    exit(0);
}
