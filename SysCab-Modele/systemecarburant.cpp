#include "systemecarburant.h"

/* ****** CONSTRUCTEURS ****** */

SystemeCarburant::SystemeCarburant() : _reservoirs(), _moteurs(), _vannesRes(), _vannesRM()
{
    // initialisation des reservoirs
    _reservoirs.reserve(3);
    _reservoirs.push_back(Reservoir("TANK1", 0));
    _reservoirs.push_back(Reservoir("TANK2", 0));
    _reservoirs.push_back(Reservoir("TANK3", 0));

    // initialisation des moteurs
    _moteurs.reserve(3);
    _moteurs.push_back(Moteur("M1", 1));
    _moteurs.push_back(Moteur("M2", 1));
    _moteurs.push_back(Moteur("M3", 1));

    // On ajoute les observers des res dans les moteurs

    for (int i = 0; i < _moteurs.size(); i++)
        _moteurs[i].updateResObserver(&getReservoirs(i));

    // initialisation des vannes vt
    _vannesRes.reserve(2);
    _vannesRes.push_back(Vanne("VT12"));
    _vannesRes.push_back(Vanne("VT23"));

}




/* ****** Méthodes de la classe ****** */





// Ouverture et fermeture des vannes entre reservoirs

void SystemeCarburant::ouvrirVanneRes(int i)
{
    if (isValidVanneResIndex(i))
    {
        _vannesRes[i].setOuvert(true);

        std::cout << "*** ouverture vanne : " << _vannesRes[i].getNom() << std::endl;
    }
}

void SystemeCarburant::fermerVanneRes(int i)
{
    if (isValidVanneResIndex(i))
    {
        _vannesRes[i].setOuvert(false);

        std::cout << "*** fermeture vanne : " << _vannesRes[i].getNom() << std::endl;

        transfertCarburant();           // transfert après fermeture de vanne
    }
}

// Ouverture et fermeture des vannes entre reservoirs et moteurs

void SystemeCarburant::ouvrirVanneRM(int i)
{
    _vannesRM.ouvrirVanne(i);
}

void SystemeCarburant::fermerVanneRM(int i)
{
    _vannesRM.fermerVanne(i);
}


// Demarrage et arrêt des pompes de secours

void SystemeCarburant::ouvrirPsecours(int i)
{
    if (isValidReservoirIndex(i))
    {
        _reservoirs[i].demarrerPompeSecours();

        std::cout << "*** demarrage pompe secours : " << _reservoirs[i].getNom() << std::endl;
    }
}

void SystemeCarburant::fermerPsecours(int i)
{
    if (isValidReservoirIndex(i))
    {
        _reservoirs[i].fermerPompeSecours();

        std::cout << "*** arret pompe secours : " << _reservoirs[i].getNom() << std::endl;
    }
}


// A chaque panne des composants, les mettre à jour en signalant
// Ceci permet d'effectuer les controles sur les pannes résolus entre moteurs et reservoirs


// vidange du reservoir à l'indice i

void SystemeCarburant::viderReservoir(int i)
{
    if (isValidReservoirIndex(i))
    {
        _reservoirs[i].viderCarburant();

        std::cout << "*** vidange du reservoir : " << _reservoirs[i].getNom() << std::endl;

        // alerter le controleur de panne
        getReservoirs(i).setCarbPanne(true);
    }
}

// Panne de la pompe primaire

void SystemeCarburant::pannePprimaire(int i)
{
    if (isValidReservoirIndex(i))
    {
        getReservoirs(i).setPannePompePrimaire();

        std::cout << "*** panne pompe primaire : " << getReservoirs(i).getNom() << std::endl;

        // on signale la panne au reservoir
        getReservoirs(i).setPompePanne(true);
        getReservoirs(i).deleteMoteurSup();

        // on parcout tous les moteurs qui observent ce reservoir et on signale la panne
        for (int j = 0; j < _moteurs.size(); j++)
        {
            if (_moteurs[j].reservoirObserver() == &(_reservoirs[i]))
            {
                getMoteurs(j).activeControlePanne();

                // Mise à jour de la couleur de la vanne
                int v = vanneIndice(i, j);
                _vannesRM.getVannes(v).updateColor(QBrush(), false);
            }
        }
    }
}

