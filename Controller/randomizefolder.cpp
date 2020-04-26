#include "randomizefolder.h"
#include <QDir>
#include <QFile>

CRandomizeFolder::CRandomizeFolder(QObject *parent) : QObject(parent)
{
    m_workingFolder = tr("");
}

bool CRandomizeFolder::Randomize()
{
    bool result = DoRandomize();
    return result;
}

bool CRandomizeFolder::DoRandomize()
{
    bool result = false;
    QString tempFolder = FindNewTempFolder();
    if (!tempFolder.isEmpty())
    {
        //assume the directory exists and contains some files
        QStringList filesToInsert = QDir(m_workingFolder).entryList(QDir::Files);
        MoveFilesToFolder(filesToInsert, tempFolder, true);


    }
    return result;
}

QString CRandomizeFolder::FindNewTempFolder()
{
#define MAX_CNT 1000
    QString result = "";
    if (QDir(m_workingFolder).exists())
    {
        QString tempName = tr("temp");
        int iCnt = 0;
        while ((++iCnt < MAX_CNT) && QDir(m_workingFolder + tempName).exists())
        {
            tempName = tr("temp") + QString(iCnt);
        }
        if (iCnt < MAX_CNT)
        result = m_workingFolder + tempName;
    }
    return result;
}

bool CRandomizeFolder::MoveFilesToFolder(const QStringList &a_filesToInsert, const QString &a_destFolder, bool a_rename)
{
    bool result = false;
    if (QDir().mkpath(a_destFolder))
    {
        //QFile
    }
    return result;
}
