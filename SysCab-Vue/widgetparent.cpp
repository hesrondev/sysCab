#include "widgetparent.h"


WidgetParent::WidgetParent(int w, int h, QString titre)
{
    setW(w);
    setH(h);

    setFixedSize(_W, _H);
    setWindowTitle(titre);
}

// Setteurs
int WidgetParent::getH() const
{
    return _H;
}

int WidgetParent::getW() const {
    return _W;
}

void WidgetParent::setH(int h)
{
    _H = h;
}

void WidgetParent::setW(int w)
{
    _W = w;
}


WidgetParent::~WidgetParent()
{
    std::cout << "Destruction de widget parent" << std::endl;
    std::cout << "-> Fin de la destruction" << std::endl;
}

