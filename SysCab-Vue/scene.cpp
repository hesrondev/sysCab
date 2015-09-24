#include "scene.h"

Scene::Scene() : _scene(), _items(), _brush(QColor(220, 220, 220))
{
    _items.reserve(21);

    setScene(&_scene);

    dessinerCoque();
    dessinerElements();

    // couleur de fond
    QBrush br = QBrush(QPixmap("images/bg"));
    setBackgroundBrush(_brush);

    // Antialliage
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
}


// Dessiner sur la scène les éléments qui ne changent pas

void Scene::dessinerCoque()
{
    QPolygonF polygoneCoque1, polygoneCoque2;

    QLineF line1(-70, 30, -70, -110);
    QLineF line2(70, 30, 70, -110);

    polygoneCoque1 << QPointF(-320, 70) << QPointF(-90, 50) << QPointF(90, 50) << QPointF(320, 70)
                   << QPointF(320, -150) << QPointF(90, -190) << QPointF(-90, -190) << QPointF(-320, -150);

    polygoneCoque2 << QPointF(-300, 50) << QPointF(-70, 30) << QPointF(70, 30) << QPointF(300, 50)
                   << QPointF(300, -80) << QPointF(70, -110) << QPointF(-70, -110) << QPointF(-300, -80);


    QPen pen1(QBrush(QColor(93, 66, 193)), 1, Qt::DashLine);
    QPen pen2(QBrush(QColor(93, 66, 193)), 1, Qt::SolidLine);
    QPen pen3(Qt::blue, 1, Qt::DashLine);


    /* Point de départ des canaux reliant les reservoirs
    *  On en place 3 en faisant varier les coordonnées de x et y dans la boucle for
    */

    qreal x = 30;
    qreal y = -5;

    for (int i = 0; i < 3; i++)
    {
        if (i == 1)
        {
            x = -280;
            y = 10;
        }

        else if (i == 2)
            x = 260;

        QRectF rect = QRectF(x, y, 20, 25);

        QLineF line3(x+7.5, y+5, x+7.5, y+20);
        QLineF line4(x+12.5, y+5, x+12.5, y+20);
        QLineF lineWhite(x+8.5, y, x+12.5, y);

        _scene.addRect(rect, QPen(Qt::blue, 1, Qt::SolidLine));
        _scene.addLine(line3, pen3);
        _scene.addLine(line4, pen3);

        QGraphicsItem *lineTransparente = _scene.addLine(lineWhite, QPen(_brush, 2, Qt::SolidLine));
        lineTransparente->setZValue(4);     // elle doit être au dessus
    }




    // Ajout des textes de reservoirs

    QGraphicsTextItem *text1 = _scene.addText("TANK1", QFont("Calibri Light", 8));
    QGraphicsTextItem *text2 = _scene.addText("TANK2", QFont("Calibri Light", 8));
    QGraphicsTextItem *text3 = _scene.addText("TANK3", QFont("Calibri Light", 8));

    text1->setPos(-113, -100);
    text2->setPos(27, -100);
    text3->setPos(72, -100);
    text1->setDefaultTextColor(QColor(93, 66, 193));
    text2->setDefaultTextColor(QColor(93, 66, 193));
    text3->setDefaultTextColor(QColor(93, 66, 193));

    _scene.addPolygon(polygoneCoque1, pen1);
    _scene.addPolygon(polygoneCoque2, pen2);
    _scene.addLine(line1, pen2);
    _scene.addLine(line2, pen2);

}

// Affichage des éléments variants

