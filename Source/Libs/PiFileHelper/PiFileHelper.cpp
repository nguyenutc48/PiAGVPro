#include "PiFileHelper.h"

QMutex PiFileHelper:: _mutex_FileHelper;
PiFileHelper::PiFileHelper()
{
}

bool PiFileHelper::SetValueSetting(QString qstrFileName, QString qstrGroup, QString qstrKey, QString qstrValue)
{
    QMutexLocker locker(&_mutex_FileHelper);
    if(qstrFileName.size() <= 0 || qstrGroup.size() <= 0 || qstrKey.size() <= 0)
    {
        return false;
    }
    if(!QFile(QString::fromLatin1("/home/pi/PiAGVPro/Settings/") + qstrFileName + ".ini").exists())
    {
        return false;
    }
    try
    {
        QSettings settings(QString::fromLatin1("/home/pi/PiAGVPro/Settings/") + qstrFileName + ".ini", QSettings::IniFormat);
        settings.beginGroup(qstrGroup);
        if(!settings.contains(qstrKey))
        {
            settings.endGroup();
            return false;
        }
        settings.setValue(qstrKey, qstrValue);
        settings.endGroup();
    }
    catch (QException &)
    {
        return false;
    }
    return true;
}

QString PiFileHelper::GetValueSetting(QString qstrFileName, QString qstrGroup, QString qstrKey)
{
    QMutexLocker locker(&_mutex_FileHelper);
            if(qstrFileName.size() <= 0 || qstrGroup.size() <= 0 || qstrKey.size() <= 0)
            {
                return "Input FileName or Group or Key ERROR";
            }
            if(!QFile(QString::fromLatin1("/home/pi/PiAGVPro/Settings/") + qstrFileName + ".ini").exists())
            {
                return "Path Incorectly";
            }
            QString qResult = "";
            try
            {
                QSettings settings(QString::fromLatin1("/home/pi/PiAGVPro/Settings/") + qstrFileName + ".ini", QSettings::IniFormat);
                settings.beginGroup(qstrGroup);
                if(!settings.contains(qstrKey))
                {
                    settings.endGroup();
                    return "Input Key Error";
                }
                qResult = settings.value(qstrKey).toString();
                settings.endGroup();
            }
            catch (QException &)
            {
                return "ex";
            }
            qResult = qResult.trimmed();
            return qResult;
}

QStringList PiFileHelper::GetListValueSetting(QString qstrFileName, QString qstrGroup, QString qstrKey)
{
    QMutexLocker locker(&_mutex_FileHelper);
    QString qResult = "";
    QStringList     listValueResult;
    if(qstrFileName.size() <= 0 || qstrGroup.size() <= 0 || qstrKey.size() <= 0)
    {
        qResult = "Input FileName or Group or Key ERROR";
    }
    else
    {
        if(QFile(QString::fromLatin1("/home/pi/PiAGVPro/Settings/") + qstrFileName + ".ini").exists())
        {
            try
            {
                QSettings settings(QString::fromLatin1("/home/pi/PiAGVPro/Settings/") + qstrFileName + ".ini", QSettings::IniFormat);
                settings.beginGroup(qstrGroup);
                if(!settings.contains(qstrKey))
                {
                    settings.endGroup();
                    qResult = "Input Key Error";
                }
                else
                {
                    qResult = settings.value(qstrKey).toString();
                    settings.endGroup();
                }
            }
            catch (QException &)
            {
                qResult = "ERROR_";
            }
        }
        else
        {
            qResult = "Path Incorectly";
        }
    }
    qResult = qResult.trimmed();
    listValueResult = qResult.split('_',QString::SkipEmptyParts);
    return listValueResult;
}

bool PiFileHelper::WriteLogFile(QString qstrFileName, QString qstrText)
{
    return  WriteLogFile(qstrFileName, qstrText, false);
}
bool PiFileHelper::WriteLogFile(QString qstrFileName, QString qstrText, bool bInsertHead)
{

    QMutexLocker locker(&_mutex_FileHelper);
    if(qstrFileName.size() <= 0)
    {
        return false;
    }
    try
    {
        QFile file(QString::fromLatin1("/home/pi/PiAGVPro/Logs/") + qstrFileName + ".txt");
        if(bInsertHead)
        {
            if(file.exists())
            {
                if(file.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    QTextStream   in(&file);
                    QString oldText = in.readAll();
                    qstrText = qstrText + "\r\n" + oldText;
                    file.close();
                }
                else
                {
                    return false;
                }
                file.remove();
                if(file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    file.write(qstrText.toUtf8());
                    file.close();
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if(file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    file.write(qstrText.toUtf8());
                    file.close();
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            if(file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                file.write(qstrText.toUtf8());
                file.close();
            }
            else
            {
                return false;
            }
        }
    }
    catch (QException &)
    {
        return false;
    }
    return true;
}

