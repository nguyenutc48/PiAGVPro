#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    reader = new PiRFIDReader(this);
    connect(reader,SIGNAL(logChanged(QString)),ui->label,SLOT(setText(QString)));
    connect(reader,SIGNAL(dataCardChanged(QString)),ui->label_2,SLOT(setText(QString)));
    connect(ui->pushButton,SIGNAL(released()),reader,SLOT(ReaderStart()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //reader->ReaderStart();
}
