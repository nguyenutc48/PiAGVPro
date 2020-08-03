#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include "../PiFileHelper/PiFileHelper.h"

namespace Ui {
class Application;
}
class QStandardItemModel;
class Application : public QMainWindow
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = nullptr);
    ~Application();

private slots:
    void on_BntReadFileini_clicked();

    void on_BntWriteFileini_clicked();

    void on_BntReadFilecsv_clicked();

    void on_BntWriteFilecsv_clicked();

    void on_BntReadAllini_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionClose_triggered();

    void on_actionNew_triggered();

private:
    Ui::Application *ui;
private:
    static PiFileHelper _m_PiFileHelper;
    QStandardItemModel *mModel;
    void setValueAt(int ix,int jx,const QString &value);
    QString getValueAt(int ix, int jx);
};

#endif // APPLICATION_H
