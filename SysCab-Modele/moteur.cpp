#include "moteur.h"

Moteur::Moteur(string nom, double conso)
{
    _nom = nom;
    _conso = conso;
    _bObserve = false;

    _reservoirObserver = NULL;
    _canalObserver = NULL;

    _controlePanne = false;

}

string Moteur::getNom() const
{
    return _nom;
}

double Moteur::getConso() const
{
    return _conso;
}

void Moteur::setNom(string nom)
{
    _nom = nom;
}

void Moteur::setConso(double conso)
{
    _conso = conso;
}

void Moteur::affiche() const
{
    std::cout << "Moteur : " << _nom << std::endl;
    std::cout << "\tconso : " << _conso << std::endl;
}

GraphicCanal *Moteur::canalObserver() const
{
    return _canalObserver;
}

Reservoir *Moteur::reservoirObserver() const
{
    return _reservoirObserver;
}


// Un moteur observe le reservoir qui l'alimente et le canal graphique

void Moteur::addCanalObserver(GraphicCanal *canal)
{
    _canalObserver = canal;
}

void Moteur::deleteResObserver()
{
    _bObserve = false;
    updateCanalObserver(false);     // si je supprime l'observer, je vide le canal
}

bool Moteur::isAlimente() const
{
    return _bObserve;
}


// Si le moteur vient à être alimenté
// On vérifie s'il était dans un état de panne

void Moteur::updateResObserver(Reservoir *res)
{
    if (_controlePanne)
    {
        _controlePanne = false;
        _reservoirObserver->controlPanneResSignal(_nom, res->getNom());
    }

    // Si le nouveau reservoir est différent alors on change
    // On avertit alors le précédent qu'il n'observe plus ce moteur
    // le delete ici intervient quant le reservoir prioritaire veut reprendre la main

    if (_reservoirObserver != res)
    {
         if (_reservoirObserver != NULL)
            _reservoirObserver->deleteMoteurSup();

        _reservoirObserver = res;
    }


    _bObserve = true;
    updateCanalObserver(true);          // si j'ajoute un observer, je rempli le canal
}

// Met à jour la couleur du canal en fonction du reservoir alimentant
// et du booléen indicant si du carburant passe dans le canal

void Moteur::updateCanalObserver(bool b)
{
    if (b)
    {
        if (_canalObserver != NULL)
            _canalObserver->setColor(_reservoirObserver->resObserver()->carbColor());
    }

    if (_canalObserver != NULL)
        _canalObserver->setBcirculer(b);

}

// Renvoie le nom du reservoir qu'il l'alimente

string Moteur::getResObserverName()
{
    if (_bObserve)
        return _reservoirObserver->getNom();

    else
        return "---";
}

// Fonction qui (ré)initialise le moteur avec les valeurs défauts
void Moteur::initialise(Reservoir* resObs, int conso)
{
    if (conso > -1 && conso != _conso)
        _conso = conso;

    _reservoirObserver = resObs;

    _controlePanne = false;
}


// Cette fonction fait passer le moteur dans un état de panne
// On active le controleur de panne, on incrémente le nb de pannes
// On dit que le moteur n'est plus alimenté

void Moteur::activeControlePanne()
{
    deleteResObserver();
    _controlePanne = true;
}


Moteur::~Moteur()
{
    //std::cout << "Destruction du moteur : " << _nom << std::endl;
}

