#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QAction>
#include <QProgressBar>
#include <QLabel>

#include <QPainter>
#include <QPolygonF>
#include <QRectF>
#include <QGraphicsTextItem>
#include <QVector>

#include "graphicmoteur.h"
#include "graphicvanne.h"
#include "graphicreservoir.h"
#include "graphiccanal.h"
#include "graphiccomposantitem.h"
#include "graphicetatrm.h"

using namespace std;

class Scene : public QGraphicsView
{
    friend class SysCabClassePrincipale;

public:
    Scene();
    void dessinerCoque();
    void dessinerElements();

    GraphicMoteur* getMoteur(int i);
    GraphicVanne* getVanne(int i);
    GraphicReservoir *getReservoir(int i);
    GraphicCanal *getCanal(int i);

    int getH() const;
    int getW() const;
    void setH(int h);
    void setW(int w);

    ~Scene();

private:
    QGraphicsScene _scene;
    QVector <GraphicComposantItem*> _items;

    QBrush _brush;
    int _W, _H;
};

#endif // SCENE_H
