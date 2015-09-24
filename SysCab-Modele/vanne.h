#ifndef VANNE_H
#define VANNE_H

#include <iostream>
#include <string>

#include "SysCab-Vue/graphicvanne.h"

using namespace std;

class Vanne
{
public:
    Vanne(string nom);

    string getNom() const;
    bool isOuvert() const;

    void setNom(string nom);
    void setOuvert(bool ouv);

    void affiche() const;

    GraphicVanne *vanneObserver() const;
    void addVanneObserver(GraphicVanne *vanneObserver);
    void update();
    void updateColor(const QBrush& carbColor, bool b);

    ~Vanne();



private:
    string _nom;
    bool _ouvert;

    // Objets Observés
    GraphicVanne *_vanneObserver;
};

#endif // VANNE_H
