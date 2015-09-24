#include "exercicesview.h"

ExercicesView::ExercicesView() : WidgetParent(400, 270, "Exercices"), _boutons()
{
    _boutons.reserve(15);
    initComps();
}

// fonction d'initialisation des composants
void ExercicesView::initComps()
{
    QGridLayout *gridLayout = new QGridLayout;

    int ligne = 0;
    int col = 0;

    for (int i = 0; i < 15; i++)
    {
        QString sNumber = QString::number(i+1);

        ExoCustomButton *bouton = new ExoCustomButton(sNumber, i);
        _boutons.push_back(bouton);

        // intialisation des signaux du widget
        QObject::connect(bouton, SIGNAL(indexSignal(int)), this, SLOT(challengeSlot(int)));

        if (i > 0 && i%5 == 0)
        {
            ligne++;
            col = 0;
        }

        gridLayout->addWidget(bouton, ligne, col);

        col++;
    }

    // activer par défaut le 1e bouton
    _boutons[0]->setBActive(true);

    gridLayout->setSpacing(3);
    gridLayout->setMargin(15);

    QGroupBox *gbox = new QGroupBox("Challenges");
    gbox->setLayout(gridLayout);

    QHBoxLayout *hl = new QHBoxLayout;
    hl->setMargin(0);
    hl->addWidget(gbox);

    setLayout(hl);
}

// Par défaut un seul bouton d'exo est accessible

void ExercicesView::bloquerExos()
{
    for (int i = 1; i < _boutons.size(); i++)
        _boutons[i]->setBActive(false);
}

void ExercicesView::debloquerUnExo(int numExo)
{
    if (numExo >= 0 && numExo < _boutons.size())
    {
        if (!_boutons[numExo]->bActive())
            _boutons[numExo]->setBActive(true);
    }
}

// On active les boutons selon le nb d'exos déjà réalisés par le pilote
// On active tous les exercices réalisés et le dernier débloqué

void ExercicesView::debloquerExos(int nbExos)
{
    if (nbExos >= 0 && nbExos <= _boutons.size())
        for (int i = 0; i <= nbExos; i++)
        {
            if (i < _boutons.size())
                _boutons[i]->setBActive(true);
        }
}

void ExercicesView::challengeSlot(int index)
{
    emit challengeSignal(index);
}


//
ExercicesView::~ExercicesView()
{
    std::cout << "Destruction de ExercicesView" << std::endl;

    for (int i = _boutons.size()-1; i >=0; i--)
        delete _boutons[i];

    std::cout << "-> Fin de la destruction" << std::endl;
}

