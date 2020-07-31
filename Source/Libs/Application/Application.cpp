#include "Application.h"
#include "ui_Application.h"
#include <QStandardItemModel>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

Application::Application(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
}

Application::~Application()
{
    delete ui;
}
//Khoi tao thu vien FIleHelper
PiFileHelper Application::_m_PiFileHelper;
void Application::on_BntReadFileini_clicked()
{
    QString Showdata =_m_PiFileHelper.GetValueSetting("aaa.csv"
                                                      "","Input","Index");
    ui->PlanTextEdit->setPlainText(Showdata);
}

void Application::on_BntWriteFileini_clicked()
{
    QString xx= ui->lineEdit->text();
    _m_PiFileHelper.SetValueSetting("aaa.ini","Input","Index",xx);
}

void Application::on_BntReadFilecsv_clicked()
{

}

void Application::on_BntWriteFilecsv_clicked()
{

}

void Application::on_BntReadAllini_clicked()
{
    QStringList xxx =_m_PiFileHelper.GetListValueSetting("Config_Input_MODA","Input","g_pi_BtnStart");
}
