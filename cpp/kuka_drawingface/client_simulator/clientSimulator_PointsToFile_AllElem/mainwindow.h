#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTcpSocket* socket;
    QByteArray data;

private slots:
    void on_pushButton_clicked();
    void sockReady();
    void sockDisc();


private:
    void readData();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
