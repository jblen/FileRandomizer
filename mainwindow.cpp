#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDateTime>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateColumnsWidth()
{
    QTableWidget *tableW = ui->tableWidget;
    QRect tableRect = tableW->geometry();
    int iWidth = tableRect.width();
    tableW->setColumnWidth(COLUMN_NAME, iWidth * 0.58);
    tableW->setColumnWidth(COLUMN_DATE, iWidth * 0.28);
    tableW->setColumnWidth(COLUMN_FIXED, iWidth * 0.03);
}

QString MainWindow::GetRowName(int a_row) const
{
    QString result;
    QTableWidget *tableW = ui->tableWidget;
    QTableWidgetItem *tableItem = tableW->item(a_row, COLUMN_NAME);
    result = tableItem->text();
    return result;
}

bool MainWindow::IsRowFixed(int a_row) const
{
    bool result;
    QTableWidgetItem *tableItem = ui->tableWidget->item(a_row, COLUMN_FIXED);
    result = tableItem->checkState() == Qt::Checked;
    return result;
}

int MainWindow::FixedRowsCount() const
{
    int fixedRows = 0;
    QTableWidget *tableW = ui->tableWidget;
    for (int i = 0; i < tableW->rowCount(); ++i)
    {
        if (tableW->item(i, COLUMN_FIXED)->checkState() == Qt::Checked)
        {
            ++fixedRows;
        }

    }
    return fixedRows;
}

void MainWindow::on_actionNew_project_triggered()
{
    // Do the "New project" stuff

}

void MainWindow::on_actionOpen_triggered()
{
    // Do the "Open project" stuff

}

void MainWindow::on_actionSave_project_triggered()
{
    // Do the "Save project" stuff

}

void MainWindow::on_actionSave_as_triggered()
{
    // Do the "SaveAs..." stuff

}

void MainWindow::AddFilesToTable(QStringList &a_filesToInsert )
{
    //FileIOUtil::mvFile(dest, outFileName,
    QTableWidget *tableW = ui->tableWidget;
    for (QString &fileToInsert : a_filesToInsert ) {
        if (tableW->findItems(fileToInsert, Qt::MatchFlags(Qt::MatchExactly)).empty())
        {
            int irow = tableW->rowCount();
            tableW->setRowCount(irow + 1);
            QTableWidgetItem *tableItem = new QTableWidgetItem(fileToInsert);
            tableItem->setText(fileToInsert);
            //tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable );
            tableW->setItem(irow, COLUMN_NAME, tableItem);

            QDateTime fileDate = QFileInfo(fileToInsert).lastModified();
            tableItem = new QTableWidgetItem(fileDate.toString());
            tableW->setItem(irow, COLUMN_DATE, tableItem);

            tableItem = new QTableWidgetItem();
            tableItem->setFlags((tableItem->flags() | Qt::ItemIsUserCheckable) & ~Qt::ItemIsEditable );
            tableItem->setCheckState(Qt::Unchecked);
            tableItem->setTextAlignment(Qt::AlignHCenter);
            tableW->setItem(irow, COLUMN_FIXED, tableItem);
        }
    }
    UpdateColumnsWidth();
}

void MainWindow::on_btnAddFiles_clicked()
{
    QStringList filesToInsert = QFileDialog::getOpenFileNames(this, tr("Select one or more files to open"));
    AddFilesToTable(filesToInsert);
}

void MainWindow::on_btnBrowseOutputFld_clicked()
{
    QString outputFolder = QFileDialog::getExistingDirectory(this, tr("Select output folder"));
    if (!outputFolder.isEmpty())
    {
        ui->edtOutPutFolder->setText(outputFolder);
    }
}

void MainWindow::on_btnAddFolder_clicked()
{
    QString strFolder = QFileDialog::getExistingDirectory(this, tr("Select folder to import"));
    if (!strFolder.isEmpty())
    {
        //assume the directory exists and contains some files
        QStringList filesToInsert = QDir(strFolder).entryList(QDir::Files);
        AddFilesToTable(filesToInsert);
    }
}

void MainWindow::on_action_Randomize_triggered()
{
    // Do the thing

}

void MainWindow::on_btnDeleteItems_clicked()
{
    QTableWidget *tableW = ui->tableWidget;
    QList<QTableWidgetItem *> selectedItems = tableW->selectedItems();
    if (!selectedItems.isEmpty())
    {
        tableW->removeRow(selectedItems[0]->row());
    }

}

void MainWindow::MoveSelectedRow(bool a_Up)
{
    QTableWidget *tableW = ui->tableWidget;
    int iCurrentRow = tableW->currentRow();
    if (iCurrentRow > -1)
    {
        int irow = iCurrentRow;
        bool doIt;
        int iStep = 0;
        if (a_Up)
        {
            doIt = irow > 0;
            iStep = -1;
        }
        else
        {
            doIt = irow < (tableW->rowCount() - 1);
            iStep = +1;
        }

        if (doIt)
        {
          QStandardItemModel *item = qobject_cast<QStandardItemModel *>(tableW->model());

          int iNewRow = iCurrentRow + iStep;
          QList<QStandardItem *> list = item->takeRow(iCurrentRow) ;
          item->insertRow(iNewRow, list);
        }
    }
}

void MainWindow::on_btnMoveUp_clicked()
{
    MoveSelectedRow(true);
}

void MainWindow::on_btnMoveDown_clicked()
{
    MoveSelectedRow(false);
}
