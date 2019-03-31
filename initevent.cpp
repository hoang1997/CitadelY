#include "initevent.h"
#include "ui_initevent.h"

initEvent::initEvent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initEvent)
{
    ui->setupUi(this);
    QStringList list = (QStringList() << "None"<<"Insider Threat" << "Burglary" << "Natural Disaster");
    ui->comboBox->addItems(list);
}

initEvent::~initEvent()
{
    delete ui;
}

void initEvent::on_pushButton_clicked()
{
    this->close();

}

attacker::attacker(QString Name, int Likeliness, QString Description) {
    name = Name;
    likeliness = Likeliness;
    description = Description;
}

QString attacker::getName()
{
    return name;
}

int attacker::getLike()
{
    return likeliness;
}

QString attacker::getDesc() {
    return description;
}

attacker* initEvent::createAttacker(QString n, int l, QString d) {
    threat = new attacker(n, l, d);

    return threat;
}

void initEvent::on_pushButton_2_clicked()
{
    if(ui->tabWidget->currentIndex() == 0)
    {
        if(ui->comboBox->currentText() == "None") {
            this->close();
        }
        else if(ui->comboBox->currentText() == "Insider Threat") {
            emit(attackerSignal(createAttacker("Insider Threat", 7, "Insider threat such as a cleaner or disgruntled employee")));
            this->close();
        }
        else if(ui->comboBox->currentText() == "Burglary") {
            emit(attackerSignal(createAttacker("Burglary", 6, "Burglary of certain assets with high value")));
            this->close();
        }
        else if(ui->comboBox->currentText() == "Natural Disaster") {
            emit(attackerSignal(createAttacker("Natural Disaster", 3, "Natural disaster such as storms or heavy rain etc.")));
            this->close();
        }


    }
    else if(ui->tabWidget->currentIndex() == 1)
    {
        emit(attackerSignal(createAttacker(ui->lineEdit->text(), ui->spinBox->value(), ui->plainTextEdit->toPlainText())));
        this->close();
    }
}

