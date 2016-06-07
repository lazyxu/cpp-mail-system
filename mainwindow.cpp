#include "mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::loginCheck()
{
    std::cout << "checking...\n";
    std::string strAccount = ui->username->text().toStdString();
    std::string strPassword = ui->password->text().toStdString();
    pop3 pop3Test(strAccount, strPassword);
    if ( pop3Test.bfLoginPop3(this->bIsDebug) ) {
        std::cout << "login successful!\n";
        emit loginSuccessful(strAccount, strPassword, bIsDebug);
    }
    else {
        QMessageBox::warning(this, tr("Waring"),
                             tr("user name or password error!"),
                             QMessageBox::Yes);
    }
}

void MainWindow::close()
{
    std::cout << "close...\n";
    this->show();
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
//        ui->label_title->setPixmap(QPixmap("./images/title.png"));
        QObject::connect( ui->login_button, SIGNAL(clicked()), this, SLOT(loginCheck()) );
    }

MainWindow::~MainWindow()
{
    delete ui;
}
