/********************************************************************************
** Form generated from reading UI file 'selectdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTDIALOG_H
#define UI_SELECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SelectDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *rowCountspinBox;
    QFormLayout *formLayout_2;
    QLabel *label_2;
    QSpinBox *colummCountspinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SelectDialog)
    {
        if (SelectDialog->objectName().isEmpty())
            SelectDialog->setObjectName(QStringLiteral("SelectDialog"));
        SelectDialog->resize(402, 138);
        verticalLayout = new QVBoxLayout(SelectDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(SelectDialog);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        rowCountspinBox = new QSpinBox(SelectDialog);
        rowCountspinBox->setObjectName(QStringLiteral("rowCountspinBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, rowCountspinBox);


        verticalLayout->addLayout(formLayout);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_2 = new QLabel(SelectDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_2);

        colummCountspinBox = new QSpinBox(SelectDialog);
        colummCountspinBox->setObjectName(QStringLiteral("colummCountspinBox"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, colummCountspinBox);


        verticalLayout->addLayout(formLayout_2);

        buttonBox = new QDialogButtonBox(SelectDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SelectDialog);

        QMetaObject::connectSlotsByName(SelectDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectDialog)
    {
        SelectDialog->setWindowTitle(QApplication::translate("SelectDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("SelectDialog", "RowCount", nullptr));
        label_2->setText(QApplication::translate("SelectDialog", "ColummCount", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectDialog: public Ui_SelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTDIALOG_H
