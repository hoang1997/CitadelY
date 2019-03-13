#include "environment.h"
#include "ui_environment.h"

environment::environment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::environment)
{
    ui->setupUi(this);
}

environment::~environment()
{
    delete ui;
}

void environment::setTreeWidget(asset* a)
{
    QTreeWidgetItem *as = new QTreeWidgetItem(ui->treeWidget);
    ui->treeWidget->addTopLevelItem(as);
    as->setText(0, a->getName());
    QTreeWidgetItem *layer = new QTreeWidgetItem(as);
    layer->setText(0, "Layers");

    for(int i=0; i<a->getIPSPs().length(); i++)
    {
        QTreeWidgetItem *ipsp = new QTreeWidgetItem(layer);
        ipsp->setText(0, "Layer " + QString::number(i) + ": " + a->getIPSPs()[i]->getName());


            QTreeWidgetItem *type = new QTreeWidgetItem(ipsp);
            type->setText(0, a->getIPSPs()[i]->getType());
            QTreeWidgetItem *PFD = new QTreeWidgetItem(ipsp);
            PFD->setText(0, QString::number(a->getIPSPs()[i]->getPFD()));

    }
}

void environment::setTreeWidgetIPSP(ipsp* l)
{
    QTreeWidgetItem *layer = new QTreeWidgetItem(ui->treeWidget_2);
    ui->treeWidget->addTopLevelItem(layer);
    layer->setText(0, l->getName());
    QTreeWidgetItem *pfd = new QTreeWidgetItem(layer);
    QTreeWidgetItem *type = new QTreeWidgetItem(layer);
    pfd->setText(0, QString::number(l->getPFD()));
    type->setText(0, l->getType());
}

void environment::on_pushButton_clicked()
{
    as = new asset();
    connect(as, SIGNAL(assetSignal(asset*)),this,SLOT(addAsset(asset*)),Qt::UniqueConnection);
    connect(as, SIGNAL(assetSignal(asset*)),this,SLOT(setTreeWidget(asset*)),Qt::UniqueConnection);
    as->setModal(true);
    as->exec();
}

void environment::on_cancelButton_clicked()
{
    this->close();
}

void environment::addAsset(asset* as)
{
    assetArr.push_back(as);
}

void environment::addOuterIPSP(ipsp* outerIPSP)
{
    outerIPSParr.push_back(outerIPSP);
}


void environment::on_addIPSP_clicked()
{
    ip = new ipsp();
    connect(ip, SIGNAL(ipspSignal(ipsp*)),this,SLOT(addOuterIPSP(ipsp*)),Qt::UniqueConnection);
    connect(ip, SIGNAL(ipspSignal(ipsp*)),this,SLOT(setTreeWidgetIPSP(ipsp*)),Qt::UniqueConnection);

    ip->setModal(true);
    ip->exec();
}

void environment::on_createButton_clicked()
{
    emit envSignal(assetArr, outerIPSParr);
    this->close();
}
