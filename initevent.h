#ifndef INITEVENT_H
#define INITEVENT_H

#include <QDialog>
class attacker {
private:
    QString name;
    int likeliness;
    QString description;

public:
    attacker(QString name, int likliness, QString description);

    QString getName();
    int getLike();
    QString getDesc();

};

namespace Ui {
class initEvent;
}

class initEvent : public QDialog
{
    Q_OBJECT

public:
    explicit initEvent(QWidget *parent = nullptr);
    ~initEvent();

    attacker* createAttacker(QString name, int likeliness, QString description);
signals:
    void attackerSignal(attacker*);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::initEvent *ui;

    attacker *threat;

};


#endif // INITEVENT_H
