#include "pompesecours.h"

PompeSecours::PompeSecours(string nom) : Pompe(nom)
{
    _marche = false; // initialement arrêtée
}

bool PompeSecours::isMarche() const
{
    return _marche;
}

// on vérifie si la pompe est en panne avant de la mêtre en marche
void PompeSecours::setMarche(bool marche)
{
    if (marche)
    {
        if (!_panne)
            _marche = marche;
        else
            std::cout << "la pompe de secours " << _nom <<" est en panne" << std::endl;
    }

    else
        _marche = marche;


}

// si une pompe tombe en panne, on l'arrête aussi
void PompeSecours::setPanne(bool panne)
{
    if (panne)
    {
        _panne = panne;
        setMarche(false);
    }

    else
        _panne = panne;
}


void PompeSecours::affiche() const
{
    std::cout << "\tPsecours : " << _nom << std::endl;
    std::cout << "\t\tpanne ? : " << _panne << std::endl;
    std::cout << "\t\tmarche ?: " << _marche << std::endl;
}

// surcharge des opérateurs
PompeSecours& PompeSecours::operator=(const PompeSecours& ps)
{
    _nom = ps._nom;
    _panne = ps._panne;
    _marche = ps._marche;

    return *this;
}

PompeSecours::~PompeSecours()
{
    //std::cout << "Destruction de la pompe de secours" << _nom << std::endl;
}

