#include "pompe.h"

Pompe::Pompe(string nom)
{
    _nom = nom;
    _panne = false; // initialement en bon état
}

string Pompe::getNom() const
{
    return _nom;
}

bool Pompe::isPanne() const
{
    return _panne;
}

void Pompe::setNom(string nom)
{
    _nom = nom;
}

void Pompe::setPanne(bool panne)
{
    _panne = panne;
}

Pompe::~Pompe()
{

}

