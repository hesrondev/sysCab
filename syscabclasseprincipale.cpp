#include "syscabclasseprincipale.h"

SysCabClassePrincipale::SysCabClassePrincipale():_modele(), _baseExos(), _baseUsers()
{
    _fen = new FenetrePrincipale;
    _tableauDeBord = new TableauDeBord;

    _fen->show();

    _tableauDeBord->move((_fen->pos().x() + (_fen->width() - _tableauDeBord->width())/2),
                         (_fen->pos().y() + _fen->height() - 20));

    Customization::customTdbWidget(_tableauDeBord);

    // gestions des bases
    _exoIndex = 0;
    _latIndex = 0;

    _currentUser = NULL;
    _baseExos.afficher();
    _baseUsers.afficher();

    // Permissions
    _modeLibre = false;
    _modeUser = false;
    _validConfig = false;
    _activeExoMode = false;
    _activeSimulation = false;


    // Ajout des OBSERVERS
    // Dans le tableau _items de la classe Scene, les moteurs graphiques sont en position [0-2]
    // les reservoirs sont entre 8-10

    for (int i = 0; i < 3; i++)
        _modele.getReservoirs(i).addResObserver(_fen->_vueDeScene->getReservoir(i+8));


    // Les cannaux RM sont en position 14, 15 et 18
    _modele.getMoteurs(0).addCanalObserver(_fen->_vueDeScene->getCanal(14));
    _modele.getMoteurs(1).addCanalObserver(_fen->_vueDeScene->getCanal(15));
    _modele.getMoteurs(2).addCanalObserver(_fen->_vueDeScene->getCanal(18));



    // le tableau d'état se trouve en position 20
    _modele.addDisplayOberserver((GraphicEtatRM*)_fen->_vueDeScene->_items[20]);

    // les vannes sont compris entre 3-7
    _modele.getVannesRes(0).addVanneObserver(_fen->_vueDeScene->getVanne(3));  //VT12
    _modele.getVannesRes(1).addVanneObserver(_fen->_vueDeScene->getVanne(4));  //VT23

    _modele.getVannesRM().getVannes(0).addVanneObserver(_fen->_vueDeScene->getVanne(5)); //V12
    _modele.getVannesRM().getVannes(1).addVanneObserver(_fen->_vueDeScene->getVanne(6)); //V13
    _modele.getVannesRM().getVannes(2).addVanneObserver(_fen->_vueDeScene->getVanne(7)); //V23


    // Initialisation des minuteurs

    _consoTimer = new QTimer;
    _challengeTimer = new QTimer;
    _latenceTimer = new QTimer;
    _tpChallengeRestant = 0;
    _tpLatenceRestant = 0;

    // Connexions des signaux et des slots

    QObject::connect(_fen, SIGNAL(modeLibreSignal()), this, SLOT(modeLibreSlot()));
    QObject::connect(_fen, SIGNAL(homeSignal()), this, SLOT(homeSlot()));
    QObject::connect(_fen, SIGNAL(exercicesSignal()), this, SLOT(exercicesWidgetSlot()));

    QObject::connect(_tableauDeBord, SIGNAL(VT12Signal(int)), this, SLOT(VTSlot(int)));
    QObject::connect(_tableauDeBord, SIGNAL(VT23Signal(int)), this, SLOT(VTSlot(int)));
    QObject::connect(_tableauDeBord, SIGNAL(V12Signal(int)), this, SLOT(VSlot(int)));
    QObject::connect(_tableauDeBord, SIGNAL(V13Signal(int)), this, SLOT(VSlot(int)));
    QObject::connect(_tableauDeBord, SIGNAL(V23Signal(int)), this, SLOT(VSlot(int)));

    QObject::connect(_tableauDeBord, SIGNAL(ps12Signal(int)), this, SLOT(pompeSecoursSlot(int)));
    QObject::connect(_tableauDeBord, SIGNAL(ps22Signal(int)), this, SLOT(pompeSecoursSlot(int)));
    QObject::connect(_tableauDeBord, SIGNAL(ps32Signal(int)), this, SLOT(pompeSecoursSlot(int)));

    QObject::connect(_consoTimer, SIGNAL(timeout()), this, SLOT(consommationSlot()));
    QObject::connect(_challengeTimer, SIGNAL(timeout()), this, SLOT(stopChallengeSlot()));
    QObject::connect(_latenceTimer, SIGNAL(timeout()), this, SLOT(genererChallengePanneSlot()));

    QObject::connect(_fen->_toolbar->_optionsView, SIGNAL(startPauseSignal(bool)), this, SLOT(startPauseSlot(bool)));
    QObject::connect(_fen->_toolbar->_optionsView, SIGNAL(restartSignal()), this, SLOT(resetSimulationSlot()));
    QObject::connect(_fen->_toolbar->_optionsView, SIGNAL(astuceSignal()), this, SLOT(astucesWidgetSlot()));

    QObject::connect(_fen->_toolbar->_pannePrimaireAction, SIGNAL(triggered()), this, SLOT(pannePrimaireSlot()));
    QObject::connect(_fen->_toolbar->_panneSecoursAction, SIGNAL(triggered()), this, SLOT(panneSecoursSlot()));
    QObject::connect(_fen->_toolbar->_panneViderAction, SIGNAL(triggered()), this, SLOT(panneViderResSlot()));
    QObject::connect(_fen->_toolbar->_panneAleatAction, SIGNAL(triggered()), this, SLOT(panneAleatoireSlot()));

    QObject::connect(_fen->_toolbar->_configButton, SIGNAL(clicked()), this, SLOT(configWidgetSlot()));
    QObject::connect(_fen->_configModelWidget, SIGNAL(capacitesSlot(double,double,double,double,double,double)), this,
                     SLOT(configModelSlot(double,double,double,double,double,double)));

    // signaux de connexions
    QObject::connect(_fen->_loginView, SIGNAL(connexionIdSignal(string, string)), this, SLOT(connexionVerificationSlot(string, string)));
    QObject::connect(_fen->_loginView, SIGNAL(registerIdSignal(string, string)), this, SLOT(registerVerificationSlot(string, string)));

    // Espace utilisateur
    QObject::connect(_fen->_toolbar->_notesAction, SIGNAL(triggered()), this, SLOT(tableDeNotesSlot()));
    QObject::connect(_fen->_toolbar->_deconnexion, SIGNAL(triggered()), this, SLOT(deconnexionSlot()));

    //
    QObject::connect(_fen->_exercicesView, SIGNAL(challengeSignal(int)), this, SLOT(openChallengeWidgetSlot(int)));
    QObject::connect(_fen->_challengeWidget, SIGNAL(beginSignal()), this, SLOT(startChallengeSlot()));

     QObject::connect(_fen->_notationWidget, SIGNAL(listeExosSignal()), _fen, SLOT(setExercicesSlot()));
    QObject::connect(_fen->_notationWidget, SIGNAL(nextChallengeSignal()), this, SLOT(nextChallengeSlot()));
    QObject::connect(_fen->_notationWidget, SIGNAL(retryChallengeSignal()), this, SLOT(resetSimulationSlot()));
}


