#include "selectdialog.h"
#include "ui_selectdialog.h"

SelectDialog::SelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);
    setWindowTitle("Set Row-Columm");
}

SelectDialog::~SelectDialog()
{
    delete ui;
}

int SelectDialog::getRowCount() const
{
    return ui->rowCountspinBox->value();
}

int SelectDialog::getColCount() const
{
    return ui->colummCountspinBox->value();
}

void SelectDialog::on_buttonBox_accepted()
{
    accept();
}

void SelectDialog::on_buttonBox_rejected()
{
    reject();
}
