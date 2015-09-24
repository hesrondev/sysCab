#ifndef VANNEMATRICE_H
#define VANNEMATRICE_H

#include <iostream>
#include <string>
#include <vector>

#include "vanne.h"

using namespace std;

class VanneMatrice
{
public:
    VanneMatrice();

    void ouvrirVanne(int i);
    void fermerVanne(int i);

    Vanne &getVannes(int i);
    int getEntree(int lig, int col);
    void setEntree(int lig, int col, int value);

    void affiche() const;

    ~VanneMatrice();

    vector<Vanne> vannes() const;
    void setVannes(const vector<Vanne> &vannes);

private:
    vector <Vanne> _vannes;
    int _matrice[3][3];
};

#endif // VANNEMATRICE_H
