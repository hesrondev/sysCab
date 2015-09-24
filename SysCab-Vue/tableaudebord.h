#ifndef TABLEAUDEBORD_H
#define TABLEAUDEBORD_H

#include <iostream>
#include "widgetparent.h"
#include "customization.h"

using namespace std;

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>

#include "tdbcustombutton.h"


class TableauDeBord : public QWidget
{
    Q_OBJECT

    friend class FenetrePrincipale;
    friend class SysCabClassePrincipale;

public:
    TableauDeBord();

    void initComps();
    void resetComps();
    ~TableauDeBord();

public slots:

    void VT12Slot();
    void VT23Slot();
    void V12Slot();
    void V13Slot();
    void V23Slot();

    void pompeSecours12Slot();
    void pompeSecours22Slot();
    void pompeSecours32Slot();


signals:

    void VT12Signal(int);
    void VT23Signal(int);
    void V12Signal(int);
    void V13Signal(int);
    void V23Signal(int);
    void ps12Signal(int);
    void ps22Signal(int);
    void ps32Signal(int);

private:
    TdbCustomButton *_VT12Button;
    TdbCustomButton *_VT23Button;
    TdbCustomButton *_P12Button;
    TdbCustomButton *_P22Button;
    TdbCustomButton *_P32Button;
    TdbCustomButton *_V12Button;
    TdbCustomButton *_V13Button;
    TdbCustomButton *_V23Button;

};

#endif // TABLEAUDEBORD_H
