#ifndef RESERVOIR_H
#define RESERVOIR_H

#include <iostream>
#include <string>

#include "pompeprimaire.h"
#include "pompesecours.h"
//#include "moteur.h"

#include "SysCab-Vue/graphicreservoir.h"

using namespace std;

class Reservoir
{
public:
    Reservoir(string nom, double capacite);

    void viderCarburant();
    void demarrerPompeSecours();
    void fermerPompeSecours();
    void setPannePompePrimaire();
    void setPannePompeSecours();

    string getNom() const;
    double getCapacite() const;
    double getQteCarburant() const;
    bool isVide() const;
    PompePrimaire getPompePrimaire() const;
    PompeSecours getPompeSecours() const;


    void setNom(string nom);
    void setCapacite(double capacite);
    double setQteCarburant(double qte);
    void setVide(bool vide);
    void setPrimaire(PompePrimaire pp);
    void setSecours(PompeSecours ps);

    bool isDiffuseCarburant();
    bool isPompesDiffusent();

    void affiche() const;

    // Observers Section

    GraphicReservoir *resObserver() const;
    void addResObserver(GraphicReservoir *pp);
    void update();

    void deleteMoteurSup();
    bool alimenteMoteurSup();
    string moteurSupId() const;
    void updateMoteurSup(string id);

    void initialise(int capacite = -1);

    // fonctions de contrôles des pannes et de decisions
    void setPompePanne(bool b);
    void setCarbPanne(bool b);
    int getCptDecisions() const;
    int getCptResolutions() const;
    int getCptPannes() const;
    void controlPanneResSignal(const string& sMoteur, const string& sNouvRes);


    ~Reservoir();



private:
    string _nom;
    double _capacite;
    double _qteCarburant;
    bool _vide;
    PompePrimaire _pompePrimaire;
    PompeSecours _pompeSecours;

    // Objets observés
    GraphicReservoir *_resObserver;
    string _moteurSupId;

    // pannes et décisions
    bool _pompePanne;
    bool _carbPanne;
    int _cptDecision;
    int _cptPannesResolus;
    int _cptPannes;


};

#endif // RESERVOIR_H
