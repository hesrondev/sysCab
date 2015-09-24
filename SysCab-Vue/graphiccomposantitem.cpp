#include "graphiccomposantitem.h"

GraphicComposantItem::GraphicComposantItem() : QGraphicsItem(),
    brushDefault(QBrush(QColor(220, 220, 220))), pen(Qt::blue, 1.3, Qt::SolidLine)
{

}

// Accesseurs

QBrush GraphicComposantItem::getBrushDefault() const
{
    return brushDefault;
}

void GraphicComposantItem::setBrushDefault(const QBrush &value)
{
    brushDefault = value;
}

// Destructeur
GraphicComposantItem::~GraphicComposantItem()
{
    std::cout << "Destruction GraphicComposantItem" << std::endl;
    std::cout << "-> Fin de la destruction" << std::endl;
}



