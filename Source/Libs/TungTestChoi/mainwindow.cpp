#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    reader = new PiRFIDReader(this,"/dev/ttyS0");

    connect(reader,SIGNAL(logChanged(QString)),ui->label,SLOT(setText(QString)));
    connect(reader,SIGNAL(dataCardChanged(QString)),ui->label_2,SLOT(setText(QString)));
    //connect(ui->pushButton,SIGNAL(released()),reader,SLOT(ReaderStart()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    reader->ReaderStart();
}

void MainWindow::on_pushButton_2_clicked()
{
    reader1 = new PiRFIDReader(this);
    reader1->ReaderStart();
    connect(reader1,SIGNAL(logChanged(QString)),ui->label_2,SLOT(setText(QString)));
}

void MainWindow::on_pushButton_3_clicked()
{
    reader->ReaderStop();
}

void MainWindow::on_pushButton_4_clicked()
{
    reader1->ReaderStop();
}

void MainWindow::on_pushButton_5_clicked()
{
    QString a = ui->lineEdit->text();
    QVariant b = reader->dataCardWrite(a);

}
