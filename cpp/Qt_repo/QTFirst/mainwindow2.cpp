#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QPalette>
MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    QColor c(0,0,0,1);

    ui->textEdit->setPalette(QPalette(c));
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

void MainWindow2::on_actionundo_triggered()
{
ui->textEdit->undo();
}

void MainWindow2::on_actionNew_triggered()
{
    file_path = "";
    ui->textEdit->setText("");
}

void MainWindow2::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open some file");
    QFile file(file_name);
    file_path = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "..", "file was not opened");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();


}

void MainWindow2::on_actionSave_triggered()
{
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "..", "file was not opened");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow2::on_actionSave_as_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "open the file");
    QFile file(file_name);
    file_path = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "..", "file was not opened");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow2::on_actioncut_triggered()
{
ui->textEdit->cut();
}

void MainWindow2::on_actioncopy_triggered()
{
ui->textEdit->copy();
}

void MainWindow2::on_actionpaste_triggered()
{
ui->textEdit->paste();
}

void MainWindow2::on_actionredo_triggered()
{
ui->textEdit->redo();
}

void MainWindow2::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }else return;
}

void MainWindow2::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
}

void MainWindow2::on_actionBackground_color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
    if(color.isValid())
    {
        ui->textEdit->setPalette(QPalette(color));
    }
}
