#include "graphicreservoir.h"

GraphicReservoir::GraphicReservoir(const qreal& x, const qreal& y, QBrush color, const qreal &hauteur): GraphicComposantItem(), _dp(x, y), _carbColor(color)
{
    _hauteur = hauteur;

    _bcirculer = false;
    bPrimMarche = true;
    bSecMarche = false;
    bPrimPanne = false;
    bSecPanne = false;

    //
}

QPointF GraphicReservoir::pointDeConnexion() const
{
    return QPointF(_dp.x()+15.5, _dp.y()-(_hauteur+20));
}



// DRAWING PART

// Cette fonction ajoute les polygones symbolysant indicant les pompes
void GraphicReservoir::drawIndicElems(QPainter *painter, qreal x, qreal y)
{
    // cercles pannes
    QRectF indicRect1 = QRectF(x-20, y+2.5, 10, 10);
    QPolygonF indicPolygone1;

    QRectF indicRect2 = QRectF(x+50, y+2.5, 10, 10);
    QPolygonF indicPolygone2;

    QPen pen2(Qt::blue, 1, Qt::SolidLine);

    indicPolygone1 << QPointF(x-15, y+2.5) << QPointF(x-5, y+7.5) << QPointF(x-15, y+12.5);
    indicPolygone2 << QPointF(x+55, y+2.5) << QPointF(x+45, y+7.5) << QPointF(x+55, y+12.5);

    QRectF indicRectIn1 = QRectF(x-18, y+4.5, 6, 6);
    QRectF indicRectIn2 = QRectF(x+52, y+4.5, 6, 6);



            pen.setWidth(2);
            painter->setPen(pen);

            painter->drawEllipse(indicRect1);
            painter->drawPolygon(indicPolygone1);
            painter->drawEllipse(indicRect2);
            painter->drawPolygon(indicPolygone2);


            QPainterPath indicPath;

            indicPath.addEllipse(indicRect1);
            painter->fillPath(indicPath, brushDefault);
            indicPath.addEllipse(indicRect2);
            painter->fillPath(indicPath, brushDefault);

            indicPath.addPolygon(indicPolygone1);
            painter->fillPath(indicPath, brushDefault);
            indicPath.addPolygon(indicPolygone2);
            painter->fillPath(indicPath, brushDefault);

            painter->setPen(pen2);
            painter->drawEllipse(indicRectIn1);
            painter->drawEllipse(indicRectIn2);

}

QRectF GraphicReservoir::boundingRect() const
{
    return QRectF(_dp.x(), _dp.y(), 15, 15);
}

