#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QBitmap>
#include <QMainWindow>
using namespace::std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_clicked();
    void listenImg(QString);
    void listenQImg(QImage);
    void listenPortrait(QImage);
    void on_portrait_clicked();
    void on_pushButton_clicked();
    void getprogbar(int);
    void getfinish();
    void getstart();
    void on_portrait_2_clicked();
    void getLog(QString);
    void getLog2(QString);

    void on_sliderdown_valueChanged(int value);

    void on_slidertop_valueChanged(int value);


    void on_XYregime_clicked();

    void on_Yregime_clicked();

    void on_Xregime_clicked();

    void on_two_clicked();

    void on_full_clicked();

    void on_pushButton_2_clicked();


    void on_clear_clicked();

    void on_sendZ_clicked();

private:
    int counter = 0;
    bool serverwasstarted = false;
    QString absolutePath = "";
    Ui::MainWindow *ui;

signals:
    void sendZ(QString);
    void sendijxy(int,int);
    void sendcurrentX(int);
    void sendFlagON();
    void takePortrait();
    void sendFlag_mythread();
    void sendtopborder(int);
    void sendbottomborder(int);
    void sendregime(int);
    void sendlenaattach(int);
    void sendrestartserver();
};

#endif // MAINWINDOW_H