void Scene::dessinerElements()
{

    QPolygonF polygoneVT1, polygoneVT2, polygoneVT3, polygoneRM1, polygoneRM2, polygoneRM3;
    QPolygonF polygoneV12, polygoneV13, polygoneV23;

    _items.push_back(new GraphicMoteur("M1", -260, -230));
    _items.push_back(new GraphicMoteur("M2", -20, -250));
    _items.push_back(new GraphicMoteur("M3", 220, -230));

    _items.push_back(new GraphicVanne("VT12", -110, -40, 1));
    _items.push_back(new GraphicVanne("VT23", 90, -40, 1));

    _items.push_back(new GraphicVanne("V12", -60, -175));
    _items.push_back(new GraphicVanne("V13", -40, -142));
    _items.push_back(new GraphicVanne("V23", 40, -175));

    // initialisation des pompes

    _items.push_back(new GraphicReservoir(-205, -70, QBrush(QColor(253, 116, 51))));
    _items.push_back(new GraphicReservoir(-20, -80, QBrush(QColor(37, 148, 34)), 68));
    _items.push_back(new GraphicReservoir(165, -70, QBrush(QColor(237, 201, 56))));     //10

    // polygones vannes

    qreal x = -280;    qreal cx = ((GraphicVanne *)_items[3])->centre().x();
    qreal y = 10;      qreal cy = ((GraphicVanne *)_items[3])->centre().y();

    polygoneVT1 << QPointF(x+7.5, y) << QPointF(x+7.5, y-12) << QPointF(cx-18, cy-3.5) << QPointF(cx, cy-3.5)
                << QPointF(cx, cy+3.5) << QPointF(cx-18, cy+3.5) << QPointF(x+13.5, y-7) << QPointF(x+13.5, y);

    _items.push_back(new GraphicCanal(polygoneVT1));        //11

    // ************

    x = 30;      cx = ((GraphicVanne *)_items[4])->centre().x();  qreal cxx = ((GraphicVanne *)_items[3])->centre().x();
    y = -5;      cy = ((GraphicVanne *)_items[4])->centre().y();  qreal cyy = ((GraphicVanne *)_items[3])->centre().y();

    polygoneVT2 << QPointF(x+13.5, y) << QPointF(x+13.5, cy+3.5) << QPointF(cx, cy+3.5) << QPointF(cx, cy-3.5)
                << QPointF(cxx, cyy-3.5) << QPointF(cxx, cyy+3.5) << QPointF(x+7.5, cyy+3.5) << QPointF(x+7.5, y);


    _items.push_back(new GraphicCanal(polygoneVT2));    //12

    // ************

    x = 260;     cx = ((GraphicVanne *)_items[4])->centre().x();
    y = 10;      cy = ((GraphicVanne *)_items[4])->centre().y();

    polygoneVT3 << QPointF(x+13.5, y) << QPointF(x+13.5, y-12) << QPointF(cx+18, cy-3.5) << QPointF(cx, cy-3.5)
                << QPointF(cx, cy+3.5) << QPointF(cx+18, cy+3.5) << QPointF(x+7.5, y-7) << QPointF(x+7.5, y);

    _items.push_back(new GraphicCanal(polygoneVT3));    //13


    // polygones canaux reservoirs - moteurs reliés aux pompes

    cx = ((GraphicVanne *)_items[5])->centre().x();
    cy = ((GraphicVanne *)_items[5])->centre().y();
    x = ((GraphicVanne *)_items[6])->centre().x();
    y = ((GraphicVanne *)_items[6])->centre().y();
    qreal dx = ((GraphicReservoir *)_items[8])->pointDeConnexion().x();
    qreal dy = ((GraphicReservoir *)_items[8])->pointDeConnexion().y();
    qreal mx = ((GraphicMoteur *)_items[0])->centre().x();
    qreal my = ((GraphicMoteur *)_items[0])->centre().y();

    polygoneRM1 << QPointF(dx, dy+7) << QPointF(mx-3.5, dy+7) << QPointF(mx-3.5, my)
                << QPointF(mx+3.5, my) << QPointF(mx+3.5, y-9.5) << QPointF(-70, cy-3.5) << QPointF(cx, cy-3.5)
                << QPointF(cx, cy+3.5) << QPointF(-70, cy+3.5) << QPointF(mx+3.5, y-2.5)
                << QPointF(mx+3.5, dy) << QPointF(dx, dy);

    _items.push_back(new GraphicCanal(polygoneRM1));    //14

    // Les cannaux reliant les moteurs aux pompes

    dx = ((GraphicReservoir *)_items[9])->pointDeConnexion().x();
    dy = ((GraphicReservoir *)_items[9])->pointDeConnexion().y();
    mx = ((GraphicMoteur *)_items[1])->centre().x();
    my = ((GraphicMoteur *)_items[1])->centre().y();

    polygoneRM2 << QPointF(mx-3.5, dy) << QPointF(mx-3.5, my) << QPointF(mx+3.5, my) << QPointF(mx+3.5, dy);

    _items.push_back(new GraphicCanal(polygoneRM2));    //15

            // ajouts du canal traversant la vanne V12

            polygoneV12 << QPointF(cx, cy-3.5) << QPointF(cx, cy+3.5) << QPointF(dx, dy+7) << QPointF(dx, dy);
            _items.push_back(new GraphicCanal(polygoneV12));    //16

    // **********

    cx = ((GraphicVanne *)_items[6])->centre().x();
    cy = ((GraphicVanne *)_items[6])->centre().y();
    x = ((GraphicVanne *)_items[7])->centre().x();
    y = ((GraphicVanne *)_items[7])->centre().y();

            polygoneV23 << QPointF(x, y-3.5) << QPointF(x, y+3.5) << QPointF(dx+11, dy+7) << QPointF(dx+11, dy);
            _items.push_back(new GraphicCanal(polygoneV23));    //17

    dx = ((GraphicReservoir *)_items[10])->pointDeConnexion().x();
    dy = ((GraphicReservoir *)_items[10])->pointDeConnexion().y();
    mx = ((GraphicMoteur *)_items[2])->centre().x();
    my = ((GraphicMoteur *)_items[2])->centre().y();

    polygoneRM3 << QPointF(dx+11, dy) << QPointF(mx-3.5, dy)
                << QPointF(mx-3.5, cy+3.5) << QPointF(70, y+3.5) << QPointF(x, y+3.5) << QPointF(x, y-3.5)
                << QPointF(70, y-3.5) << QPointF(mx-3.5, cy-3.5) << QPointF(mx-3.5, my) << QPointF(mx+3.5, my)
                << QPointF(mx+3.5, dy+7) << QPointF(dx+11, dy+7);


    _items.push_back(new GraphicCanal(polygoneRM3));    //18

            // Ajout du canal de la vanne 13

            x = ((GraphicReservoir *)_items[8])->pointDeConnexion().x();
            y = ((GraphicReservoir *)_items[8])->pointDeConnexion().y();
            dx = ((GraphicReservoir *)_items[10])->pointDeConnexion().x();
            dy =((GraphicReservoir *) _items[10])->pointDeConnexion().y();

            polygoneV13 << QPointF(x+11, y+7) << QPointF(x+11, y) << QPointF(x+19, y) << QPointF(-70, cy-3.5)
                        << QPointF (70, cy-3.5) << QPointF (dx-10, dy) << QPointF (dx, dy) << QPointF (dx, dy+7)
                        << QPointF (dx-10, dy+7) << QPointF (70, cy+3.5) << QPointF(-70, cy+3.5)
                        << QPointF(x+19, dy+7);

            _items.push_back(new GraphicCanal(polygoneV13));    //19


    // Ajouts des tableaux des états du système
    _items.push_back(new GraphicEtatRM(-320, -332));    //20

    // Ajouts des items à la scène

    for (int i = _items.size()-1; i >=0; i--)
    {

        /* De 11 à 13 on trouve les canaux 'CanalVanne' traversant les vannes et qui croisent les cannaux des pompes
         * Ceux ci seront au dessous des cannaux des pompes
         */
        if (i >= 11 && i <= 13)
            _items[i]->setZValue(2);

        else
            _items[i]->setZValue(3);

        _scene.addItem(_items[i]);
    }


    // Ajout des observeurs -  Connexion des cannaux aux vannes

    ((GraphicVanne*)_items[3])->addObserver((GraphicCanal*)_items[11]);  //VT12
    ((GraphicVanne*)_items[3])->addObserver((GraphicCanal*)_items[12]);  //VT12
    ((GraphicVanne*)_items[4])->addObserver((GraphicCanal*)_items[12]);  //VT23
    ((GraphicVanne*)_items[4])->addObserver((GraphicCanal*)_items[13]);  //VT23

    ((GraphicVanne*)_items[5])->addObserver((GraphicCanal*)_items[16]);  //V12
    ((GraphicVanne*)_items[6])->addObserver((GraphicCanal*)_items[19]);  //V13
    ((GraphicVanne*)_items[7])->addObserver((GraphicCanal*)_items[17]);  //V23

}


//

GraphicMoteur *Scene::getMoteur(int i)
{
    if (i >= 0 && i <= 2)
        return (GraphicMoteur*)_items[i];
}

GraphicVanne *Scene::getVanne(int i)
{
    if (i >= 3 && i <= 7)
        return (GraphicVanne*)_items[i];
}

GraphicReservoir *Scene::getReservoir(int i)
{
    if (i >= 8 && i <= 10)
        return (GraphicReservoir*)_items[i];
}

GraphicCanal *Scene::getCanal(int i)
{
    if (i >= 11 && i <= 19)
        return (GraphicCanal*)_items[i];
}




// Setteurs
int Scene::getH() const
{
    return _H;
}

int Scene::getW() const {
    return _W;
}

void Scene::setH(int h)
{
    _H = h;
}

void Scene::setW(int w)
{
    _W = w;
}


// Destructeur

Scene::~Scene()
{
    cout << "Destruction de la vue de scene" << endl;

    for (int i = _items.size()-1; i >= 0; i--)
    {
        delete _items[i];
    }

    std::cout << "-> Fin de la destruction" << std::endl;
}

