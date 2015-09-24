#include "graphicmoteur.h"

GraphicMoteur::GraphicMoteur(QString nom, qreal x, qreal y) : GraphicComposantItem(), _dp(x, y), _nom(nom)
{

}

QPointF GraphicMoteur::centre() const
{
    return QPointF(_dp.x()+20, _dp.y()+24);
}

void GraphicMoteur::surconsoState()
{

}

void GraphicMoteur::normalState()
{

}

QRectF GraphicMoteur::boundingRect() const
{
    return QRectF(_dp.x(), _dp.y(), 100, 100);
}

void GraphicMoteur::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal x = _dp.x();
    qreal y = _dp.y();

    QPolygonF polygone1, polygone2;

    QLineF line1(x+9, y+32, x+15, y+32);
    QLineF line2(x+31, y+32, x+25, y+32);

    polygone1 << QPointF(x, y) << QPointF(x+40, y) << QPointF(x+40, y+13) << QPointF(x, y+13);

    polygone2 << QPointF(x+6, y+13) << QPointF(x+34, y+13) << QPointF(x+34, y+25) << QPointF(x+28, y+48)
              << QPointF(x+12, y+48) << QPointF(x+6, y+25);

    painter->setPen(pen);

    painter->drawText(x+14, y+11, _nom);

    QPainterPath path;
    path.addPolygon(polygone2);

    painter->fillPath(path, brushDefault);

    painter->drawPolygon(polygone1);
    painter->drawPolygon(polygone2);
    painter->drawLine(line1);
    painter->drawLine(line2);
}


GraphicMoteur::~GraphicMoteur()
{

}

