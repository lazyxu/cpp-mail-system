#ifndef MAINWINDOW_2_H
#define MAINWINDOW_2_H

#include <QMainWindow>

namespace Ui {
class MainWindow_2;
}

class MainWindow_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_2(QWidget *parent = 0);
    ~MainWindow_2();
signals:
    void sWriteMail();
private slots:
    void init();
    void revMail();
    void writeMail();
private:
    Ui::MainWindow_2 *ui;
};

#endif // MAINWINDOW_2_H
