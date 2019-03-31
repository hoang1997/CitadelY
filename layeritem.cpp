#include "layeritem.h"
#include <QtGui>
#include <QtCore>
#include <QTreeWidget>
#include <QGraphicsItem>
#include <QPaintEvent>
#include <QGraphicsScene>


layerItem::layerItem(int height, int width, QString name, int pfd)
{
    this->n = name;
    this->d.height = height;
    this->d.width = width;
    this->pfd = pfd;
    this->setFlag(ItemIsMovable);
    this->setFlag(ItemIsSelectable);
    isPressed = false;
    this->setAcceptHoverEvents(true);
    this->setAcceptDrops(true);

}

QRectF layerItem::boundingRect() const
{

    return QRectF(10,10, d.height,d.width);
}

void layerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    QColor green30 = Qt::green;
    green30.setAlphaF(0.3);


    if(pfd <= 4)
    {
        painter->drawRect(rec);
        brush.setColor(Qt::green);
        painter->fillRect(rec, brush);
        painter->drawText(rec, Qt::AlignLeft | Qt::AlignTop, n);
    }
    else if(pfd <=7 && pfd > 4)
    {
        painter->drawRect(rec);
        brush.setColor("orange");
        painter->fillRect(rec, brush);
        painter->drawText(rec, Qt::AlignLeft | Qt::AlignTop, n);
    }
    else if(pfd <= 10 && pfd > 7)
    {
        painter->drawRect(rec);
        brush.setColor(Qt::red);
        painter->fillRect(rec, brush);
        painter->drawText(rec, Qt::AlignLeft | Qt::AlignTop, n);
    }
    else if(pfd == 11){
        painter->drawRect(rec);
        painter->drawText(rec, Qt::AlignLeft | Qt::AlignVCenter, n);
    }
}

void layerItem::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    dragStartPosition = QCursor::pos();
    QGraphicsItem::mousePressEvent(e);
}