/* ****** SLOTS ****** */


/* *** INTERFACE GENERALE *** */


void SysCabClassePrincipale::modeLibreSlot()
{
    setModeLibrePermissions(true);
}

// Affichage de la fenêtre de configuration

void SysCabClassePrincipale::configWidgetSlot()
{
    // mettre en pause si simulation active
    mettreEnPause();

    _fen->_configModelWidget->show();
}

// Configuration du modèle selon les valeurs entrées

void SysCabClassePrincipale::configModelSlot(double r1, double r2, double r3, double m1, double m2, double m3)
{
    resetSimulationSlot();

    _modele.initialise(r1, r2, r3, m1, m2, m3);
    _tableauDeBord->resetComps();

    if (!_validConfig)
        setConfigPermissions(true);

    refreshSceneView();
}


void SysCabClassePrincipale::homeSlot()
{
    resetSimulationSlot();

    // cacher le tableau de bord
    _tableauDeBord->hide();

    // vider tout
    _modele.resetModel();

    setModeLibrePermissions(false);
    setModeUserPermissions(false);
}

void SysCabClassePrincipale::exercicesWidgetSlot()
{
    resetSimulationSlot();
    _tableauDeBord->hide();
}


/* *** SLOTS DU TABLEAU DE BORD *** */


void SysCabClassePrincipale::VTSlot(int i)
{
    // On inverse la valeur du booléen à chaque clic

    bool nonb = !(_modele.getVannesRes(i).isOuvert());
    _modele.getVannesRes(i).setOuvert(nonb);

    refreshSceneView();
}


