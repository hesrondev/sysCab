#include "reservoir.h"

/* ****** CONSTRUCTEURS ****** */

Reservoir::Reservoir(string nom, double capacite) : _pompePrimaire("P11"), _pompeSecours("P12")
{
    _nom = nom;
    setCapacite(capacite);
    _qteCarburant = _capacite;
    _vide = false;
    _moteurSupId = "";

    _pompePanne = false;
    _carbPanne = false;
    _cptDecision = 0;
    _cptPannesResolus = 0;
    _cptPannes = 0;
}

/* ****** METHODES DE LA CLASSE ****** */

void Reservoir::viderCarburant()
{
    setQteCarburant(0);
}

void Reservoir::demarrerPompeSecours()
{
    _pompeSecours.setMarche(true);
    _resObserver->setBSecMarche(_pompeSecours.isMarche());

}

void Reservoir::fermerPompeSecours()
{
    _pompeSecours.setMarche(false);
    _resObserver->setBSecMarche(_pompeSecours.isMarche());

    cout << " __ " << _pompeSecours.isMarche() << endl;
}

// Pannes des pompes

void Reservoir::setPannePompePrimaire()
{
    _pompePrimaire.setPanne(true);
    _resObserver->setBPrimPanne(_pompePrimaire.isPanne());
    _resObserver->setBPrimMarche(!_pompePrimaire.isPanne());
}

void Reservoir::setPannePompeSecours()
{
    _pompeSecours.setPanne(true);
    fermerPompeSecours();
    _resObserver->setBSecPanne(_pompeSecours.isPanne());
}

/* ****** GETTEURS ET SETTEURS ****** */

string Reservoir::getNom() const
{
    return _nom;
}

double Reservoir::getCapacite() const
{
    return _capacite;
}

double Reservoir::getQteCarburant() const
{
    return _qteCarburant;
}

bool Reservoir::isVide() const
{
    return _vide;
}

PompePrimaire Reservoir::getPompePrimaire() const
{
    return _pompePrimaire;
}

PompeSecours Reservoir::getPompeSecours() const
{
    return _pompeSecours;
}

void Reservoir::setNom(string nom)
{
    _nom = nom;
}


// capacite toujours positive
void Reservoir::setCapacite(double capacite)
{
    if (capacite < 0)
        capacite *= -1;

    _capacite = capacite;
}


// la qte ne doit pas être supérieure à la capacite
// renvoie la qte de carburant superflux

double Reservoir::setQteCarburant(double qte)
{
    double qRes = 0;

    if (qte <= 0.9)
    {
        _qteCarburant = 0;
        setVide(true);
    }

    else
    {
        if (qte > _capacite)
        {
            _qteCarburant = _capacite;
            qRes = qte - _capacite;
        }
        else
            _qteCarburant = qte;

        setVide(false);
    }

    // si la qte de carburant a augmenté alors qu'elle était vide (suite à une panne)
    // alors dire que c'est une bonne décision

    if (_carbPanne && _qteCarburant > 0)
    {
        _carbPanne = false;
        _cptDecision++;
        _cptPannesResolus++;
    }

    return qRes;
}

// vide depend de la qte du carburant dans le reservoir
void Reservoir::setVide(bool vide)
{
    _vide = vide;
    _resObserver->setBcirculer(!_vide);
}

void Reservoir::setPrimaire(PompePrimaire pp)
{
    _pompePrimaire = pp;
}

void Reservoir::setSecours(PompeSecours ps)
{
    _pompeSecours = ps;
}

// varifie si un réservoir diffuse du carburant

bool Reservoir::isDiffuseCarburant()
{
    if (isVide())
        return false;

    // Ou si les pompes sont non fonctionnels

    if (_pompePrimaire.isPanne() && (_pompeSecours.isPanne() || !_pompeSecours.isMarche()))
        return false;

    else
        return true;
}

bool Reservoir::isPompesDiffusent()
{
    // Tous les pompes diffusent à la fois et reservoir non vide

    if (!isVide() && !_pompePrimaire.isPanne() && _pompeSecours.isMarche())
        return true;

    else
        return false;
}

/* ****** FONCTIONS UTILITAIRES ****** */

