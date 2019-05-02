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
    void on_portrait_clicked();
    void on_pushButton_clicked();
    void getprogbar(int);
    void getfinish();
    void getstart();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
