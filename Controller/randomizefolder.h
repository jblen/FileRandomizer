#ifndef CRANDOMIZEFOLDER_H
#define CRANDOMIZEFOLDER_H

#include <QObject>

class CRandomizeFolder : public QObject
{
    Q_OBJECT
public:
    explicit CRandomizeFolder(QObject *parent = nullptr);

    void SetWorkingFolder(const QString &a_folder) { m_workingFolder = a_folder; }
    bool Randomize();

protected:
    virtual bool DoRandomize();
    QString FindNewTempFolder();
    bool MoveFilesToFolder(const QStringList &a_filesToInsert, const QString &a_destFolder, bool a_rename);

private:
    QString m_workingFolder;
    // We could create filters here 'type of files to randomize'


};

#endif // CRANDOMIZEFOLDER_H
