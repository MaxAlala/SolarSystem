#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "mainwindow2.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_progressBar_valueChanged(int value);

    void on_signIn_clicked();

    void on_actionClose_triggered();

private:
    Ui::MainWindow *ui;
    Dialog * dialog;
    MainWindow2 *ui2;
};
#endif // MAINWINDOW_H
