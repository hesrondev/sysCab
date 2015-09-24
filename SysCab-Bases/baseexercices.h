#ifndef BASEEXO_H
#define BASEEXO_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "exercice.h"

using namespace std;



class BaseExercices
{
public:
    BaseExercices();

    Exercice getExo(int i) const;

    void chargerExercices();
    vector<int> strToVect(const string &ligneFichier);

    void afficher();

    vector<Exercice> Exercices() const;
    void setExercices(const vector<Exercice> &Exercices);

    ~BaseExercices();



private:
    vector<Exercice> _Exercices;
    string _cheminFichier;

};

#endif // BASEEXO_H
