#include "evaluate.h"
#include "ui_evaluate.h"
#include <QFileDialog>
#include <stdio.h>
#include <math.h>
#include <QDebug>
#include <QTreeWidgetItem>
#include <iomanip>
//r = tf * (likelihood  - sum(credits(ipl)))
evaluate::evaluate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::evaluate)
{
    ui->setupUi(this);
    QStringList columnHeaders;
    QStringList columnHeaders2;
    columnHeaders << "Target" << "Possible Damage" << "Risk"<<"Residual Risk" << "Current IPSPs Performance " <<"Recommended IPSPs Performance";
    columnHeaders2 << "Layer" <<  "PFD" << "Credits" << "Investigate";
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget_2->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(columnHeaders);
    ui->tableWidget_2->setHorizontalHeaderLabels(columnHeaders2);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

evaluate::~evaluate()
{
    delete ui;
}

void evaluate::setTableData(QVector<asset*> a, QVector<ipsp*> o) {

    ui->tableWidget->setRowCount(a.size());

    assetArr = a;
    outerArray = o;
    for(int i = 0; i < a.size(); i++)
    {
        ui->tableWidget_2->setRowCount(a[i]->getIPSPs().length());
        double outerCredits = 0;
        for(int j = 0; j < o.length(); j++) {
            outerCredits += o[j]->getPFD();
        }
        outerCredits = outerCredits/o.length();

        avRisk = a[i]->getAvRisk() * a[i]->getSeverity();
        rRisk = avRisk + a[i]->getCredits() + outerCredits;



        QTableWidgetItem *target = new QTableWidgetItem(tr("%1").arg((i+1)*(i+1)));
        QTableWidgetItem *pDamage = new QTableWidgetItem(tr("%1").arg((i+1)*(i+1)));
        QTableWidgetItem *r = new QTableWidgetItem(tr("%1").arg((i+1)*(i+1)));
        QTableWidgetItem *rr = new QTableWidgetItem(tr("%1").arg((i+1)*(i+1)));
        QTableWidgetItem *aLevel = new QTableWidgetItem(tr("%1").arg((i+1)*(i+1)));
        QTableWidgetItem *rLevel = new QTableWidgetItem(tr("%1").arg((i+1)*(i+1)));
        target->setText(a[i]->getName());
        pDamage->setText(a[i]->getDamageLevel());
        if(avRisk < 20) {
            r->setText("LIMITED");
        }
        else if (avRisk >= 20 && avRisk < 40) {
            r->setText("ACCEPTABLE");
        }
        else if(avRisk >= 40 && avRisk < 60) {
            r->setText("MODERATE");
        }
        else if(avRisk >= 60 && avRisk < 80) {
            r->setText("HIGH");
        }
        else if(avRisk >= 80 && avRisk <= 100) {
            r->setText("SEVERE");
        }

        if(rRisk < 20) {
            rr->setText("LIMITED");
        }
        else if (rRisk >= 20 && rRisk < 40) {
            rr->setText("ACCEPTABLE");
        }
        else if(rRisk >= 40 && rRisk < 60) {
            rr->setText("MODERATE");
        }
        else if(rRisk >= 60 && rRisk < 80) {
            rr->setText("HIGH");
        }
        else if(rRisk >= 80 && rRisk <= 100) {
            rr->setText("SEVERE");
        }

        aLevel->setText(QString::number(mean * 10)+"%");
        if(a[i]->getSeverity() % 2 == 0) {
            rLevel->setText(QString::number(a[i]->getSeverity()/2));
        }
        else {rLevel->setText(QString::number(ceil(a[i]->getSeverity()/2)));}
        ui->tableWidget->setItem(i, 0, target);
        ui->tableWidget->setItem(i, 1, pDamage);
        ui->tableWidget->setItem(i, 2, r);
        ui->tableWidget->setItem(i, 3, rr);
        ui->tableWidget->setItem(i, 4, aLevel);
        ui->tableWidget->setItem(i, 5, rLevel);


        qDebug()<<"Standard deviation " << sd;



    }
}

void evaluate::setLayerTableData(QVector<asset *> a, QVector<ipsp *>outer)
{
    for(int i = 0; i < a.length(); i++)
    {
        for(int j = 0; j < a[i]->getIPSPs().length(); j++)
        {
            QTableWidgetItem *layer = new QTableWidgetItem(tr("%1").arg((j+1)*(j+1)));
            QTableWidgetItem *PFD = new QTableWidgetItem(tr("%1").arg((j+1)*(j+1)));
            QTableWidgetItem *credits = new QTableWidgetItem(tr("%1").arg((j+1)*(j+1)));
            QTableWidgetItem *inv = new QTableWidgetItem(tr("%1").arg((j+1)*(j+1)));

            layer->setText(a[i]->getIPSPs()[j]->getName());
            PFD->setText(QString::number(a[i]->getIPSPs()[j]->getPFD()));
            credits->setText(QString::number(-log(a[i]->getIPSPs()[j]->getPFD())));
            if(a[i]->getIPSPs()[j]->getPFD() > upper || a[i]->getIPSPs()[j]->getPFD() < lower) {
                 inv->setText("YES");
            } else {inv->setText("NO");}

            ui->tableWidget_2->setItem(j, 0, layer);
            ui->tableWidget_2->setItem(j, 1, PFD);
            ui->tableWidget_2->setItem(j, 2, credits);
            ui->tableWidget_2->setItem(j, 3, inv);
        }
        for(int j = 0; j < outer.length(); j++) {
            QTableWidgetItem *layer = new QTableWidgetItem(tr("%1").arg((j+1)*(j+1)));
            QTableWidgetItem *PFD = new QTableWidgetItem(tr("%1").arg((j+1)*(j+1)));
            QTableWidgetItem *credits = new QTableWidgetItem(tr("%1").arg((j+1)*(j+1)));
            QTableWidgetItem *inv = new QTableWidgetItem(tr("%1").arg((j+1)*(j+1)));

            layer->setText(a[i]->getIPSPs()[j]->getName());
            PFD->setText(QString::number(a[i]->getIPSPs()[j]->getPFD()));
            credits->setText(QString::number(-log(a[i]->getIPSPs()[j]->getPFD())));
            if(a[i]->getIPSPs()[j]->getPFD() > upper || a[i]->getIPSPs()[j]->getPFD() < lower) {
                 inv->setText("YES");
            } else {inv->setText("NO");}

            ui->tableWidget_2->setItem(j, 0, layer);
            ui->tableWidget_2->setItem(j, 1, PFD);
            ui->tableWidget_2->setItem(j, 2, credits);
            ui->tableWidget_2->setItem(j, 3, inv);
        }
    }
}

void evaluate::setInitEventTreeWidget(QVector<asset *> a, QVector<ipsp *> o)
{
    ui->treeWidget->clear();
    for(int i = 0; i < a.length();i++ )
    {
        QTreeWidgetItem *as = new QTreeWidgetItem(ui->treeWidget);
        ui->treeWidget->addTopLevelItem(as);
        as->setText(0, a[i]->getName());

        for(int j=0; j < a[i]->getInitEvents().length(); j++)
        {
            QTreeWidgetItem *initEvent = new QTreeWidgetItem(as);
            initEvent->setText(0, "Initiating Event " + QString::number(j) + ": " + a[i]->getInitEvents()[j]->getName());


            QTreeWidgetItem *like = new QTreeWidgetItem(initEvent);
            like->setText(0, "Likeliness: " + QString::number(a[i]->getInitEvents()[j]->getLike()));
            QTreeWidgetItem *desc = new QTreeWidgetItem(initEvent);
            desc->setText(0, a[i]->getInitEvents()[j]->getDesc());

        }
    }
}

void evaluate::setCalc(QVector<asset *>a, QVector<ipsp *>o)
{
    avPFD = 0;
    sumOfCredits = 0;
    mean = 0;
    sumOfSD = 0;
    sd = 0;
    int sum = o.size();
    for(int i = 0; i < a.length(); i++)
    {
        for(int j = 0; j < a[i]->getIPSPs().length(); j++)
        {
           avPFD += a[i]->getIPSPs()[j]->getPFD();
           sumOfCredits += -log(a[i]->getIPSPs()[j]->getPFD());

        }
        for(int j = 0; j < o.length(); j++)
        {
            avPFD += o[j]->getPFD();
            sumOfCredits += -log(o[j]->getPFD());
        }
        sum += a[i]->getIPSPs().size();
    }

    mean = avPFD / sum;
    avPFD = avPFD / sum;

    for(int i = 0; i < a.length(); i++)
    {
        for(int j = 0; j < a[i]->getIPSPs().length(); j++)
        {
           sumOfSD += pow(a[i]->getIPSPs()[j]->getPFD() - mean, 2);

        }
        for(int j = 0; j < o.length(); j++)
        {
            sumOfSD += pow(o[j]->getPFD() - mean, 2);
        }

    }
    sd = sqrt(sumOfSD/sum - 1);
}

void evaluate::setDiagram(QPixmap image)
{
    scene->addPixmap(image);
    pixmap = image;
    scene->setSceneRect(scene->itemsBoundingRect());
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);

}