void SysCabClassePrincipale::VSlot(int i)
{
    bool nonb = !(_modele.getVannesRM().getVannes(i).isOuvert());

    if (nonb)
        _modele.getVannesRM().ouvrirVanne(i);

    else
        _modele.getVannesRM().fermerVanne(i);

    refreshSceneView();
}

void SysCabClassePrincipale::pompeSecoursSlot(int i)
{
    bool nonb = !(_modele.getReservoirs(i).getPompeSecours().isMarche());

    if (nonb)
        _modele.getReservoirs(i).demarrerPompeSecours();

    else
        _modele.getReservoirs(i).fermerPompeSecours();

    refreshSceneView();
}




/* *** SLOTS DES PANNES *** */


void SysCabClassePrincipale::pannePrimaireSlot()
{
    // On récupère l'indice du reservoir sélectionné
    int i = _fen->_toolbar->_reservoirMenu->currentIndex();
    _modele.pannePprimaire(i);

    QString sp = "[!] Panne POMPE PRIMAIRE du réservoir " + QString::fromStdString(_modele.getReservoirs(i).getNom());
    _fen->_statusBar->showMessage(sp, 3000);

    refreshSceneView();
}

void SysCabClassePrincipale::panneSecoursSlot()
{
    int i = _fen->_toolbar->_reservoirMenu->currentIndex();
    _modele.pannePsecours(i);

    QString sp = "[!] Panne POMPE SECOURS du réservoir " + QString::fromStdString(_modele.getReservoirs(i).getNom());
    _fen->_statusBar->showMessage(sp, 3000);

    refreshSceneView();
}

void SysCabClassePrincipale::panneViderResSlot()
{
    int i = _fen->_toolbar->_reservoirMenu->currentIndex();
    _modele.viderReservoir(i);

    QString sp = "[!] Vidage du réservoir " + QString::fromStdString(_modele.getReservoirs(i).getNom()) +" ...";
    _fen->_statusBar->showMessage(sp, 3000);

    refreshSceneView();
}

void SysCabClassePrincipale::panneAleatoireSlot()
{
    int aleat1 = 0, aleat2 = 0;         //indice du reservoir + numéro panne aléatoires
    int borneMin = 1, borneMax = 3;

    srand(time(NULL));

    aleat1 = (int) (rand() % (borneMax - borneMin) + borneMin);
    aleat2 = (int) (rand() % (borneMax - borneMin) + borneMin);

    switch (aleat2)                         // couple de valeurs une et un seule fois
    {
        case 0: _modele.pannePprimaire(aleat1-1); break;
        case 1: _modele.pannePsecours(aleat1-1); break;
        case 2: _modele.viderReservoir(aleat1-1); break;
    }

    QString sp = "[!] Panne aléatoire (?)";
    _fen->_statusBar->showMessage(sp, 3000);

    refreshSceneView();
}



/* *** SLOTS DE LA SIMULATION *** */



void SysCabClassePrincipale::consommationSlot()
{
    bool isConso = _modele.consommation();

    if (!isConso)
    {
        _modele.afficher();
        _fen->_statusBar->showMessage("[!] Réservoirs à sec !", 3000);

        if (_activeExoMode)
            stopChallengeSlot();
        else
            stopSimulationSlot();
    }

    refreshSceneView();
}

// Démarrage et Pause de la simulation

void SysCabClassePrincipale::startPauseSlot(bool EnPause)
{
    hideMenu();

    if (!EnPause)
    {
        _activeSimulation = true;   // la simulation est en cours

        _tableauDeBord->show();
        _consoTimer->start(500);
        _fen->_statusBar->showMessage("Consommation ...");

        // Si challenge en cours

        if (_activeExoMode)
            spChallengeSlot(true);
    }

    else
    {
        _activeSimulation = false;   // la simulation est en pause

        _consoTimer->stop();
        _fen->_statusBar->showMessage("[ETAT] Simulateur en pause ...");
        _tableauDeBord->hide();

        // Si challenge en cours

        if (_activeExoMode)
            spChallengeSlot(false);
    }
}


