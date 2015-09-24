#include "tableaudebord.h"

TableauDeBord::TableauDeBord()
{
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setFixedSize(336, 130);
    setWindowTitle("SysCab - Tableau de bord");

    // initialisation des widgets composants
    initComps();

    QObject::connect(_VT12Button, SIGNAL(clicked()), this, SLOT(VT12Slot()));
    QObject::connect(_VT23Button, SIGNAL(clicked()), this, SLOT(VT23Slot()));
    QObject::connect(_V12Button, SIGNAL(clicked()), this, SLOT(V12Slot()));
    QObject::connect(_V13Button, SIGNAL(clicked()), this, SLOT(V13Slot()));
    QObject::connect(_V23Button, SIGNAL(clicked()), this, SLOT(V23Slot()));

    QObject::connect(_P12Button, SIGNAL(clicked()), this, SLOT(pompeSecours12Slot()));
    QObject::connect(_P22Button, SIGNAL(clicked()), this, SLOT(pompeSecours22Slot()));
    QObject::connect(_P32Button, SIGNAL(clicked()), this, SLOT(pompeSecours32Slot()));
}

/* ****** Méthodes de la classe ****** */

// fonction d'initialisation
void TableauDeBord::initComps()
{

    // initialisation des boutons
    _VT12Button = new TdbCustomButton("VT12", 90, 30);
    _VT23Button = new TdbCustomButton("VT23", 90, 30);
    _P12Button = new TdbCustomButton("P12", 90, 30);
    _P22Button = new TdbCustomButton("P22", 90, 30);
    _P32Button = new TdbCustomButton("P32", 90, 30);
    _V12Button = new TdbCustomButton("V12", 90, 30);
    _V13Button = new TdbCustomButton("V13", 90, 30);
    _V23Button = new TdbCustomButton("V23", 90, 30);

    QGridLayout *glayout = new QGridLayout;
    glayout->setMargin(3);
    glayout->setSpacing(0);

    glayout->addWidget(_VT12Button, 0, 2, 1, 3);
    glayout->addWidget(_VT23Button, 0, 6, 1, 3);
    glayout->addWidget(_P12Button, 1, 0, 1, 3);
    glayout->addWidget(_P22Button, 1, 4, 1, 3);
    glayout->addWidget(_P32Button, 1, 8, 1, 3);
    glayout->addWidget(_V12Button, 2, 0, 1, 3);
    glayout->addWidget(_V13Button, 2, 4, 1, 3);
    glayout->addWidget(_V23Button, 2, 8, 1, 3);

    setLayout(glayout);
}

void TableauDeBord::resetComps()
{
    _VT12Button->resetConfig();
    _VT23Button->resetConfig();
    _P12Button->resetConfig();
    _P22Button->resetConfig();
    _P32Button->resetConfig();
    _V12Button->resetConfig();
    _V13Button->resetConfig();
    _V23Button->resetConfig();
}

void TableauDeBord::VT12Slot()
{
    emit VT12Signal(0);
}

void TableauDeBord::VT23Slot()
{
    emit VT23Signal(1);
}

void TableauDeBord::V12Slot()
{
    emit V12Signal(0);
}

void TableauDeBord::V13Slot()
{
    emit V13Signal(1);
}

void TableauDeBord::V23Slot()
{
    emit V23Signal(2);
}

void TableauDeBord::pompeSecours12Slot()
{
    emit ps12Signal(0);
}

void TableauDeBord::pompeSecours22Slot()
{
    emit ps22Signal(1);
}

void TableauDeBord::pompeSecours32Slot()
{
    emit ps32Signal(2);
}

/* ****** DESTRUCTEUR ******* */

TableauDeBord::~TableauDeBord()
{
    std::cout << "Destruction du tableau de bord" << std::endl;

    delete _VT12Button;
    delete _VT23Button;
    delete _P12Button;
    delete _P22Button;
    delete _P32Button;
    delete _V12Button;
    delete _V13Button;
    delete _V23Button;

    std::cout << "-> Fin de la destruction" << std::endl;

}