void evaluate::on_pushButton_2_clicked()
{
    this->close();
}

void evaluate::on_pushButton_clicked()
{
    QString fileLocationName = QFileDialog::getSaveFileName(this, "Save As", QDir::currentPath());
    QFile file(fileLocationName);
    pixmap.save(&file, "JPG",0);
}

void evaluate::on_pushButton_3_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save As" , QDir::currentPath());

    QFile file(filePath);

    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream data( &file );
        QStringList strList;
        for( int c = 0; c < ui->tableWidget->columnCount(); ++c )
        {
            strList  << ui->tableWidget->horizontalHeaderItem(c)->data(Qt::DisplayRole).toString() + "\t";
        }

        data << strList.join("") << "\n";
        for( int r = 0; r < ui->tableWidget->rowCount(); ++r )
        {
            strList.clear();
            for( int c = 0; c < ui->tableWidget->columnCount(); ++c )
            {   QTableWidgetItem* item = ui->tableWidget->item(r,c);        //Load items
                if (!item || item->text().isEmpty())                        //Test if there is something at item(r,c)
                {
                    ui->tableWidget->setItem(r,c,new QTableWidgetItem("0"));//IF there is nothing write 0
                }
                strList << ui->tableWidget->item( r, c )->text()+"\t";

            }
            data << strList.join("") +"\n";
        }

        file.close();
    }

}