void SystemeCarburant::pannePsecours(int i)
{
    if (isValidReservoirIndex(i))
    {
        getReservoirs(i).setPannePompeSecours();

        std::cout << "*** panne pompe secours : " << getReservoirs(i).getNom() << std::endl;

        // on signale la panne au reservoir
        getReservoirs(i).setPompePanne(true);
        // signaler le reservoir qu'il n'alimente plus le moteur
        getReservoirs(i).deleteMoteurSup();

        // on parcout tous les moteurs qui observent ce reservoir et on signale la panne
        for (int j = 0; j < _moteurs.size(); j++)
        {
            if (_moteurs[j].reservoirObserver() == &(_reservoirs[i]))
            {
                getMoteurs(j).activeControlePanne();

                // Mise à jour de la couleur de la vanne
                int v = vanneIndice(i, j);
                _vannesRM.getVannes(v).updateColor(QBrush(), false);
            }
        }
    }
}



// Fonction vérifiant que la valeur en entrée est un index correct

bool SystemeCarburant::isValidReservoirIndex(int i)
{
    if ((i >= 0) && (i < (int) _reservoirs.size()))
        return true;

    else
        return false;
}

bool SystemeCarburant::isValidMoteurIndex(int i)
{
    if ((i >= 0) && (i < (int) _moteurs.size()))
        return true;

    else
        return false;
}

bool SystemeCarburant::isValidVanneResIndex(int i)
{
    if ((i >= 0) && (i < (int) _vannesRes.size()))
        return true;

    else
        return false;
}





// Getteurs

Moteur &SystemeCarburant::getMoteurs(int i)
{
    if (isValidMoteurIndex(i))
        return _moteurs[i];

    else
    {
        std::cout << "hors bornes du tableau de moteurs // : " << i << std::endl;
        exit(0);
    }
}

Reservoir &SystemeCarburant::getReservoirs(int i)
{
    if (isValidReservoirIndex(i))
        return _reservoirs[i];

    else
    {
        std::cout << "hors bornes du tableau de reservoirs // : " << i << std::endl;
        exit(0);
    }
}

Vanne &SystemeCarburant::getVannesRes(int i)
{
    if (isValidVanneResIndex(i))
        return _vannesRes[i];

    else
    {
        std::cout << "hors bornes du tableau de vannes RES // : " << i << std::endl;
        exit(0);
    }
}

VanneMatrice &SystemeCarburant::getVannesRM()
{
    return _vannesRM;
}


bool SystemeCarburant::isReservoirsVide()
{
    for (int i = 0; i < _reservoirs.size(); i++)
    {
        if (!_reservoirs[i].isVide())
            return false;
    }

    return true;
}

bool SystemeCarburant::isReservoirsDiffusent()
{
    int b = false;

    for (int i = 0; i < _reservoirs.size(); i++)
    {
        if (!getReservoirs(i).getPompePrimaire().isPanne() || !getReservoirs(i).getPompeSecours().isPanne())
        {
            b = true;
        }
    }

    return b;
}





// Fonctions de consommation, parcours les reservoirs et moteurs et déduit la qte de carburant pour alimenter les moteurs
// Consomme si au moins un réservoir contient du carburant


