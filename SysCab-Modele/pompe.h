#ifndef POMPE_H
#define POMPE_H

#include <iostream>
#include <string>

using namespace std;

class Pompe
{
public:
    Pompe(string nom);

    string getNom() const;
    bool isPanne() const;
    void setNom(string nom);
    void setPanne(bool panne);

    virtual void affiche() const = 0;

    ~Pompe();

protected:
    string _nom;
    bool _panne;
};

#endif // POMPE_H
