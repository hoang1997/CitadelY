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

    double mean = 0;
    double sumOfSD = 0;
    double sd = 0;
    double upper = mean + sd;
    double lower = mean - sd;
    double sumOfCredits = 0;
    double avPFD = 0;
    double avRisk = 0;
    double rRisk = 0;
};

#endif // EVALUATE_H