bool SystemeCarburant::consommation()
{
    std::cout << "*** lancement de la consommation" << std::endl;

    if (isReservoirsVide() || !isReservoirsDiffusent())     // si tous vides ou si on peut encore diffuser
    {
        cout << "*** Fin de la consommation ***" << endl;

        for (int i = 0; i < _moteurs.size(); i++)
            _moteurs[i].deleteResObserver();

        for (int i = 0; i < _vannesRes.size(); i++)
            _vannesRes[i].updateColor(QBrush(), false);

        for (int i = 0; i < _vannesRM.vannes().size(); i++)
            _vannesRM.getVannes(i).updateColor(QBrush(), false);

        return false;
    }

    else
    {
        for (int i = 0; i < (int) _reservoirs.size(); i++)
        {
            for (int j = 0; j < (int) _moteurs.size(); j++)
            {
                if (_vannesRM.getEntree(i, j) > 0)     // si vanne fermée
                {

                    if (i == j)
                    {
                        if (_reservoirs[i].isDiffuseCarburant())  // si peut diffuser
                        {
                            double temp = _reservoirs[i].getQteCarburant() - (_moteurs[j].getConso() * _vannesRM.getEntree(i, j));
                            _reservoirs[i].setQteCarburant(temp);           // update de la qte de carburant

                            _moteurs[j].updateResObserver(&(_reservoirs[i]));       // update observer
                        }

                        else
                        {
                            if (&(_reservoirs[i]) == _moteurs[j].reservoirObserver())
                                _moteurs[j].deleteResObserver();
                        }
                    }


                    else        // i != j --> peut alimenter un autre reservoir si les deux pompes sont actifs
                    {
                        if (_reservoirs[i].isPompesDiffusent())
                        {

                            // si le moteur n'est pas déjà alimenté et que le reservoir alimente un seul moteur
                            if (!_moteurs[j].isAlimente() && !_reservoirs[i].alimenteMoteurSup())
                            {
                                double temp = _reservoirs[i].getQteCarburant() - (_moteurs[j].getConso() * _vannesRM.getEntree(i, j));
                                _reservoirs[i].setQteCarburant(temp);

                                _moteurs[j].updateResObserver(&(_reservoirs[i]));
                               _reservoirs[i].updateMoteurSup(_moteurs[j].getNom());

                                // update de la couleur des vannes selon le reservoir qui alimente

                                int v = vanneIndice(i, j);
                                _vannesRM.getVannes(v).updateColor(getReservoirs(i).resObserver()->carbColor(), true);
                            }

                            // alimente le moteur sup qu'il alimente déjà
                            else if (_reservoirs[i].alimenteMoteurSup() && (_reservoirs[i].moteurSupId() == _moteurs[j].getNom()))
                            {
                                double temp = _reservoirs[i].getQteCarburant() - (_moteurs[j].getConso() * _vannesRM.getEntree(i, j));
                                _reservoirs[i].setQteCarburant(temp);
                            }

                            else
                            {
                                cout << "PENALITE !!!" << endl;
                            }
                        }

                        else
                        {
                            if (&(_reservoirs[i]) == _moteurs[j].reservoirObserver())
                            {
                                _moteurs[j].deleteResObserver();
                                _reservoirs[i].deleteMoteurSup();

                                int v = vanneIndice(i, j);
                                _vannesRM.getVannes(v).updateColor(QBrush(), false);
                            }
                        }

                    }

                }

                // Si la vanne est fermée

                else
                {
                    if (&(_reservoirs[i]) == _moteurs[j].reservoirObserver())
                    {
                        _moteurs[j].deleteResObserver();

                        int v = vanneIndice(i, j);
                        _vannesRM.getVannes(v).updateColor(QBrush(), false);
                    }
                }

            }

        }

        //
        transfertCarburant();
        updateDisplay();

        return true;
    }

}







// on vérifie s'il y a des vannes fermées et on équilibre le niveau de carburant dans les réservoirs

