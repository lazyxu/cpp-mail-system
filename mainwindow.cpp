#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
void MainWindow::loginCheck()
{
    std::cout << "checking...\n";
    QString username = ui->username->accessibleName();
    QString password = ui->password->accessibleName();
    if( username.compare("admin") && password.compare("admin") )
        std::cout << "login successful!\n";
    emit loginSuccessful();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
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
