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
