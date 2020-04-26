#ifndef STATUSFORM_H
#define STATUSFORM_H

#include <QDialog>

namespace Ui {
class CStatusForm;
}

class CStatusForm : public QDialog
{
    Q_OBJECT

public:
    explicit CStatusForm(QWidget *parent = nullptr);
    ~CStatusForm();

private:
    Ui::CStatusForm *ui;
};

#endif // STATUSFORM_H
