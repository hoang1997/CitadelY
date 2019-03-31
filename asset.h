#ifndef ASSET_H
#define ASSET_H

#include <QDialog>
#include <QVector>
#include "ipsp.h"
#include "initevent.h"

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

    void setSeverity();
    int getSeverity();
    double getCredits();

    QVector<ipsp*> getIPSPs();

    QString getDamageLevel();

    int getRSS();

    QVector<attacker*> getInitEvents();

    int getAvRisk();



signals:
    void assetSignal(asset*);

private slots:
    void on_pushButton_clicked();

    void on_cancelButton_clicked();

    void addIPSP(ipsp*);

    void setTreeWidget(ipsp*);

    void on_createButton_clicked();

    void on_pushButton_2_clicked();

    void addInitEvents(attacker*);



private:
    Ui::asset *ui;
    ipsp *ps;
    QString name;
    int severity;
    QVector<ipsp*> ipspArr;
    initEvent *iEvent;
    QVector<attacker*> initEvents;
    int avLike;

};

#endif // ASSET_H
