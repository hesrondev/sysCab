#ifndef GRAPHICCOMPOSANTITEM_H
#define GRAPHICCOMPOSANTITEM_H

/*
*   Cette classe redéfinissant la classe QGraphicsItem
*   Regroupe les attributs communs aux objets à dessiner comme
*   la couleur par défaut ou le pen
*/

#include <iostream>

#include <QGraphicsItem>
#include <QPainter>

class GraphicComposantItem : public QGraphicsItem
{
public:
    GraphicComposantItem();

    QBrush getBrushDefault() const;
    void setBrushDefault(const QBrush &value);
    virtual ~GraphicComposantItem();


protected:
    QBrush brushDefault;
    QPen pen;       // par défault

};

#endif // GRAPHICCOMPOSANTITEM_H
