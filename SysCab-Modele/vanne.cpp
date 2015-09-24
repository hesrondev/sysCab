#include "vanne.h"

Vanne::Vanne(string nom)
{
    _nom = nom;
    _ouvert = true; // initialement ouvert
}

string Vanne::getNom() const
{
    return _nom;
}

bool Vanne::isOuvert() const
{
    return _ouvert;
}

void Vanne::setNom(string nom)
{
    _nom = nom;
}

void Vanne::setOuvert(bool ouv)
{
    _ouvert = ouv;

    update();
}

void Vanne::affiche() const
{
    std::cout << "Vanne : " << _nom << std::endl;
    std::cout << "\t\touvert ? : " << _ouvert << std::endl;
}


// Observers Section
GraphicVanne *Vanne::vanneObserver() const
{
    return _vanneObserver;
}

void Vanne::addVanneObserver(GraphicVanne *vanneObserver)
{
    _vanneObserver = vanneObserver;
}

void Vanne::updateColor(const QBrush &carbColor, bool b)
{
    if (b)
        _vanneObserver->setCarbColor(carbColor);

    _vanneObserver->setBcirculer(b);
}

void Vanne::update()
{
    _vanneObserver->setOpen(_ouvert);
}



Vanne::~Vanne()
{
     //std::cout << "Destruction de la vanne : " << _nom << std::endl;
}

