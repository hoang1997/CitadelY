#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QPaintEvent>
#include <QGraphicsScene>
#include <QtMath>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    eval = new evaluate(this);
    connect(this, &MainWindow::tableDataSignal, eval, &evaluate::setTableData);
    connect(this, &MainWindow::tableDataSignal, eval, &evaluate::setLayerTableData);
    connect(this, &MainWindow::tableDataSignal, eval, &evaluate::setCalc);
    connect(this, &MainWindow::tableDataSignal, eval, &evaluate::setInitEventTreeWidget);
    connect(this, &MainWindow::tableDataSignal, eval, &evaluate::setTableData);
    connect(this, &MainWindow::diagramSignal, eval, &evaluate::setDiagram);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
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

void MainWindow::createGraphicsLayer(QVector<asset*> a, QVector<ipsp*> o)
{
    QVector<layerItem*> ipspArray;

    layerItem *rec;

    for(int i = o.length() - 1; i >= 0; i--) {
        rec = new layerItem(350 + (i * 50),350 + (i*50), o[i]->getName(), o[i]->getPFD());

        ipspArray.push_back(rec);
    }

    for(int i = 0; i < ipspArray.length(); i++) {
        if(i > 0)
        {
            ipspArray[i]->setParentItem(ipspArray[i-1]);
            ipspArray[i]->setBoundingRegionGranularity(ipspArray[i-1]->boundingRegionGranularity());
        }
        scene->addItem(ipspArray[i]);
    }

    for(int i = 0; i < a.length(); i++) {
        QVector<layerItem*> aArray;
        for(int j = a[i]->getIPSPs().length()-1; j >= 0; j--) {
            rec = new layerItem(75 + (j*20), 75 + (j*20), a[i]->getIPSPs()[j]->getName(), a[i]->getIPSPs()[j]->getPFD());
            if(j == a[i]->getIPSPs().length()-1 && ipspArray.length() > 0)
            {
                rec->setParentItem(ipspArray[ipspArray.length()-1]);
            }
            aArray.push_back(rec);
        }

        for(int i = 0; i < aArray.length(); i++) {
            if(i > 0)
            {
                aArray[i]->setParentItem(aArray[i-1]);
            }
            scene->addItem(aArray[i]);
        }

        rec = new layerItem(50, 50,a[i]->getName(), 11);
        rec->setParentItem(aArray[aArray.length()-1]);
        scene->addItem(rec);


    }

}

void MainWindow::on_createButton_clicked()
{
    env = new environment;
    connect(env, SIGNAL(envSignal(QVector<asset*>, QVector<ipsp*>)), this, SLOT(setAssetIPSP(QVector<asset*>, QVector<ipsp*>)), Qt::UniqueConnection);
    connect(env, SIGNAL(envSignal(QVector<asset*>, QVector<ipsp*>)), this, SLOT(setTreeWidget(QVector<asset*>, QVector<ipsp*>)), Qt::UniqueConnection);
    connect(env, SIGNAL(envSignal(QVector<asset*>, QVector<ipsp*>)), this, SLOT(createGraphicsLayer(QVector<asset*>, QVector<ipsp*>)), Qt::UniqueConnection);
    env->setModal(true);
    env->show();
}

void MainWindow::on_evaluateButton_clicked()
{
    if(assetArr.length() == 0 || outerIPSParr.length() == 0) {
        displayError("ERROR:\n\nAsset or Outer IPSP seems to be missing");
    } else {
        eval->setModal(true);
        QPixmap *pixmap = new QPixmap;
        *pixmap = ui->graphicsView->grab();
        emit diagramSignal(*pixmap);
        emit tableDataSignal(assetArr, outerIPSParr);
        eval->show();
    }
}

void MainWindow::on_actionTable_Reference_triggered()
{
    r = new referenceTable();
    r->setModal(true);
    r->show();
}

void MainWindow::displayError(QString errorMessage){

    QMessageBox::StandardButton error;
    error = QMessageBox::information(this,"ERROR:", errorMessage);

}
