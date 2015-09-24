#ifndef INDEXVIEW_H
#define INDEXVIEW_H

#include <iostream>
#include "widgetparent.h"

using namespace std;

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAction>


class IndexView : public WidgetParent
{
    friend class FenetrePrincipale;
public:
    IndexView();
    void initComps();
    ~IndexView();

private:
    QPushButton *_connexionButton;
    QPushButton *_partieLibreButton;
};

#endif // INDEXVIEW_H
