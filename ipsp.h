#ifndef IPSP_H
#define IPSP_H

#include <QDialog>

namespace Ui {
class ipsp;
}

class ipsp : public QDialog
{
    Q_OBJECT

public:
    explicit ipsp(QWidget *parent = nullptr);
    ~ipsp();

    void setIPSP();
    QString getName();
    QString getType();
    int getPFD();

signals:
    void ipspSignal(ipsp*);
private slots:
    void on_closeButton_clicked();

    void on_addButton_clicked();

private:
    Ui::ipsp *ui;
    QString name, type;
    int PFD;
};

#endif // IPSP_H
