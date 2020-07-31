/********************************************************************************
** Form generated from reading UI file 'Application.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLICATION_H
#define UI_APPLICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Application
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionClose;
    QWidget *centralWidget;
    QPushButton *BntReadFileini;
    QPushButton *BntWriteFileini;
    QPushButton *BntReadFilecsv;
    QPushButton *BntWriteFilecsv;
    QPlainTextEdit *PlanTextEdit;
    QPushButton *BntReadAllini;
    QLineEdit *lineEdit;
    QTableView *tableView;
    QMenuBar *menuBar;
    QMenu *menuOpen;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Application)
    {
        if (Application->objectName().isEmpty())
            Application->setObjectName(QStringLiteral("Application"));
        Application->resize(470, 356);
        actionOpen = new QAction(Application);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(Application);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionClose = new QAction(Application);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        centralWidget = new QWidget(Application);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BntReadFileini = new QPushButton(centralWidget);
        BntReadFileini->setObjectName(QStringLiteral("BntReadFileini"));
        BntReadFileini->setGeometry(QRect(20, 20, 91, 30));
        BntWriteFileini = new QPushButton(centralWidget);
        BntWriteFileini->setObjectName(QStringLiteral("BntWriteFileini"));
        BntWriteFileini->setGeometry(QRect(20, 60, 91, 30));
        BntReadFilecsv = new QPushButton(centralWidget);
        BntReadFilecsv->setObjectName(QStringLiteral("BntReadFilecsv"));
        BntReadFilecsv->setGeometry(QRect(20, 140, 91, 30));
        BntWriteFilecsv = new QPushButton(centralWidget);
        BntWriteFilecsv->setObjectName(QStringLiteral("BntWriteFilecsv"));
        BntWriteFilecsv->setGeometry(QRect(20, 180, 91, 30));
        PlanTextEdit = new QPlainTextEdit(centralWidget);
        PlanTextEdit->setObjectName(QStringLiteral("PlanTextEdit"));
        PlanTextEdit->setGeometry(QRect(150, 60, 201, 31));
        BntReadAllini = new QPushButton(centralWidget);
        BntReadAllini->setObjectName(QStringLiteral("BntReadAllini"));
        BntReadAllini->setGeometry(QRect(20, 100, 91, 30));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(150, 20, 201, 30));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(150, 100, 256, 192));
        Application->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Application);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 470, 27));
        menuOpen = new QMenu(menuBar);
        menuOpen->setObjectName(QStringLiteral("menuOpen"));
        Application->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Application);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Application->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Application);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Application->setStatusBar(statusBar);

        menuBar->addAction(menuOpen->menuAction());
        menuOpen->addSeparator();
        menuOpen->addSeparator();
        menuOpen->addAction(actionOpen);
        menuOpen->addAction(actionSave);
        menuOpen->addAction(actionClose);

        retranslateUi(Application);

        QMetaObject::connectSlotsByName(Application);
    } // setupUi

    void retranslateUi(QMainWindow *Application)
    {
        Application->setWindowTitle(QApplication::translate("Application", "Application", nullptr));
        actionOpen->setText(QApplication::translate("Application", "Open", nullptr));
        actionSave->setText(QApplication::translate("Application", "Save", nullptr));
        actionClose->setText(QApplication::translate("Application", "Close", nullptr));
        BntReadFileini->setText(QApplication::translate("Application", "ReadFIle.ini", nullptr));
        BntWriteFileini->setText(QApplication::translate("Application", "WriteFIle.ini", nullptr));
        BntReadFilecsv->setText(QApplication::translate("Application", "ReadFIle.csv", nullptr));
        BntWriteFilecsv->setText(QApplication::translate("Application", "WriteFIle.csv", nullptr));
        BntReadAllini->setText(QApplication::translate("Application", "ReadAll.ini", nullptr));
        menuOpen->setTitle(QApplication::translate("Application", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Application: public Ui_Application {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLICATION_H
