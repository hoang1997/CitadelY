#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QDialog>
#include "asset.h"

#include <QVector>


namespace Ui {
class environment;
}



class environment : public QDialog
{
    Q_OBJECT

public:
    explicit environment(QWidget *parent = nullptr);
    ~environment();

signals:
    void envSignal(QVector<asset*>, QVector<ipsp*>);
private slots:
    void on_pushButton_clicked();

    void on_cancelButton_clicked();

    void addAsset(asset*);

    void addOuterIPSP(ipsp*);

    void setTreeWidget(asset*);

    void setTreeWidgetIPSP(ipsp*);

    void on_addIPSP_clicked();

    void on_createButton_clicked();

private:
    Ui::environment *ui;

    asset *as;

    ipsp *ip;

    QVector<asset*>assetArr;

    QVector<ipsp*>outerIPSParr;



};

#endif // ENVIRONMENT_H
