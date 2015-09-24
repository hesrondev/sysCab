#include "barreoutils.h"

BarreOutils::BarreOutils()
{
    // caractéristiques
    setFixedHeight(40);
    setIconSize(QSize(24, 24));
    setMovable(false);


    // initialisation des composants
    initComps();

    // Etant initial des widgets


    _idAction->setVisible(false);
    _reservoirMenu->setEnabled(false);
    _configButton->setEnabled(false);
    _pannePrimaireAction->setEnabled(false);
    _panneSecoursAction->setEnabled(false);
    _panneViderAction->setEnabled(false);
    _panneAleatAction->setEnabled(false);

}

// initialisation des composants de la barre d'outils

void BarreOutils::initComps()
{

    QMenu *idMenu = new QMenu;
    _resumeMenu = new QMenu;
    _optionsView = new OptionsView(_resumeMenu);

    _configButton = new QPushButton("Configuration");
    _configButton->setFixedSize(100, 22);

    _reservoirMenu = new QComboBox;
    _reservoirMenu->addItem("TANK1");
    _reservoirMenu->addItem("TANK2");
    _reservoirMenu->addItem("TANK3");

    _reservoirMenu->setFixedSize(90, 20);


    // initialisations des actions    

    _pannePrimaireAction = new QAction(QIcon(":/logIcons/p11_t"), "Déclencher panne pompe primaire", this);
    _panneSecoursAction = new QAction(QIcon(":/logIcons/p12_t"), "Déclencher panne pompe secours", this);
    _panneViderAction = new QAction(QIcon(":/logIcons/vider_t"), "Vider le réservoir", this);
    _panneAleatAction = new QAction(QIcon(":/logIcons/aleat_tt"), "Panne aléatoire ?", this);

    _idAction = new QAction("", this);
    _loginAction = new QAction(QIcon(":/logIcons/login"), "Ouvrir une session", this);
    _saveAction = new QAction(QIcon(":/logIcons/save"), "Enregistrer la session", this);
    _notesAction = new QAction(QIcon(":/logIcons/notes"), "Mes notes", this);
    _classementAction = new QAction(QIcon(":/logIcons/classement"), "Mon classement", this);
    _myIdsAction = new QAction(QIcon(":/logIcons/id"), "Mes identifiants", this);
    _deconnexion = new QAction(QIcon(":/logIcons/"), "Deconnexion", this);
    _pauseAction = new QAction(QIcon(":/logIcons/options"), "Mettre en pause / reprendre la partie", this);

    _loginAction->setEnabled(false);

    // espace
    QWidget *emptyWidget = new QWidget;
    QHBoxLayout *hl = new QHBoxLayout;
    QSpacerItem *spacer = new QSpacerItem(260, 32);
    hl->addSpacerItem(spacer);
    emptyWidget->setLayout(hl);

    // Widget de configuration

    QWidget *configWidget = new QWidget;
    QHBoxLayout *hlayout = new QHBoxLayout;
    QSpacerItem *spacerLeft = new QSpacerItem(10, 32);
    QSpacerItem *spacer5 = new QSpacerItem(5, 32);

    hlayout->setMargin(1);
    hlayout->addSpacerItem(spacerLeft);
    hlayout->addWidget(_configButton);
    hlayout->addSpacerItem(spacer5);
    hlayout->addWidget(_reservoirMenu);

    configWidget->setLayout(hlayout);

    // placement des actions et menus
    _pauseAction->setMenu(_resumeMenu);
    _idAction->setMenu(idMenu);

    idMenu->addAction(_notesAction);
    idMenu->addSeparator();
    idMenu->addAction(_classementAction);
    idMenu->addSeparator();
    idMenu->addAction(_myIdsAction);
    idMenu->addSeparator();
    idMenu->addAction(_deconnexion);

    _resumeMenu->addAction(_optionsView);

    addAction(_pauseAction);
    addWidget(configWidget);
    addSeparator();
    addAction(_pannePrimaireAction);
    addAction(_panneSecoursAction);
    addAction(_panneViderAction);
    addAction(_panneAleatAction);
    addWidget(emptyWidget);
    addAction(_loginAction);
    addSeparator();
    addAction(_idAction);
}

BarreOutils::~BarreOutils()
{
    std::cout << "Destruction de la barre d'outils" << std::endl;
    delete _optionsView;
    delete  _loginAction;
    delete _saveAction;
    delete _notesAction;
    delete _classementAction;
    delete _myIdsAction;
    delete _deconnexion;

    delete _pannePrimaireAction;
    delete _panneSecoursAction;
    delete _panneViderAction;
    delete _panneAleatAction;

    delete _reservoirMenu;
    delete _configButton;

    delete _resumeMenu;

    delete _pauseAction;    // détruire après resumeMenu
    delete  _idAction;
    std::cout << "-> Fin de la destruction" << std::endl;
}