void SysCabClassePrincipale::resetSimulationSlot()
{
    hideMenu();
    stopSimulationSlot();

    _tableauDeBord->resetComps();
    _modele.initialise();

    // Si le challenge est en cours
    if (_activeExoMode)
        _latIndex = 0;

    refreshSceneView();
}

void SysCabClassePrincipale::stopSimulationSlot()
{
    _fen->_statusBar->showMessage("Arrêt en cours ...", 1000);
    _fen->_statusBar->showMessage("[ETAT] Arrêté");

    _consoTimer->stop();
    _fen->_toolbar->_optionsView->resetPauseAction();

    if (_activeExoMode)
    {
        _challengeTimer->stop();
        _latenceTimer->stop();
    }

    _activeSimulation = false;   // la simulation est arrêté
}



// Les deux fonctions suivantes vérifient la validité des identifiants en paramètres
// Pour la connexion ou la création d'un compte

void SysCabClassePrincipale::connexionVerificationSlot(string id, string mdp)
{
    _currentUser = _baseUsers.rechercherUtilisateur(id, mdp);

    if (_currentUser != NULL)
    {
        cout << "[DONE] connexion reussie" << endl;

        // On initialise aussi le tableau d'exercices
        _fen->_exercicesView->debloquerExos(_currentUser->getNbExosRealises());

        // On initialise les notes
        _fen->_notesUserTable->updateUserNotes(_currentUser->getExoNotes());

        // vider les champs
        _fen->_loginView->viderChamps();

        setModeUserPermissions(true);
        _fen->_toolbar->_idAction->setText(QString::fromStdString(_currentUser->getId()));  // afficher le pseudo
        _fen->setSceneInterface();
    }

    else
    {
        _fen->_loginView->connexionWarnings("Identifiants incorrects !");
        cout << "[ECHEC] Indentifiants incorrects, veuillez vous enregistrer" << endl;
    }
}


void SysCabClassePrincipale::registerVerificationSlot(string id, string mdp)
{
    bool valid = _baseUsers.ajouterUtilisateur(id, mdp);

    if (valid)
    {
        cout << "[DONE] creation de compte reussie" << endl;

        _fen->setLoginInterface();
        _baseUsers.sauverBase();
        _baseUsers.afficher();

        // vider les champs
        _fen->_loginView->viderChamps();
    }

    else
    {
        _fen->_loginView->registerWarnings("Identifiants invalides !");
    }
}

// Affichage du tableau de notes de l'utilisateur courant

void SysCabClassePrincipale::tableDeNotesSlot()
{
    _fen->_notesUserTable->show();
}

void SysCabClassePrincipale::deconnexionSlot()
{
    _currentUser = NULL;

    _fen->_toolbar->_idAction->setText("");
    _fen->_toolbar->_idAction->setVisible(false);

    // On bloque aussi les exos
    _fen->_exercicesView->bloquerExos();

    // retour vers la page d'accueil
    _fen->setIndexSlot();
}




/* *** SLOTS DE GESTION DES CHALLENGES *** */


// Ouverture de la fenetre de présentation du challenge
// mise à jour de la fenetre de présentation du challenge avec les params de l'exo choisi
// initialisation du modèle avec la configuration de l'exo

void SysCabClassePrincipale::openChallengeWidgetSlot(int numExo)
{
    _fen->setSceneInterface();

    _fen->_challengeWidget->setLabels(numExo+1, _baseExos.getExo(numExo));
    _fen->_challengeWidget->show();

    _modele.initExoConfig(_baseExos.getExo(numExo).Config());

    // Mise à jour des variables
    _tpChallengeRestant = _baseExos.getExo(numExo).duree() * 1000;
    _tpLatenceRestant = _baseExos.getExo(numExo).getLatences()[0];
    _exoIndex = numExo;
    _latIndex = 0;
}

// Commencer le challenge après l'appuie sur "commencer"

void SysCabClassePrincipale::startChallengeSlot()
{
    setExercicesPermissions(true);

    // Réinitialisation du tdbord
    _tableauDeBord->resetComps();

    // Commencer

    _fen->_toolbar->_optionsView->startPauseSlot();

}

