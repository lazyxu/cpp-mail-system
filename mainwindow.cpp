#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::slotLoginCheck()
{
    if (bIsDebug) std::cout << "checking...\n";
    std::string strAccount = ui->username->text().toStdString();
    std::string strPassword = ui->password->text().toStdString();
    CPop3 pop3Test(strAccount, strPassword, bIsDebug);
    if (strAccount.compare("")==0) {
        QMessageBox::warning(this, tr("Waring"), tr("please input your e-mail address!"), QMessageBox::Yes);
        return;
    }
    if (strPassword.compare("")==0) {
        QMessageBox::warning(this, tr("Waring"), tr("please input your password!"), QMessageBox::Yes);
        return;
    }
    if ( pop3Test.bfLoginPop3() ) {
        if (bIsDebug) std::cout << "login successful!\n";
        emit sigLoginSuccessful(strAccount, strPassword);
    }
    else
        QMessageBox::warning(this, tr("Waring"), tr("user name or password error!"), QMessageBox::Yes);
}

void MainWindow::slotClose()
{
    if (bIsDebug) std::cout << "close...\n";
    show();
    MainWindow::~MainWindow();
}

MainWindow::MainWindow(bool bIsDebug, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
        this->bIsDebug = bIsDebug;
        ui->setupUi(this);
        ui->username->setFocus();
        ui->username->setText("qqq1051814353@163.com");
        ui->password->setText("qqq1051814353");
    //    this->image = new QImage();
    //    image->load("./images/login.png");
    //    QGraphicsScene *scene = new QGraphicsScene;
    //    scene->addPixmap(QPixmap::fromImage(*image));
    //    ui->graphicsView->setScene(scene);
    //    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
    //    ui->graphicsView->show();

//        ui->label_login->setPixmap(QPixmap("./images/login.png"));
        ui->label_title->setPixmap(QPixmap("./images/title.png"));
        QObject::connect( ui->login_button, SIGNAL(clicked()), this, SLOT(slotLoginCheck()) );
    }

MainWindow::~MainWindow()
{
    delete ui;
}
