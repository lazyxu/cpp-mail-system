#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "QMessageBox"
void MainWindow::loginCheck()
{
    std::cout << "checking...\n";
    if( ui->username->text() == tr("admin") &&
       ui->password->text() == tr("admin") ) {
        std::cout << "login successful!\n";
        emit loginSuccessful();
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        ui->username->setFocus();
        ui->username->setText("admin");
        ui->password->setText("admin");
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