void SysCabClassePrincipale::stopChallengeSlot()
{
    // Arrêter la simulation
    stopSimulationSlot();

    cout << "FIN DU CHALLENGE" << endl;

    _modele.afficher();

    // Appeler la fonction de notation
    int ctrlDecisions = _modele.getControlDecisions();
    int ctrlResolus = _modele.getControlResolutions();
    int ctrlPannes = _modele.getControlPannes();

    bool reussi = true;

    if (ctrlResolus == 0)   //si aucune panne n'a été résolu
        reussi = false;

        cout << ctrlResolus << " < " << ctrlPannes << endl;

    if (reussi)
    {
        // debloquer le niveau suivant
        if(_exoIndex < _fen->_exercicesView->_boutons.size()-1)
            _fen->_exercicesView->debloquerUnExo(_exoIndex+1);

        // enregistrer le score

        if (_currentUser != NULL)
        {
            _currentUser->ajouterNote(_exoIndex, ctrlDecisions+ctrlResolus);

            // ajouter dans le tableau
            _fen->_notesUserTable->updateUserNotes(_currentUser->getExoNotes());
        }
    }

    // afficher la fenêtre de note qui affiche
    _tableauDeBord->hide();
    _fen->_notationWidget->setLabels(reussi, _exoIndex, ctrlResolus, ctrlDecisions, ctrlPannes);
    _fen->_notationWidget->show();
}

void SysCabClassePrincipale::spChallengeSlot(bool bStart)
{
    if (bStart)
    {
        // On lance le cpt à rebours selon la durée de l'exo (en msec)
        _challengeTimer->start(_tpChallengeRestant);
        _latenceTimer->start(_tpLatenceRestant);
    }

    else
    {
        _tpChallengeRestant = _challengeTimer->remainingTime();
        _tpLatenceRestant = _latenceTimer->remainingTime();

        cout << "Temps restant : " << _tpChallengeRestant << " , " << _tpLatenceRestant << endl;
        _challengeTimer->stop();
        _latenceTimer->stop();
    }
}

// Cette fonction génère une panne du tableau de panne si le temps de latence s'écoule

void SysCabClassePrincipale::genererChallengePanneSlot()
{
    _latenceTimer->stop();

    // récupérer la panne qui fait suite au temps de latence terminé
    int ptemp = _baseExos.getExo(_exoIndex).getPannes()[_latIndex];

    switch(ptemp)
    {
    case 1: _modele.pannePprimaire(0);
        break;
    case 2: _modele.pannePsecours(0);
        break;
    case 3: _modele.pannePprimaire(1);
        break;
    case 4: _modele.pannePsecours(1);
        break;
    case 5: _modele.pannePprimaire(2);
        break;
    case 6: _modele.pannePsecours(2);
        break;
    case 7: _modele.viderReservoir(0);
        break;
    case 8: _modele.viderReservoir(1);
        break;
    case 9: _modele.viderReservoir(2);
        break;
    }

    _latIndex++;

    if (_latIndex < _baseExos.getExo(_exoIndex).getLatences().size())
    {
        _tpLatenceRestant = _baseExos.getExo(_exoIndex).getLatences()[_latIndex];
        _latenceTimer->start(_tpLatenceRestant);
    }

}

// Slot du challenge suivant
void SysCabClassePrincipale::nextChallengeSlot()
{
    // incrémentation du numéro d'exercice jusqu'à 14.
    if (_exoIndex < 14)
    {
        int tp = _exoIndex+1;
        openChallengeWidgetSlot(tp);
    }

    else
    {
        cout << "FIN DE LA SERIE D'exos" << endl;
        exercicesWidgetSlot();
    }
}

void SysCabClassePrincipale::retryChallengeSlot()
{

}




/* *** AUTRES SLOTS *** */

// Affiche la feuille de mission de l'exercice
void SysCabClassePrincipale::astucesWidgetSlot()
{
    hideMenu();
    mettreEnPause();
}





/* ****** Fonctions utilitaires de la classe ****** */



// Cache le menu après sélection de l'objet
void SysCabClassePrincipale::hideMenu()
{
    _fen->_toolbar->_resumeMenu->hide();
}

