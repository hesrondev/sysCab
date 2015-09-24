#ifndef GRAPHICPOMPE_H
#define GRAPHICPOMPE_H

#include <QPolygonF>
#include <QPainter>

#include "graphiccomposantitem.h"



class GraphicReservoir : public GraphicComposantItem
{
public:
    GraphicReservoir(const qreal &x, const qreal &y, QBrush color, const qreal &hauteur = 30);
    QPointF pointDeConnexion() const;

    void drawIndicElems(QPainter *painter, qreal x, qreal y);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool getBPrimMarche() const;
    void setBPrimMarche(bool value);

    bool getBSecMarche() const;
    void setBSecMarche(bool value);

    bool getBPrimPanne() const;
    void setBPrimPanne(bool value);

    bool getBSecPanne() const;
    void setBSecPanne(bool value);

    bool bcirculer() const;
    void setBcirculer(bool bcirculer);

    QBrush carbColor() const;
    void setCarbColor(const QBrush &carbColor);

     ~GraphicReservoir();

private:

    QPointF _dp;
    qreal _hauteur;
    QBrush _carbColor;

    bool bPrimMarche;
    bool bSecMarche;
    bool bPrimPanne;
    bool bSecPanne;

    bool _bcirculer;
};

#endif // GRAPHICPOMPE_H
