#ifndef EVALUATE_H
#define EVALUATE_H

#include <QDialog>
#include "asset.h"
#include "ipsp.h"
#include <QGraphicsScene>
namespace Ui {
class evaluate;
}

class evaluate : public QDialog
{
    Q_OBJECT

public:
    explicit evaluate(QWidget *parent = nullptr);
    ~evaluate();

    void setDiagram(QPixmap);

public slots:
    void setTableData(QVector<asset*>, QVector<ipsp*>);
    void setLayerTableData(QVector<asset*>, QVector<ipsp*>);
    void setInitEventTreeWidget(QVector<asset*>, QVector<ipsp*>);
    void setCalc(QVector<asset*>, QVector<ipsp*>);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::evaluate *ui;
    QVector<asset*> assetArr;
    QVector<ipsp*> outerArray;
    QGraphicsScene *scene;
    QPixmap pixmap;

    double mean;
    double sumOfSD;
    double sd;
    double upper;
    double lower;
    double sumOfCredits;
    double avPFD;
    double avRisk;
    double rRisk;
};

#endif // EVALUATE_H
