#ifndef SYSTEMECARBURANT_H
#define SYSTEMECARBURANT_H

#include <vector>

#include "reservoir.h"
#include "vanne.h"
#include "vannematrice.h"
#include "moteur.h"

#include "SysCab-Vue/graphicetatrm.h"

class SystemeCarburant
{
    friend class SysCabClassePrincipale;

public:
    SystemeCarburant();

    void ouvrirVanneRes(int i);
    void fermerVanneRes(int i);
    void ouvrirVanneRM(int i);
    void fermerVanneRM(int i);

    void ouvrirPsecours(int i);
    void fermerPsecours(int i);

    void viderReservoir(int i);
    void pannePprimaire(int i);
    void pannePsecours(int i);

    bool isValidReservoirIndex(int i);
    bool isValidMoteurIndex(int i);
    bool isValidVanneResIndex(int i);

    Moteur& getMoteurs(int i);
    Reservoir& getReservoirs(int i);
    Vanne& getVannesRes(int i);
    VanneMatrice& getVannesRM();

    bool isReservoirsVide();
    bool isReservoirsDiffusent();
    bool consommation();
    void transfertCarburant();

    int vanneIndice(int i, int j);
    void afficher() const;

    int getControlDecisions();
    int getControlResolutions();
    int getControlPannes();

    ~SystemeCarburant();


    // fonctions de la gestion graphique

    GraphicEtatRM *displayOberserver() const;
    void addDisplayOberserver(GraphicEtatRM *displayOberserver);
    void updateDisplay();
    float pourcentage(const Reservoir &res);

    //initialisations
    void initialise(double r1 = -1, double r2 = -1, double r3 = -1, double m1 = -1, double m2 = -1, double m3 = -1);
    void initExoConfig(vector<int> vconf);
    void resetModel();


private:
    vector <Reservoir> _reservoirs;
    vector <Moteur> _moteurs;
    vector <Vanne> _vannesRes;
    VanneMatrice _vannesRM;

    // Objets observés
    GraphicEtatRM *_displayOberserver;

};

#endif // SYSTEMECARBURANT_H