// met à jour l'affichage des fenêtres, le faire de façon inverse

void SysCabClassePrincipale::refreshSceneView()
{
    _modele.updateDisplay();
    _fen->_vueDeScene->_scene.update();
}

// Fonction qui met en pause la simulation si on clique sur un bouton hors contexte

void SysCabClassePrincipale::mettreEnPause()
{
    if (_activeSimulation)
        _fen->_toolbar->_optionsView->startPauseSlot();     // Met en pause si en cours...
}


/* *** Fonctions d'activation ou désactivation des widgets **** */

// Mode utilisation libre

void SysCabClassePrincipale::setModeLibrePermissions(bool b)
{
    if (b)
    {
        _modeLibre = true;
        _fen->_toolbar->_configButton->setEnabled(true);
    }

    else
    {
        _modeLibre = false;
        setConfigPermissions(false);
        _fen->_toolbar->_configButton->setEnabled(false);
    }
}

// Activation des widgets après configuration du modèle

void SysCabClassePrincipale::setConfigPermissions(bool b)
{
    if (b)
    {

        // desactiver le mode exercice

        if (_activeExoMode)
            setExercicesPermissions(false);

        _validConfig = true;

        _fen->_toolbar->_optionsView->_startAction->setEnabled(true);
        _fen->_toolbar->_optionsView->_restartAction->setEnabled(true);
        _fen->_toolbar->_reservoirMenu->setEnabled(true);
        _fen->_toolbar->_panneAleatAction->setEnabled(true);
        _fen->_toolbar->_pannePrimaireAction->setEnabled(true);
        _fen->_toolbar->_panneSecoursAction->setEnabled(true);
        _fen->_toolbar->_panneViderAction->setEnabled(true);
        _tableauDeBord->show();
    }

    else
    {
        _validConfig = false;

        _fen->_toolbar->_optionsView->_startAction->setEnabled(false);
        _fen->_toolbar->_optionsView->_restartAction->setEnabled(false);
        _fen->_toolbar->_reservoirMenu->setEnabled(false);
        _fen->_toolbar->_panneAleatAction->setEnabled(false);
        _fen->_toolbar->_pannePrimaireAction->setEnabled(false);
        _fen->_toolbar->_panneSecoursAction->setEnabled(false);
        _fen->_toolbar->_panneViderAction->setEnabled(false);
        _tableauDeBord->hide();
    }
}

// Configuration exos

void SysCabClassePrincipale::setExercicesPermissions(bool b)
{
    if (b)
    {
        // desactiver la config libre en laissant actif le bouton config actif

        if (_validConfig)
            setConfigPermissions(false);

        _activeExoMode = true;

        _fen->_toolbar->_optionsView->_startAction->setEnabled(true);
        _fen->_toolbar->_optionsView->_restartAction->setEnabled(true);
        _fen->_toolbar->_optionsView->_astucesAction->setEnabled(true);

        _tableauDeBord->show();
    }

    else
    {
        _activeExoMode = false;

        _fen->_toolbar->_optionsView->_startAction->setEnabled(false);
        _fen->_toolbar->_optionsView->_restartAction->setEnabled(false);
        _fen->_toolbar->_optionsView->_astucesAction->setEnabled(false);

        _tableauDeBord->hide();
    }
}

// Mode Utilisateur connecté

void SysCabClassePrincipale::setModeUserPermissions(bool b)
{
    if (b)
    {
        _modeUser = true;
        setModeLibrePermissions(true);                  // mode libre inclus

        _fen->_toolbar->_idAction->setVisible(true);
        _fen->_toolbar->_optionsView->_exercicesAction->setEnabled(true);
    }

    else
    {
      _modeUser = false;
      setModeLibrePermissions(false);

      if (_activeExoMode)
          setExercicesPermissions(false);

      _fen->_toolbar->_optionsView->_exercicesAction->setEnabled(false);
    }
}





/* *** DESTRUCTEUR *** */
SysCabClassePrincipale::~SysCabClassePrincipale()
{
    delete _consoTimer;
    delete _challengeTimer;
    delete _latenceTimer;

    delete _tableauDeBord;
    delete _fen;

}





