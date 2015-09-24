#ifndef POMPESECOURS_H
#define POMPESECOURS_H

#include "pompe.h"

class PompeSecours : public Pompe
{
public:
    PompeSecours(string nom);

    bool isMarche() const;
    void setMarche(bool marche);
    void setPanne(bool panne);      //surcharge de cette fonction

    void affiche() const;

    // surcharge opérateurs
    PompeSecours& operator=(const PompeSecours& ps);

    ~PompeSecours();

private:
    bool _marche;
};

#endif // POMPESECOURS_H
