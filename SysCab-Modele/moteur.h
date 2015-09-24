#ifndef MOTEUR_H
#define MOTEUR_H

#include <iostream>
#include <string>

#include <QVector>
#include "SysCab-Vue/graphiccanal.h"
#include "SysCab-Vue/graphicetatrm.h"
#include "reservoir.h"


using namespace std;

class Moteur
{
public:
    Moteur(string nom, double conso);

    string getNom() const;
    double getConso() const;    

    void setNom(string nom);
    void setConso(double conso);

    void affiche() const;

    GraphicCanal* canalObserver() const;
    Reservoir* reservoirObserver() const;
    void addCanalObserver(GraphicCanal* canal);
    void deleteResObserver();
    bool isAlimente() const;

    void updateResObserver(Reservoir *res);
    void updateCanalObserver(bool b);
    string getResObserverName();

    void initialise(Reservoir* resObs, int conso = 0);

    // controle de pannes et décisions
    void activeControlePanne();

    ~Moteur();

private:
    string _nom;
    double _conso;
    bool _bObserve;

    // objets observés
    GraphicCanal *_canalObserver;
    Reservoir *_reservoirObserver;

    // controle de pannes
    bool _controlePanne;
};

#endif // MOTEUR_H
