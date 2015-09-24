#ifndef POMPEPRIMAIRE_H
#define POMPEPRIMAIRE_H

#include "pompe.h"

class PompePrimaire : public Pompe
{
public:
    PompePrimaire(string nom);

    void affiche() const;

    // surcharge opérateurs
    PompePrimaire& operator=(const PompePrimaire& pp);

    ~PompePrimaire();
};

#endif // POMPEPRIMAIRE_H
