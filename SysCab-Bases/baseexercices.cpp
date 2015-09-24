#include "baseexercices.h"

BaseExercices::BaseExercices(): _Exercices()
{
    _cheminFichier = "fic/baseExos";
    _Exercices.reserve(15);
    chargerExercices();
}

Exercice BaseExercices::getExo(int i) const
{
    if (i >= 0 && i < _Exercices.size())
        return _Exercices[i];
}

void BaseExercices::chargerExercices()
{
    fstream fluxDeLecture;
    fluxDeLecture.open(_cheminFichier);

    if (fluxDeLecture)
    {
        int cpt = 1;
        int index = 0;
        string line;
        string strTemp = "";
        vector<int> vtemp;

        while (!fluxDeLecture.eof())
        {
            getline(fluxDeLecture, line);

            if (line == "--//--")
            {
                cpt = 1;
                strTemp = "";
                index++;
            }

            else if (!line.empty())
            {
                if (cpt == 1)
                    vtemp = strToVect(line);

                else if (cpt == 2)
                    _Exercices.push_back(Exercice(vtemp, strToVect(line)));

                else if (cpt == 3)
                    _Exercices[index].setConfig(strToVect(line));

                else if (cpt == 4)
                    _Exercices[index].setDuree(stoi(line));

                else if (cpt == 5)
                    _Exercices[index].setTitre(line);

                else if (cpt == 6)
                    _Exercices[index].setAstuces(line);

                else if (cpt == 7)
                    strTemp = line +"\n";

                else
                {
                    strTemp += line;
                    _Exercices[index].setDescription(strTemp);
                }

                cpt++;
            }

            else
                cout << "[WARNING] le fichier a été modifié !!!" << endl;
        }
    }

    else
        cerr << "[CHARGEMENT Exos] Erreur lors de l'ouverture du fichier: " << _cheminFichier << endl;
}


// Conversion d'un string (de int) en un tableau de notes (entiers)

vector<int> BaseExercices::strToVect(const string &ligneFichier)
{
    vector <int> vectNotes;

    int j = 0;
    string stemp = "";

    for (int i = 0; i < ligneFichier.size(); i++)
    {
        if (ligneFichier[i] != ' ')
        {
            j = i;

            while ((ligneFichier[j] != ' ') && (j < ligneFichier.size()))
                j++;

            stemp = ligneFichier.substr(i, j-i);
            vectNotes.push_back(stoi(stemp));

            i = j;
        }
    }

    return vectNotes;
}


// affichage de la base
void BaseExercices::afficher()
{
    for (int i = 0; i < _Exercices.size(); i++)
        _Exercices[i].afficher();
}


BaseExercices::~BaseExercices()
{

}
vector<Exercice> BaseExercices::Exercices() const
{
    return _Exercices;
}

void BaseExercices::setExercices(const vector<Exercice> &Exercices)
{
    _Exercices = Exercices;
}


