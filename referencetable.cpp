#include "referencetable.h"
#include "ui_referencetable.h"

referenceTable::referenceTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::referenceTable)
{
    ui->setupUi(this);
}

referenceTable::~referenceTable()
{
    delete ui;
}
