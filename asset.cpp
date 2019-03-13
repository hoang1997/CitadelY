#include "asset.h"
#include "ui_asset.h"

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

QVector<ipsp*> asset::getIPSPs()
{
    return ipspArr;
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
    emit assetSignal(this);
    this->close();
}
