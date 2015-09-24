#include "configmodelwidget.h"

ConfigModelWidget::ConfigModelWidget()
{
    setWindowTitle("SysCab - Configuration");
    setModal(true);

    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(400, 220);

    setObjectName("cadre");

    initComps();


    // Connexion des signaux

    QObject::connect(_res2SpBox, SIGNAL(valueChanged(double)), this, SLOT(res2CapaciteSlot(double)));
    QObject::connect(_cancelButton, SIGNAL(clicked()), this, SLOT(cancelSlot()));
    QObject::connect(_validButton, SIGNAL(clicked()), this, SLOT(validSlot()));

}

void ConfigModelWidget::initComps()
{
    _res1SpBox = new QDoubleSpinBox;
    _res2SpBox = new QDoubleSpinBox;
    _res3SpBox = new QDoubleSpinBox;

    _m1SpBox = new QDoubleSpinBox;
    _m2SpBox = new QDoubleSpinBox;
    _m3SpBox = new QDoubleSpinBox;

    // Valeurs par défaut

    _res1SpBox->setEnabled(false);
    _res3SpBox->setEnabled(false);

    _res1SpBox->setMaximum(10000);
    _res2SpBox->setRange(0, 9000);
    _res3SpBox->setMaximum(10000);

    _res1SpBox->setDecimals(2);
    _res1SpBox->setSingleStep(0.5);
    _res2SpBox->setDecimals(2);
    _res2SpBox->setSingleStep(0.5);
    _res3SpBox->setDecimals(2);
    _res3SpBox->setSingleStep(0.5);

    _m1SpBox->setRange(1, 100);
    _m1SpBox->setSingleStep(0.5);
    _m1SpBox->setDecimals(1);

    _m2SpBox->setRange(1, 100);
    _m2SpBox->setSingleStep(0.5);
    _m2SpBox->setDecimals(1);

    _m3SpBox->setRange(1, 100);
    _m3SpBox->setSingleStep(0.5);
    _m3SpBox->setDecimals(1);


    //
    _validButton = new QPushButton("Valider");
    _cancelButton = new QPushButton("Annuler");

    _validButton->setObjectName("validButton");
    _cancelButton->setObjectName("cancelButton");

    QLabel *res1label = new QLabel("TANK 1 : ");
    QLabel *res2label = new QLabel("TANK 2 : ");
    QLabel *res3label = new QLabel("TANK 3 : ");

    QLabel *m1label = new QLabel("Moteur 1 : ");
    QLabel *m2label = new QLabel("Moteur 2 : ");
    QLabel *m3label = new QLabel("Moteur 3 : ");

    QHBoxLayout *hl = new QHBoxLayout;
    hl->addWidget(_cancelButton);
    hl->addWidget(_validButton);

    QGroupBox *groupbox = new QGroupBox("Configuration");
    QGridLayout *glayout = new QGridLayout;

    glayout->addWidget(res1label, 0, 0);
    glayout->addWidget(_res1SpBox, 0, 1);
    glayout->addWidget(m1label, 0, 2);
    glayout->addWidget(_m1SpBox, 0, 3);

    glayout->addWidget(res2label, 1, 0);
    glayout->addWidget(_res2SpBox, 1, 1);
    glayout->addWidget(m2label, 1, 2);
    glayout->addWidget(_m2SpBox, 1, 3);

    glayout->addWidget(res3label, 2, 0);
    glayout->addWidget(_res3SpBox, 2, 1);
    glayout->addWidget(m3label, 2, 2);
    glayout->addWidget(_m3SpBox, 2, 3);

    glayout->addLayout(hl, 3, 2, 1, 2);

    groupbox->setLayout(glayout);

    //
    QHBoxLayout *classlayout = new QHBoxLayout;
    classlayout->setMargin(1);
    classlayout->addWidget(groupbox);

    setLayout(classlayout);

}


// SLOTS


void ConfigModelWidget::res2CapaciteSlot(double v)
{
    // Les capacités de res 1 et res3 > à res 2 au moins d'une unité

    _res1SpBox->setMinimum(v+1);
    _res3SpBox->setMinimum(v+1);

    _res1SpBox->setEnabled(true);
    _res3SpBox->setEnabled(true);
}

void ConfigModelWidget::validSlot()
{
    emit capacitesSlot(_res1SpBox->value(), _res2SpBox->value(), _res3SpBox->value(),
                       _m1SpBox->value(), _m2SpBox->value(), _m3SpBox->value());

    //setModal(false);
    hide();
}

void ConfigModelWidget::cancelSlot()
{
    //setModal(false);
    hide();
}



ConfigModelWidget::~ConfigModelWidget()
{
    std::cout << "Destruction ConfigModelWidget" << std::endl;

    delete _res1SpBox;
    delete _res2SpBox;
    delete _res3SpBox;

    delete _m1SpBox;
    delete _m2SpBox;
    delete _m3SpBox;

    delete _validButton;
    delete _cancelButton;

    std::cout << "-> Fin de la destruction" << std::endl;
}


