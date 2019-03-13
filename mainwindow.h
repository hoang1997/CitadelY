#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "environment.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void setAssetIPSP(QVector<asset*>, QVector<ipsp*>);

    void setTreeWidget(QVector<asset*>, QVector<ipsp*>);

private slots:
    void on_createButton_clicked();

private:
    Ui::MainWindow *ui;

    QVector<asset*> assetArr;
    QVector<ipsp*> outerIPSParr;
    environment *env;
};

#endif // MAINWINDOW_H