void Reservoir::affiche() const
{
    std::cout << "Caracteristiques du reservoir : " << _nom << std::endl;
    std::cout << "\tcapacite : " << _capacite << std::endl;
    std::cout << "\tqteCarb : " << _qteCarburant << std::endl;
    std::cout << "\tvide ? : " << _vide << std::endl;
    std::cout << std::endl << "\tDecisions : " << _cptDecision << std::endl;
    std::cout << "\tNb pannes : " << _cptPannes << std::endl;
    std::cout << "\tnb Resolus : " << _cptPannesResolus << std::endl;

    _pompePrimaire.affiche();
    _pompeSecours.affiche();
}

// Cette fonction
// Une fois que la pompe a été en panne on garde en mémoire le nom du moteur obs
// On le nettoie une fois que ce dernier aura signalé avoir trouvé preneur

void Reservoir::deleteMoteurSup()
{
    if (!_pompePanne)
        _moteurSupId = "";
}

bool Reservoir::alimenteMoteurSup()
{
    if (_moteurSupId != "")
        return true;
    else
        return false;
}

string Reservoir::moteurSupId() const
{
    return _moteurSupId;
}

void Reservoir::updateMoteurSup(string id)
{
    _moteurSupId = id;
}


// Permet d'avoir une information sur le nombre d moteur alimentés


//

void Reservoir::addResObserver(GraphicReservoir *pp)
{
    _resObserver = pp;
}

void Reservoir::update()
{
    _resObserver->setBPrimMarche(!_pompePrimaire.isPanne());    //le contraire de la panne = marche, car marche par défaut
    _resObserver->setBPrimPanne(_pompePrimaire.isPanne());
    _resObserver->setBSecMarche(_pompeSecours.isMarche());
    _resObserver->setBSecPanne(_pompeSecours.isPanne());
    _resObserver->setBcirculer(!_vide);
}

GraphicReservoir *Reservoir::resObserver() const
{
    return _resObserver;
}

// Initialise avec les valeurs par défaut

void Reservoir::initialise(int capacite)
{
    if (capacite > -1 && _capacite != capacite)
        setCapacite(capacite);

    setQteCarburant(_capacite);
    _pompePrimaire.setPanne(false);
    _pompeSecours.setPanne(false);
    _pompeSecours.setMarche(false);

    _moteurSupId = "";
    _pompePanne = false;
    _carbPanne = false;
    _cptDecision = 0;
    _cptPannesResolus = 0;
    _cptPannes = 0;

    update();
}


// Fonctions de controles de pannes et de décisions

void Reservoir::setPompePanne(bool b)
{
    _pompePanne = b;

    if (b)
        _cptPannes++;
}

void Reservoir::setCarbPanne(bool b)
{
    _carbPanne = b;

    if (b)
        _cptPannes++;
}

int Reservoir::getCptDecisions() const
{
    return _cptDecision;
}

int Reservoir::getCptResolutions() const
{
    return _cptPannesResolus;
}

int Reservoir::getCptPannes() const
{
    return _cptPannes;
}


// Cette fonction est appelé par le moteur comme signale au réservoir
// Elle prend en entrée le nom du moteur signalant et le nouveau reservoir qui va l'alimenter

/*
 * Cas 1: Si après panne d'ue des pompes et qu'une autre a été activée --> Bonne décision
 * Cas 2: Si on reçoit le signal du moteur par défaut et que les deux pompes sont hors service
 *        Cela veut dire que l'utilisateur a alimenté le moteur avec un autre reservoir
 * Cas 2bis: Si parcontre on reçoit le signal du moteur par défaut mais qu'une des pompes était en bonne état mais pas actif --> NON
 * Cas 3: Si on reçoit le signal du moteur sup, on le reset. Noter que dans les autres cas, la panne est résolu mais pas avec la bonne décision
**/

void Reservoir::controlPanneResSignal(const string &sMoteur, const string &sNouvRes)
{
    if (_pompePanne)
    {
        if (sNouvRes == _nom && (sMoteur != moteurSupId()))
        {
            cout << "bonne décision" << endl;
            _cptDecision++;
        }

        else if ((sMoteur != moteurSupId()) && _pompePrimaire.isPanne() && _pompeSecours.isPanne())
        {
            cout << "bonne décision" << endl;
            _cptDecision++;
        }

        else if (sMoteur == moteurSupId())
        {
            _moteurSupId = "";
        }

        _cptPannesResolus++;      // panne résolu
        setPompePanne(false);     // le signal est désactivé dans tous les cas car une décision a été prise
    }

}



/* ****** DESTRUCTEUR ****** */

Reservoir::~Reservoir()
{
    //std::cout << "Destruction de reservoir" << _nom << std::endl;
}


