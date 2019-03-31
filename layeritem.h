#ifndef LAYERITEM_H
#define LAYERITEM_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtCore>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTreeWidget>


struct dimensions {
    int height;
    int width;
};

class layerItem : public QGraphicsItem
{

private:
    dimensions d;
    QString n;
    int pfd;

    bool isPressed;

    QPointF dragStartPosition;
public:
    layerItem(int height, int width, QString name, int pfd);

    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mousePressEvent(QGraphicsSceneMouseEvent* e);



};

#endif // LAYERITEM_H
