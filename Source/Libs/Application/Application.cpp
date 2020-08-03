#include "Application.h"
#include "ui_Application.h"
#include <QStandardItemModel>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <selectdialog.h>

Application::Application(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    mModel=new QStandardItemModel(this);
    ui->tableView->setModel(mModel);
    setWindowTitle("Test View File .csv");
    //setCentralWidget(ui->tableView);
}

Application::~Application()
{
    delete ui;
}
//Khoi tao thu vien FIleHelper
PiFileHelper Application::_m_PiFileHelper;
void Application::on_BntReadFileini_clicked()
{
    QString Showdata =_m_PiFileHelper.GetValueSetting("SetIPServer","IP_SERVER","IP");
    ui->PlanTextEdit->setPlainText(Showdata);
}

void Application::on_BntWriteFileini_clicked()
{
    QString xx= ui->lineEdit->text();
    _m_PiFileHelper.SetValueSetting("aaa","Input","Index",xx);
}

void Application::on_BntReadFilecsv_clicked()
{
    _m_PiFileHelper.WriteLogFile("aaa","xxxx",true);
}

void Application::on_BntWriteFilecsv_clicked()
{
    _m_PiFileHelper.WriteLogFile("xxx","11111");
}

void Application::on_BntReadAllini_clicked()
{
    QStringList xxx =_m_PiFileHelper.GetListValueSetting("Config_Input_MODA","Input","g_pi_BtnStart");
}

void Application::on_actionOpen_triggered()
{
    auto filename=QFileDialog::getOpenFileName(this,"PiAGVPro",QDir::rootPath(),"CSV File (*.csv)");
    if(filename.isEmpty())
    {
        return;
    }
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    QTextStream xin(&file);
    int ix=0;
    while (!xin.atEnd())
    {
        mModel->setRowCount(ix);
        auto line =xin.readLine();
        auto values=line.split(",");
        const int colCount=values.size();
        mModel->setColumnCount(colCount);
        for (int jx=0;jx<colCount;++jx)
        {
            setValueAt(ix,jx,values.at(jx));
        }
        ++ix;
    }
    file.close();
}

void Application::on_actionSave_triggered()
{
    auto filename = QFileDialog::getSaveFileName(this,"aaaNew",QDir::rootPath(),"CSV File (*.csv)");
    if (filename.isEmpty())
    {
        return;
    }
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        return;
    }
    QTextStream xout(&file);
    const int rowCount=mModel->rowCount();
    const int colCount=mModel->columnCount();
    for (int ix=0;ix<rowCount;++ix)
    {
        xout << getValueAt(ix,0);
        for (int jx=1;jx<colCount;++jx)
        {
            xout << "," << getValueAt(ix,jx);
        }
        xout<< "\n";
    }
    file.flush();
    file.close();
}

void Application::on_actionClose_triggered()
{
    close();
}

void Application::setValueAt(int ix, int jx, const QString &value)
{
    if(!mModel->item(ix,jx))
    {
        mModel->setItem(ix,jx,new QStandardItem(value));
    }
    else
    {
        mModel->item(ix,jx)->setText(value);
    }
}

QString Application::getValueAt(int ix, int jx)
{
    if(!mModel->item(ix,jx))
    {
        return "";
    }
    else
    {
        return  mModel->item(ix,jx)->text();
    }
}

void Application::on_actionNew_triggered()
{
    SelectDialog select(this);
    if (select.exec()==QDialog::Rejected)
    {
        return;
    }
    const int rowCOunt=select.getRowCount();
    const int colCount=select.getColCount();
    mModel->setRowCount(rowCOunt);
    mModel->setColumnCount(colCount);
}
