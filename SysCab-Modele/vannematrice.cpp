#include "vannematrice.h"

/* ****** CONSTRUCTEURS ****** */

VanneMatrice::VanneMatrice() : _vannes()
{
    // initialisation des vannes reliant les reservoirs aux moteurs

    _vannes.reserve(3);                     // reserve la memoire pour l'allocation des vannes
    _vannes.push_back(Vanne("V12"));
    _vannes.push_back(Vanne("V13"));
    _vannes.push_back(Vanne("V23"));

    // initialisation de la matrice de cout de transport

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
                _matrice[i][j] = 1;

            else
                _matrice[i][j] = 0;
        }

}

/* Ouvrir la vanne à l'indice i du tableau
 * Occasionne la modification de la matrice
 */

void VanneMatrice::ouvrirVanne(int i)
{
    if ((i >= 0) && (i < (int) _vannes.size()))
    {
        _vannes[i].setOuvert(true);

        switch(i)       // modification de la matrice selon la valeur de i
        {
            case 0:
                setEntree(0, 1, 0);
                setEntree(1, 0, 0);
                break;
            case 1:
                setEntree(0, 2, 0);
                setEntree(2, 0, 0);
                break;
            case 2:
                setEntree(1, 2, 0);
                setEntree(2, 1, 0);
                break;
        }

        std::cout << "*** ouverture vanne : " << _vannes[i].getNom() << std::endl;
    }
}

void VanneMatrice::fermerVanne(int i)
{
    if ((i >= 0) && (i < (int) _vannes.size()))
    {
        _vannes[i].setOuvert(false);

        switch(i)
        {
            case 0:
                setEntree(0, 1, 2);
                setEntree(1, 0, 2);
                break;
            case 1:
                setEntree(0, 2, 2);
                setEntree(2, 0, 2);
                break;
            case 2:
                setEntree(1, 2, 2);
                setEntree(2, 1, 2);
                break;
        }

        std::cout << "*** fermeture vanne : " << _vannes[i].getNom() << std::endl;
    }
}

// renvoie une copie pour avoir la possibilité de modifier à l'extérieur
Vanne& VanneMatrice::getVannes(int i)
{
    if ((i >= 0) && (i < (int) _vannes.size()))
        return _vannes[i];

    else
    {
        std::cout << "hors bornes du tableau de vannes // : " << i << std::endl;
        exit(0);
    }
}

int VanneMatrice::getEntree(int lig, int col)
{
    if ((lig >= 0 && lig < 3) && (col >= 0 && col < 3))
        return _matrice[lig][col];

    else
        return 0;
}

void VanneMatrice::setEntree(int lig, int col, int value)
{
    if ((lig >= 0 && lig < 3) && (col >= 0 && col < 3))
        _matrice[lig][col] = value;
}

vector<Vanne> VanneMatrice::vannes() const
{
    return _vannes;
}

void VanneMatrice::setVannes(const vector<Vanne> &vannes)
{
    _vannes = vannes;
}






void VanneMatrice::affiche() const
{
    std::cout << "Etat des connexions reservoirs - moteurs" << std::endl;

    for (int i = 0; i < (int) _vannes.size(); i++)
    {
        std::cout << "\t";
        _vannes[i].affiche();
    }

    std::cout << "\tmatrice des couts d'alimentation" << std::endl;

    for (int i = 0; i < 3; i++)
    {
        std::cout << "\t";
        for (int j = 0; j < 3; j++)
        {
            std:: cout << _matrice[i][j] << " ";
        }
        std::cout << std::endl;
    }
}



VanneMatrice::~VanneMatrice()
{
    //std::cout << "Destruction des vannes de connexion" << std::endl;
}
