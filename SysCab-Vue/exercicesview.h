#ifndef EXERCICESVIEW_H
#define EXERCICESVIEW_H

using namespace std;
#include <iostream>
#include "widgetparent.h"
#include "exocustombutton.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QVector>

class ExercicesView : public WidgetParent
{
    Q_OBJECT

    friend class FenetrePrincipale;
    friend class SysCabClassePrincipale;

public:
    ExercicesView();
    void initComps();
    void bloquerExos();
    void debloquerUnExo(int numExo);
    void debloquerExos(int nbExos);
    ~ExercicesView();

public slots:
    void challengeSlot(int index);

signals:
    void challengeSignal(int index);

private:
    QVector <ExoCustomButton *> _boutons;
};

#endif // EXERCICESVIEW_H
