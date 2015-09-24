#ifndef MOTEURGRAPHIC_H
#define MOTEURGRAPHIC_H

#include <QPainter>
#include <QPolygonF>
#include <QLineF>

#include "graphiccomposantitem.h"

class GraphicMoteur : public GraphicComposantItem
{
public:
    GraphicMoteur(QString nom, qreal x, qreal y);

    QPointF centre() const;
    void surconsoState();
    void normalState();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    ~GraphicMoteur();

private:
    QPointF _dp;
    QString _nom;

};

#endif // MOTEURGRAPHIC_H
