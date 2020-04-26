#include "statusform.h"
#include "ui_statusform.h"

CStatusForm::CStatusForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CStatusForm)
{
    ui->setupUi(this);
}

CStatusForm::~CStatusForm()
{
    delete ui;
}
