#ifndef GRAPHICCANALRM_H
#define GRAPHICCANALRM_H

#include <QPolygonF>
#include <QPainter>
#include "graphiccomposantitem.h"

class GraphicCanal : public GraphicComposantItem
{
public:
    GraphicCanal(const QPolygonF& polygone);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setColor(const QBrush& color);

    ~GraphicCanal();

    bool getBcirculer() const;
    void setBcirculer(bool value);

private:
    QPolygonF _polygone;
    QBrush _carbColor;
    bool bcirculer;
};

#endif // GRAPHICCANALRM_H
