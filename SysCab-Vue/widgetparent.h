#ifndef WIDGETPARENT_H
#define WIDGETPARENT_H

#include <iostream>
using namespace std;

#include <QWidget>


// Widget de base définissant les dimensions des widgets héritants

class WidgetParent : public QWidget
{
public:
    WidgetParent(int w, int h, QString titre = "SysCab 1.0");

    int getH() const;
    int getW() const;
    void setH(int h);
    void setW(int w);

    ~WidgetParent();

protected:
    int _W, _H;

};

#endif // WIDGETPARENT_H
