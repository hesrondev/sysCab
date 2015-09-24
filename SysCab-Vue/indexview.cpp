#include "indexview.h"

IndexView::IndexView() : WidgetParent(350, 200, "Index")
{
    // initialisation des composants
    initComps();
}

void IndexView::initComps()
{
    QLabel *titleLabel = new QLabel("Bienvenue dans le simulateur");
    QLabel *syscabLabel = new QLabel("SysCab 1.0");


    titleLabel->setFixedWidth(300);
    syscabLabel->setFixedWidth(300);

    titleLabel->setAlignment(Qt::AlignCenter);
    syscabLabel->setAlignment(Qt::AlignCenter);

    _connexionButton = new QPushButton("ESPACE COMPTE");
    _partieLibreButton = new QPushButton("SIMULATION LIBRE");

    _connexionButton->setFixedSize(300, 40);
    _partieLibreButton->setFixedSize(300, 40);

    QVBoxLayout *vlayout = new QVBoxLayout;
    QSpacerItem *spacer = new QSpacerItem(this->width(), 40);

    vlayout->addWidget(titleLabel);
    vlayout->addWidget(syscabLabel);
    vlayout->addSpacerItem(spacer);
    vlayout->addWidget(_connexionButton);
    vlayout->addWidget(_partieLibreButton);

    setLayout(vlayout);

    // IDS
    titleLabel->setObjectName("title");     // identifiant pour le style
    syscabLabel->setObjectName("syscab");   // id
    _connexionButton->setObjectName("cnxButton");
    _partieLibreButton->setObjectName("libreButton");
}


IndexView::~IndexView()
{
    std::cout << "Destruction IndexView" << std::endl;
    delete _connexionButton;
    delete _partieLibreButton;
    std::cout << "-> Fin de la destruction" << std::endl;
}
