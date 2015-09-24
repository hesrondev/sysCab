#include "graphiccanal.h"

GraphicCanal::GraphicCanal(const QPolygonF &polygone) : GraphicComposantItem(), _polygone(polygone), _carbColor(QBrush(QColor(250, 248, 255)))
{
    bcirculer = false;
}


// modification de la couleur du carburant circulant

void GraphicCanal::setColor(const QBrush &color)
{
    _carbColor = color;
}

bool GraphicCanal::getBcirculer() const
{
    return bcirculer;
}

void GraphicCanal::setBcirculer(bool value)
{
    bcirculer = value;
}





// Fonctions paint

QRectF GraphicCanal::boundingRect() const
{
    return QRectF(0, 0, 0, 0);
}

void GraphicCanal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);

    QPainterPath path;
    path.addPolygon(_polygone);

    if (bcirculer)
        painter->fillPath(path, _carbColor);

    else
        painter->fillPath(path, brushDefault);

    painter->drawPolygon(_polygone);
}


GraphicCanal::~GraphicCanal()
{
    std::cout << "Destruction GraphicCanal" << std::endl;
    std::cout << "-> Fin de la destruction" << std::endl;
}


