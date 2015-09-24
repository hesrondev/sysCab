#ifndef VANNEGRAPHIC_H
#define VANNEGRAPHIC_H

#include <QPainter>
#include <QRectF>
#include <QVector>

#include "graphiccomposantitem.h"
#include "graphiccanal.h"

class GraphicVanne : public GraphicComposantItem
{
public:
    GraphicVanne(QString nom, qreal x, qreal y, int brush = 0);

    bool isOpen() const;
    void setOpen(bool op);    
    QPointF centre() const;

    QBrush carbColor() const;
    void setCarbColor(const QBrush &carbColor);

    void addObserver(GraphicCanal *canal);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    ~GraphicVanne();


    bool bcirculer() const;
    void setBcirculer(bool bcirculer);

private:
    QPointF _dp;
    bool _bopen;
    bool _bcirculer;
    QString _nom;

    QBrush _carbColor;

    QVector <GraphicCanal*> _canalObserver;      //chaque vanne est lié à 1 ou plusieurs cannaux
};

#endif // VANNEGRAPHIC_H
