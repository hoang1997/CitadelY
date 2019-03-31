#include "asset.h"
#include "ui_asset.h"
#include <QtMath>
#include <QMessageBox>
asset::asset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::asset)
{
    ui->setupUi(this);
}

asset::~asset()
{
    delete ui;
}

void asset::setName()
{
    name = ui->lineEdit->text();
}

QString asset::getName()
{
    return name;
}

void asset::setSeverity()
{
    severity = ui->spinBox->value();
}

int asset::getSeverity()
{
    return severity;
}

double asset::getCredits()
{
    double sum=0.0;
    for(int i = 0; i < ipspArr.length(); i++){
       double credit = -(qLn(ipspArr[i]->getPFD()));
       sum += credit;
    }
    return sum;
}

QVector<ipsp*> asset::getIPSPs()
{
    return ipspArr;
}

QString asset::getDamageLevel()
{
    if(severity >= 0 && severity <= 2) {
        return "ACCEPTABLE";
    }
    else if(severity > 2 && severity <=4) {
        return "LIMITED";
    }
    else if(severity > 4 && severity <=6) {
        return "MODERATE";
    }
    else if(severity > 6 && severity <= 8) {
        return "HIGH";
    }
    else if(severity > 8 && severity <= 10) {
        return "SEVERE";
    } else return "NULL";
}

int asset::getRSS()
{
    int sum = 0;
    for(int i = 0; i < ipspArr.length();i++)
        sum+=ipspArr[i]->getPFD();

    return (sum/ipspArr.length())*10;
}

void asset::addIPSP(ipsp* ip)
{
    ipspArr.push_back(ip);
}

void asset::setTreeWidget(ipsp* l)
{
    QTreeWidgetItem *layer = new QTreeWidgetItem(ui->treeWidget);
    ui->treeWidget->addTopLevelItem(layer);
    layer->setText(0, l->getName());
    QTreeWidgetItem *pfd = new QTreeWidgetItem(layer);
    QTreeWidgetItem *type = new QTreeWidgetItem(layer);
    pfd->setText(0, QString::number(l->getPFD()));
    type->setText(0, l->getType());
}

void asset::on_pushButton_clicked()
{
    ps = new ipsp;
    connect(ps, SIGNAL(ipspSignal(ipsp*)),this,SLOT(addIPSP(ipsp*)),Qt::UniqueConnection);
    connect(ps, SIGNAL(ipspSignal(ipsp*)),this,SLOT(setTreeWidget(ipsp*)),Qt::UniqueConnection);
    ps->setModal(true);
    ps->exec();
}

void asset::on_cancelButton_clicked()
{
    this->close();
}


void asset::on_createButton_clicked()
{
    setName();
    setSeverity();
    if(name == " ") {
        QMessageBox::StandardButton error;
        error = QMessageBox::information(this,"ERROR:", "ERROR:\n\n Must Create Asset Name");
    }
    else if(ipspArr.size() == 0 ) {
        QMessageBox::StandardButton error;
        error = QMessageBox::information(this,"ERROR:", "ERROR:\n\nIPSP's Surrounding Asset has not been created");
    }
    else if(severity == 0 ) {
        QMessageBox::StandardButton error;
        error = QMessageBox::information(this,"ERROR:", "ERROR:\n\nMust Add Severity Level");
    }
    else if(initEvents.size() == 0) {
        QMessageBox::StandardButton error;
        error = QMessageBox::information(this,"ERROR:", "ERROR:\n\nNo Inititiating Event");
    }
    else {
        emit assetSignal(this);
        this->close();
    }
}

void asset::addInitEvents(attacker* initEvent) {
    initEvents.push_back(initEvent);
}

QVector<attacker*> asset::getInitEvents() {
    return initEvents;
}

int asset::getAvRisk()
{
    if(initEvents.length() > 1)
    {
        for(int i = 0; i < initEvents.length(); i++){
            avLike += initEvents[i]->getLike();
        }


        avLike = avLike / initEvents.length();
        return avLike;
    } else {
        return initEvents[0]->getLike();
    }
}
void asset::on_pushButton_2_clicked()
{
    iEvent = new initEvent(this);
    connect(iEvent, SIGNAL(attackerSignal(attacker*)),this,SLOT(addInitEvents(attacker*)),Qt::UniqueConnection);
    iEvent->setModal(true);
    iEvent->show();
}
