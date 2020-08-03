#ifndef PIFILEHELPER_H
#define PIFILEHELPER_H
#include <QMutex>
#include <QMutexLocker>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QException>
#include <QSettings>
#include <QTextStream>
#include "pifilehelper_global.h"

class PIFILEHELPERSHARED_EXPORT PiFileHelper
{

public:
    PiFileHelper();
    //success return true
    bool    SetValueSetting(QString qstrFileName ,QString qstrGroup, QString qstrKey,QString qstrValue);
    QString GetValueSetting(QString qstrFileName,QString qstrGroup, QString strKey);
    QStringList GetListValueSetting(QString qstrFileName, QString qstrGroup, QString qstrKey);
    bool    WriteLogFile(QString qstrFileName, QString qstrText);
    bool    WriteLogFile(QString qstrFileName, QString qstrText,bool bInsertHead);

public:
    static QMutex _mutex_FileHelper;
};

#endif // PIFILEHELPER_H
