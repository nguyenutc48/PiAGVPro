#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    reader = new PiRFIDReader(this);

    connect(reader,SIGNAL(logChanged(QString)),ui->label,SLOT(setText(QString)));
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
