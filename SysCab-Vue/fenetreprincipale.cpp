#include "fenetreprincipale.h"


FenetrePrincipale::FenetrePrincipale(QWidget *parent) : QMainWindow(parent)
{
    // initialisations
    _H = 500;
    _W = 850;

    setFixedSize(_W, _H);

    setWindowTitle(tr("SysCab 1.0"));

    setObjectName("topCadre");

    // fonctions d'initialisation
    initComps();

    //
    customize();


    // Connexions des signaux et des slots

    QObject::connect(_indexView->_connexionButton, SIGNAL(clicked()), this, SLOT(setLoginSlot()));
    QObject::connect(_indexView->_partieLibreButton, SIGNAL(clicked()), this, SLOT(setSceneSlot()));

    QObject::connect(_toolbar->_optionsView, SIGNAL(homeSignal()), this, SLOT(setIndexSlot()));
    QObject::connect(_toolbar->_optionsView, SIGNAL(exercicesSignal()), this, SLOT(setExercicesSlot()));

}

// Initialisation  des composants
void FenetrePrincipale::initComps()
{
    // Initialisation du widget de la zone centrale

    _centralView = new QWidget;

    _horiLayout = new QHBoxLayout;
    _horiLayout->setMargin(0);

    _centralView->setLayout(_horiLayout);

    setCentralWidget(_centralView);

    // Initialisation de la barre d'outils
    _toolbar = new BarreOutils;
    addToolBar(_toolbar);
    _toolbar->hide();

    // initialisation de la barre de status
    _statusBar = new QStatusBar;
    setStatusBar(_statusBar);

    // initialisation de l'index, au départ on est sur la Interface index
    _indexView = new IndexView;
    centrerWidget(_indexView);

    // initialisation de la Interface de connexion
    _loginView = new LoginView;

    // initialisation de la Interface d'exercices
    _exercicesView = new ExercicesView;

    // initialisation de la scene
    _vueDeScene = new Scene;

    // initialisation du widget de configuration
    _configModelWidget = new ConfigModelWidget;

    // initialisation du widget challenge
    _challengeWidget = new ChallengeWidget;

    // initialisation du widget notation
    _notationWidget = new NotationWidget;

    // intialiation des tableaux de notes
    _notesUserTable = new NotesUserView;

}


// fonction qui permet de centrer le widget en entrée
void FenetrePrincipale::centrerWidget(QWidget *widget)
{
    int w = (_centralView->width() - widget->width()) / 2;

    // déclaration des espaces
    QSpacerItem* leftSpacer = new QSpacerItem(w, _centralView->height());
    QSpacerItem* rightSpacer = new QSpacerItem(w, _centralView->height());

    _horiLayout->addSpacerItem(leftSpacer);
    _horiLayout->addWidget(widget);
    _horiLayout->addSpacerItem(rightSpacer);
}


// On enlève les widgets de la fenetre

void FenetrePrincipale::resetComps()
{
    _vueDeScene->setParent(NULL);
    _loginView->setParent(NULL);
    _indexView->setParent(NULL);
    _exercicesView->setParent(NULL);

    while (_horiLayout->takeAt(0) != NULL)
        delete _horiLayout->takeAt(0);
}

//

void FenetrePrincipale::customize()
{
    Customization::customIndexView(_indexView);
    Customization::customLoginView(_loginView);
    Customization::customExercicesView(_exercicesView);
    Customization::customConfigModel(_configModelWidget);
    Customization::customToolBar(_toolbar);
    Customization::customChallengeDesc(_challengeWidget);
    Customization::customNotationWidget(_notationWidget);
    Customization::customNotesUserWidget(_notesUserTable);
}


//
void FenetrePrincipale::setIndexInterface()
{
    // cacher la barre d'options
    _toolbar->_resumeMenu->hide();
    _toolbar->hide();

    resetComps();
    centrerWidget(_indexView);
}

void FenetrePrincipale::setLoginInterface()
{
    resetComps();
    centrerWidget(_loginView);
}

void FenetrePrincipale::setExercicesInterface()
{
    // cacher la barre d'options et la barre d'outils
    _toolbar->_resumeMenu->hide();
    _toolbar->hide();

    resetComps();
    centrerWidget(_exercicesView);
}

void FenetrePrincipale::setSceneInterface()
{
    resetComps();

    // On affiche la barre d'outils
    _toolbar->show();

    _horiLayout->addWidget(_vueDeScene);
}





/* ****** SLOTS ****** */




void FenetrePrincipale::setIndexSlot()
{
    setIndexInterface();
    emit homeSignal();
}

void FenetrePrincipale::setLoginSlot()
{
    setLoginInterface();
}

void FenetrePrincipale::setExercicesSlot()
{
    setExercicesInterface();
    emit exercicesSignal();
}

void FenetrePrincipale::setSceneSlot()
{
    setSceneInterface();
    emit modeLibreSignal();
}


// Setteurs
int FenetrePrincipale::getH() const
{
    return _H;
}

int FenetrePrincipale::getW() const
{
    return _W;
}

void FenetrePrincipale::setH(int h)
{
    _H = h;
}

void FenetrePrincipale::setW(int w)
{
    _W = w;
}



// Destructeur, détruire dans le sens inverse de la création

FenetrePrincipale::~FenetrePrincipale()
{
    cout << "Destruction de la fenetre principale" << endl;   

    delete _toolbar;
    delete _indexView;
    delete _loginView;
    delete _exercicesView;
    delete _vueDeScene;
    delete _configModelWidget;
    delete _challengeWidget;
    delete _notationWidget;
    delete _notesUserTable;

    delete _horiLayout;

    delete _statusBar;
    delete _centralView;


    std::cout << "-> Fin de la destruction Fenetre Principale" << std::endl;
}

