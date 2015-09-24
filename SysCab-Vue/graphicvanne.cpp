#include "graphicvanne.h"

GraphicVanne::GraphicVanne(QString nom, qreal x, qreal y, int brush) : GraphicComposantItem(), _dp(x, y), _canalObserver()
{
    _bopen = true;
    _bcirculer = false;

    _nom = nom;

    _canalObserver.reserve(2);

    // Couleur par défaut

    if (brush == 0)
        _carbColor = brushDefault;

    else
        _carbColor = QBrush(QColor(181, 123, 183));
}

bool GraphicVanne::isOpen() const
{
    return _bopen;
}

void GraphicVanne::setOpen(bool op)
{
    _bopen = op;
}

// Si le carburant ne circule pas, on remet la valeur par défaut

void GraphicVanne::setBcirculer(bool bcirculer)
{
    _bcirculer = bcirculer;
    QBrush br;

    if (!_bcirculer)
        br = brushDefault;

    else
        br = _carbColor;

    for (int i = 0; i < _canalObserver.size(); i++)
    {
        _canalObserver[i]->setBcirculer(_bcirculer);
        _canalObserver[i]->setColor(br);
    }
}






// Renvoie le point centre de la vanne

QPointF GraphicVanne::centre() const
{
    return QPointF(_dp.x()+10, _dp.y()+10);
}

//
QBrush GraphicVanne::carbColor() const
{
    return _carbColor;
}

void GraphicVanne::setCarbColor(const QBrush &carbColor)
{
    _carbColor = carbColor;

    for (int i = 0; i < _canalObserver.size(); i++)
    {
        _canalObserver[i]->setColor(_carbColor);
    }
}

bool GraphicVanne::bcirculer() const
{
    return _bcirculer;
}




// chaque vanne observe un ou plusieurs cannaux. Ajout de ces cannaux

void GraphicVanne::addObserver(GraphicCanal *canal)
{
    _canalObserver.push_back(canal);
}



// Fonctions de paint

QRectF GraphicVanne::boundingRect() const
{
    return QRectF(_dp.x(), _dp.y(), 20, 20);
}

void GraphicVanne::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal x = _dp.x();
    qreal y = _dp.y();

    QRectF rect = boundingRect();
    QRectF opcRect;

    QPen extPen(Qt::blue, 0.7, Qt::SolidLine);
    QBrush brush;

    QLine extLine1(x, y+6, x+20, y+6);
    QLine extLine2(x, y+13.5, x+20, y+13.5);

    if (!_bopen)
    {
        QRectF r(x-1, y+6.5, 22, 7);
        opcRect = r;

        if (_bcirculer)
            brush = _carbColor;

        else
            brush = brushDefault;
    }

    else
    {
        QRectF r(x+7.5, y, 5, 20);
        opcRect = r;
        brush = QBrush(Qt::blue);
    }

    painter->fillRect(rect, brushDefault);

    painter->setPen(pen);
    painter->drawEllipse(rect);

    painter->fillRect(opcRect, brush);

    painter->drawText(x+0.5, y-3, _nom);    // nom de la vanne

    if (!_bopen)
    {
        painter->setPen(extPen);
        painter->drawLine(extLine1);
        painter->drawLine(extLine2);
    }

}



// Destructeur

GraphicVanne::~GraphicVanne()
{

}