void GraphicReservoir::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal x = _dp.x();
    qreal y = _dp.y();

    qreal sx = x+25;

    qreal rx = x+17.5;
    qreal ry = y-12;

    // cercles externes des pompes
    QRectF primRect = boundingRect();
    QRectF secRect = QRectF(sx, y, 15, 15);

    // mini cercles à l'interieur des pompes

    QRectF inRect1 = QRectF(x+5, y+5, 5, 5);
    QRectF inRect2 = QRectF(x+30, y+5, 5, 5);

    drawIndicElems(painter, x, y);

    // branchement entre les canaux de P1 et P2

    QRectF transRect = QRectF(rx-2, ry-2, 9, 9);
    QRectF transRectSupLeft = QRectF(rx-4, ry-3, 2, 11);
    QRectF transRectSupRight = QRectF(rx+7, ry-3, 2, 11);

    // canal de ralongement et de connexion aux canaux des moteurs

    QRectF ralRect = QRectF(rx-1, ry-_hauteur, 7, _hauteur);
    QRectF ralConnectRect = QRectF(rx-3, ry-(_hauteur+10), 11, 11);
    QRectF ralRectLeft = QRectF(rx-5, ry-(_hauteur+12), 2, 15);
    QRectF ralRectRight = QRectF(rx+8, ry-(_hauteur+12), 2, 15);

    // les polygones  de rattachement pompes aux canaux

    QPolygonF polygonePrim, polygoneSec;

    polygonePrim << QPoint(x+5, y)  << QPoint(x+5, ry) << QPoint(rx, ry)
                 << QPoint(rx, ry+5) << QPoint(x+10, ry+5) << QPoint(x+10, y);

    polygoneSec << QPoint(rx+5, ry)  << QPoint(sx+10, ry) << QPoint(sx+10, y)
                 << QPoint(sx+5, y) << QPoint(sx+5, y-5) << QPoint(rx+5, ry+5);


    // édition
    pen.setWidth(1);
    painter->setPen(pen);

    painter->drawText(x+4, y+28, "1");
    painter->drawText(x+29, y+28, "2");

    QPainterPath pathPrim, pathSec;
    pathPrim.addPolygon(polygonePrim);
    pathSec.addPolygon(polygoneSec);

    painter->drawPolygon(polygonePrim);
    painter->drawPolygon(polygoneSec);

    if (bPrimMarche && _bcirculer)
    {
        painter->fillPath(pathPrim, _carbColor);
    }

    else
    {
        painter->fillPath(pathPrim, brushDefault);
    }

    if (bSecMarche && _bcirculer)
    {
        painter->fillPath(pathSec, _carbColor);
    }

    else
    {
        painter->fillPath(pathSec, brushDefault);
    }


    // cercles externes

    painter->fillRect(primRect, brushDefault);
    painter->fillRect(secRect, brushDefault);

    // cercles internes

    painter->fillRect(inRect1, Qt::blue);
    painter->fillRect(inRect2, Qt::blue);

    // points de connexions

    if ((bPrimMarche || bSecMarche) && _bcirculer)
        painter->fillRect(ralRect, _carbColor);

    else
        painter->fillRect(ralRect, brushDefault);

    painter->drawRect(ralRect);
    painter->fillRect(ralConnectRect, brushDefault);
    painter->drawRect(ralConnectRect);
    painter->fillRect(ralRectLeft, brushDefault);
    painter->drawRect(ralRectLeft);
    painter->fillRect(ralRectRight, brushDefault);
    painter->drawRect(ralRectRight);

    painter->fillRect(transRect, brushDefault);
    painter->fillRect(transRectSupLeft, brushDefault);
    painter->fillRect(transRectSupRight, brushDefault);

    painter->drawRect(transRect);
    painter->drawRect(transRectSupLeft);
    painter->drawRect(transRectSupRight);


    // coloriage des cercles avec ou sans panne

    if (bPrimPanne)
    {
        painter->setBrush(Qt::red);
        painter->drawEllipse(primRect);
        painter->setBrush(brushDefault);
        painter->drawEllipse(inRect1);
    }

    else
    {
        painter->setBrush(brushDefault);
        painter->drawEllipse(primRect);
        painter->setBrush(Qt::blue);
        painter->drawEllipse(inRect1);
    }

    if (bSecPanne)
    {
        painter->setBrush(Qt::red);
        painter->drawEllipse(secRect);
        painter->setBrush(brushDefault);
        painter->drawEllipse(inRect2);
    }

    else
    {
        painter->setBrush(brushDefault);
        painter->drawEllipse(secRect);
        painter->setBrush(Qt::blue);
        painter->drawEllipse(inRect2);
    }


}


// ACCESSEURS *************

bool GraphicReservoir::getBPrimMarche() const
{
    return bPrimMarche;
}

void GraphicReservoir::setBPrimMarche(bool value)
{
    bPrimMarche = value;
}
bool GraphicReservoir::getBSecMarche() const
{
    return bSecMarche;
}

void GraphicReservoir::setBSecMarche(bool value)
{
    bSecMarche = value;
}
bool GraphicReservoir::getBPrimPanne() const
{
    return bPrimPanne;
}

void GraphicReservoir::setBPrimPanne(bool value)
{
    if (value)
        setBPrimMarche(false);

    bPrimPanne = value;
}
bool GraphicReservoir::getBSecPanne() const
{
    return bSecPanne;
}

void GraphicReservoir::setBSecPanne(bool value)
{
    if (value)
        setBSecMarche(false);

    bSecPanne = value;
}

bool GraphicReservoir::bcirculer() const
{
    return _bcirculer;
}

void GraphicReservoir::setBcirculer(bool bcirculer)
{
    _bcirculer = bcirculer;
}

QBrush GraphicReservoir::carbColor() const
{
    return _carbColor;
}

void GraphicReservoir::setCarbColor(const QBrush &carbColor)
{
    _carbColor = carbColor;
}



// DESCTRUCTEURS

GraphicReservoir::~GraphicReservoir()
{

}


