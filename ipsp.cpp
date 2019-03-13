#include "ipsp.h"
#include "ui_ipsp.h"

ipsp::ipsp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ipsp)
{
    ui->setupUi(this);
    QStringList list = (QStringList()<<"Active"<< "Passive");
    ui->typeBox->addItems(list);
}

ipsp::~ipsp()
{
    delete ui;
}

void ipsp::setIPSP()
{
    name = ui->ipspName->text();
    PFD = ui->PFDspinBox->value();
    type = ui->typeBox->currentText();
}

int ipsp::getPFD() {
    return PFD;
}

QString ipsp::getName(){
    return name;
}

QString ipsp::getType(){
    return type;
}

void ipsp::on_closeButton_clicked()
{
    this->close();
}

void ipsp::on_addButton_clicked()
{
    setIPSP();
    emit ipspSignal(this);
    this->close();
}
