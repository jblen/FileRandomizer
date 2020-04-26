#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum {
        COLUMN_NAME,
        COLUMN_DATE,
        COLUMN_FIXED,
        MAX_COLUMN_NUMBER
    };
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    QString GetRowName(int a_row) const;
    bool IsRowFixed(int a_row) const;
    int FixedRowsCount() const;
    void AddFilesToTable(QStringList &a_filesToInsert);    
    void UpdateColumnsWidth();
    void MoveSelectedRow(bool a_Up);
private slots:
    void on_actionNew_project_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_project_triggered();

    void on_actionSave_as_triggered();

    void on_btnAddFiles_clicked();

    void on_btnBrowseOutputFld_clicked();

    void on_action_Randomize_triggered();

    void on_btnAddFolder_clicked();

    void on_btnDeleteItems_clicked();

    void on_btnMoveUp_clicked();

    void on_btnMoveDown_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