void SystemeCarburant::transfertCarburant()
{
    // si les deux vannes sont fermées et qu'au moins 1 res non vide

    if ((!_vannesRes[0].isOuvert()) && (!_vannesRes[1].isOuvert()) && (!isReservoirsVide()))
    {
        double temp = (_reservoirs[0].getQteCarburant() + _reservoirs[1].getQteCarburant()
                + _reservoirs[2].getQteCarburant()) / 3;

        // update des reserves
        double qRes = _reservoirs[1].setQteCarburant(temp);
        _reservoirs[0].setQteCarburant(temp + qRes/2);      // on répartit le reste dans les deux autres reservoirs
        _reservoirs[2].setQteCarburant(temp + qRes/2);

        std::cout << "*** transfert de carburant entre les trois reservoirs" << std::endl;

        getVannesRes(0).vanneObserver()->setBcirculer(true);
        getVannesRes(1).vanneObserver()->setBcirculer(true);
    }

    // si seule la vanne VT12 est fermée et res1 ou res2 non vide

    else if (!_vannesRes[0].isOuvert() && (!_reservoirs[0].isVide() || !_reservoirs[1].isVide()))
    {
        double temp = (_reservoirs[0].getQteCarburant() + _reservoirs[1].getQteCarburant()) / 2;

        // update des reserves
        double qRes = _reservoirs[1].setQteCarburant(temp);
        _reservoirs[0].setQteCarburant(temp + qRes);

        std::cout << "*** transfert de carburant entre " << _reservoirs[0].getNom() << " et "
                  << _reservoirs[1].getNom() << std::endl;

        getVannesRes(0).vanneObserver()->setBcirculer(true);
    }

    // Si seule la vanne VT23

    else if (!_vannesRes[1].isOuvert() && (!_reservoirs[1].isVide() || !_reservoirs[2].isVide()))
    {
        double temp = (_reservoirs[1].getQteCarburant() + _reservoirs[2].getQteCarburant()) / 2;

        // update des reserves
        double qRes = _reservoirs[1].setQteCarburant(temp);
        _reservoirs[2].setQteCarburant(temp + qRes);

        std::cout << "*** transfert de carburant entre " << _reservoirs[1].getNom() << " et "
                  << _reservoirs[2].getNom() << std::endl;

        getVannesRes(1).vanneObserver()->setBcirculer(true);
    }

    else
    {
        for (int i = 0; i < _vannesRes.size(); i++)
            getVannesRes(i).vanneObserver()->setBcirculer(false);
    }

    //
    updateDisplay();

}




// Renvoie l'indice de la vanne V en fonction des moteurs et reservoirs concernées

int SystemeCarburant::vanneIndice(int i, int j)
{
    if ((i == 0 && j == 1) || (i == 1 && j == 0))
        return 0;

    else if ((i == 0 && j == 2) || (i == 2 && j == 0))
        return 1;

    else
        return 2;
}

// affichage de l'etat du systeme

void SystemeCarburant::afficher() const
{
    std:: cout << std::endl << "Etat du systeme carburant"<< std::endl;

    for (int i = 0; i < (int) _reservoirs.size(); i++)
    {
        _reservoirs[i].affiche();
    }

    for (int i = 0; i < (int) _moteurs.size(); i++)
    {
        _moteurs[i].affiche();
    }

    for (int i = 0; i < (int) _vannesRes.size(); i++)
    {
        _vannesRes[i].affiche();
    }

    _vannesRM.affiche();
}


// Récupérer la somme de toutes les bonnes décisions

int SystemeCarburant::getControlDecisions()
{
    int cpt = 0;

    for (int i = 0; i < _reservoirs.size(); i++)
        cpt += _reservoirs[i].getCptDecisions();

    return cpt;
}

int SystemeCarburant::getControlResolutions()
{
    int cpt = 0;

    for (int i = 0; i < _reservoirs.size(); i++)
        cpt += _reservoirs[i].getCptResolutions();

    return cpt;
}

int SystemeCarburant::getControlPannes()
{
    int cpt = 0;

    for (int i = 0; i < _reservoirs.size(); i++)
    {
        cout << _reservoirs[i].getCptPannes() << endl;
        cpt += _reservoirs[i].getCptPannes();
    }

    return cpt;
}



// Observers Section

GraphicEtatRM *SystemeCarburant::displayOberserver() const
{
    return _displayOberserver;
}

