#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAssetIPSP(QVector<asset *> a, QVector<ipsp *> o)
{
    outerIPSParr = o;
    assetArr = a;
}

void MainWindow::setTreeWidget(QVector<asset *> a, QVector<ipsp *>o)
{
    QTreeWidgetItem *assets = new QTreeWidgetItem(ui->treeWidget);
    assets->setText(0, "Inner IPSP");
    QTreeWidgetItem *outer = new QTreeWidgetItem(ui->treeWidget);
    outer->setText(0, "Outer IPSP");

    for(int i=0; i<a.length(); i++)
    {
        QTreeWidgetItem *asset = new QTreeWidgetItem(assets);
        asset->setText(0, a[i]->getName());

        for(int j = 0; j<a[i]->getIPSPs().length(); j++)
        {
            QTreeWidgetItem *ipsp = new QTreeWidgetItem(asset);
            QTreeWidgetItem *PFD = new QTreeWidgetItem(ipsp);
            QTreeWidgetItem *type = new QTreeWidgetItem(ipsp);
            ipsp->setText(0, a[i]->getIPSPs()[j]->getName());
            type->setText(0, a[i]->getIPSPs()[j]->getType());
            PFD->setText(0, QString::number((a[i]->getIPSPs()[j]->getPFD())));
        }
    }

    if(o.length()>0)
    {
        for(int i=0; i < o.length();i++)
        {
            QTreeWidgetItem *layer = new QTreeWidgetItem(outer);
            ui->treeWidget->addTopLevelItem(layer);
            layer->setText(0, o[i]->getName());
            QTreeWidgetItem *pfd = new QTreeWidgetItem(layer);
            QTreeWidgetItem *type = new QTreeWidgetItem(layer);
            pfd->setText(0, QString::number(o[i]->getPFD()));
            type->setText(0, o[i]->getType());
        }
    }
}

void MainWindow::on_createButton_clicked()
{
    env = new environment;
    connect(env, SIGNAL(envSignal(QVector<asset*>, QVector<ipsp*>)), this, SLOT(setAssetIPSP(QVector<asset*>, QVector<ipsp*>)), Qt::UniqueConnection);
    connect(env, SIGNAL(envSignal(QVector<asset*>, QVector<ipsp*>)), this, SLOT(setTreeWidget(QVector<asset*>, QVector<ipsp*>)), Qt::UniqueConnection);
    env->setModal(true);
    env->exec();
}
