#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "environment.h"
#include "layeritem.h"
#include "evaluate.h"
#include "referencetable.h"

#include <QGraphicsScene>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void tableDataSignal(QVector<asset*>, QVector<ipsp*>);
    void diagramSignal(QPixmap);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void displayError(QString);

public slots:
    void setAssetIPSP(QVector<asset*>, QVector<ipsp*>);

    void setTreeWidget(QVector<asset*>, QVector<ipsp*>);

    void createGraphicsLayer(QVector<asset*>, QVector<ipsp*>);

private slots:
    void on_createButton_clicked();

    void on_evaluateButton_clicked();

    void on_actionTable_Reference_triggered();

private:
    Ui::MainWindow *ui;
    QVector<asset*> assetArr;
    QVector<ipsp*> outerIPSParr;
    environment *env;
    evaluate *eval;
    QGraphicsScene *scene;
    referenceTable *r;
};

#endif // MAINWINDOW_H
