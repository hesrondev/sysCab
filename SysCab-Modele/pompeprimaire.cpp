#include "pompeprimaire.h"

PompePrimaire::PompePrimaire(string nom) : Pompe(nom)
{

}

void PompePrimaire::affiche() const
{
    std::cout << "\tPprimaire ? : " << _nom << std::endl;
    std::cout << "\t\tpanne ? : " << _panne << std::endl;
}

// surcharge des opérateurs
PompePrimaire& PompePrimaire::operator=(const PompePrimaire& pp)
{
    _nom = pp._nom;
    _panne = pp._panne;

    return *this;
}

PompePrimaire::~PompePrimaire()
{
    //std::cout << "Destruction de la pompe primaire" << _nom << std::endl;
}

