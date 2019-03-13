#ifndef ASSET_H
#define ASSET_H

#include <QDialog>
#include <QVector>
#include "ipsp.h"

namespace Ui {
class asset;
}

class asset : public QDialog
{
    Q_OBJECT

public:
    explicit asset(QWidget *parent = nullptr);
    ~asset();

    void setName();


    QString getName();

    QVector<ipsp*> getIPSPs();

signals:
    void assetSignal(asset*);

private slots:
    void on_pushButton_clicked();

    void on_cancelButton_clicked();

    void addIPSP(ipsp*);

    void setTreeWidget(ipsp*);

    void on_createButton_clicked();

private:
    Ui::asset *ui;
    ipsp *ps;
    QString name;
    QVector<ipsp*> ipspArr;
};

#endif // ASSET_H