void SystemeCarburant::addDisplayOberserver(GraphicEtatRM *displayOberserver)
{
    _displayOberserver = displayOberserver;
}

void SystemeCarburant::updateDisplay()
{

    int pval1 = pourcentage(getReservoirs(0));
    int pval2 = pourcentage(getReservoirs(1));
    int pval3 = pourcentage(getReservoirs(2));

    QString level1 = pval1 < 25 ? (pval1 <= 0? "VIDE" : "LOW") : QString::number(getReservoirs(0).getQteCarburant());
    QString level2 = pval2 < 25 ? (pval2 <= 0? "VIDE" : "LOW") : QString::number(getReservoirs(1).getQteCarburant());
    QString level3 = pval3 < 25 ? (pval3 <= 0? "VIDE" : "LOW") : QString::number(getReservoirs(2).getQteCarburant());

    QString rm1 = QString::fromStdString(getMoteurs(0).getResObserverName());
    QString rm2 = QString::fromStdString(getMoteurs(1).getResObserverName());
    QString rm3 = QString::fromStdString(getMoteurs(2).getResObserverName());

    QString tl = QString::number(getReservoirs(0).getQteCarburant() + getReservoirs(1).getQteCarburant()
                                 + getReservoirs(2).getQteCarburant());

    QString cm1 = QString::number(getMoteurs(0).getConso());
    QString cm2 = QString::number(getMoteurs(1).getConso());
    QString cm3 = QString::number(getMoteurs(2).getConso());


    _displayOberserver->updateBarValues(pval1, pval2, pval3);
    _displayOberserver->updateLevelRes(level1, level2, level3, tl);
    _displayOberserver->updateResMoteur(rm1, rm2, rm3);
    _displayOberserver->updateConsoMoteur(cm1, cm2, cm3);
}

//
float SystemeCarburant::pourcentage(const Reservoir& res)
{
    if (res.isVide())
        return 0;

    else
        return (float)( (res.getQteCarburant()*100) / res.getCapacite());
}

// Les paramètres de ces fonctions sont facultatifs

void SystemeCarburant::initialise(double r1, double r2, double r3, double m1, double m2, double m3)
{
    getReservoirs(0).initialise(r1);
    getReservoirs(1).initialise(r2);
    getReservoirs(2).initialise(r3);

    getMoteurs(0).initialise(&getReservoirs(0), m1);
    getMoteurs(1).initialise(&getReservoirs(1), m2);
    getMoteurs(2).initialise(&getReservoirs(2), m3);

    // Fermeture des vannes

    for (int i = 0; i < _vannesRes.size(); i++)
        _vannesRes[i].setOuvert(true);

    for (int i = 0; i < _vannesRM.vannes().size(); i++)
        _vannesRM.ouvrirVanne(i);

    // Mise à jour des couleurs

    for (int i = 0; i < _vannesRes.size(); i++)
        _vannesRes[i].updateColor(QBrush(), false);

    for (int i = 0; i < _vannesRM.vannes().size(); i++)
        _vannesRM.getVannes(i).updateColor(QBrush(), false);

    //
    updateDisplay();
}

void SystemeCarburant::initExoConfig(vector<int> vconf)
{
    if (vconf.size() >= 6)
    {
        initialise(vconf[0], vconf[1], vconf[2], vconf[3], vconf[4], vconf[5]);
    }

    else
        cerr << "Tableau de configs incorrecte" << endl;
}

// Reset le modèle

void SystemeCarburant::resetModel()
{
    initialise(0, 0, 0, 0, 0, 0);

    getMoteurs(0).deleteResObserver();
    getMoteurs(1).deleteResObserver();
    getMoteurs(2).deleteResObserver();

    //
    updateDisplay();
}


/* ****** DESTRUCTEUR ****** */
SystemeCarburant::~SystemeCarburant()
{
    //std::cout << "Destruction du systeme carburant" << std::endl;
}


