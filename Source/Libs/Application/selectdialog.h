#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDialog(QWidget *parent = nullptr);
    ~SelectDialog();
    int getRowCount() const;
    int getColCount() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SelectDialog *ui;
};

#endif // SELECTDIALOG_H
