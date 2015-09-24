#include "utilisateur.h"


using namespace std;


Utilisateur::Utilisateur(const string &user, const string &motDePasse): _id(user), _mdp(motDePasse), _exoNote()
{
    _exoNote.reserve(15);

    for (int i = 0; i < 15; i++)
    {
        vector <int> vect;
        _exoNote.push_back(vect);
    }
}

string Utilisateur::getId() const
{
    return _id;
}


void Utilisateur::setId(const string &id)
{
    _id = id;
}

string Utilisateur::getMdp() const
{
    return _mdp;
}

void Utilisateur::setMdp(const string &mdp)
{
    _mdp = mdp;
}

vector<vector<int> > Utilisateur::getExoNotes() const
{
    return _exoNote;
}


void Utilisateur::ajouterNote(int numExo, int note)
{
    if (numExo < 16 && numExo >= 0)
        _exoNote [numExo].push_back(note);
}

void Utilisateur::setVectNotes(int numExo, vector<int> vNotes)
{
    if (numExo < 16 && numExo >= 0)
        _exoNote[numExo] = vNotes;
}

// Renvoie le nb d'exos réalisés en comptant les tableaux non vides

int Utilisateur::getNbExosRealises()
{
    int cpt = 0;

    for (int i = 0; i < _exoNote.size(); i++)
    {
        if (!_exoNote[i].empty())
            cpt++;
    }

    return cpt;
}

void Utilisateur::afficherNote()
{
    for (int i = 0; i < _exoNote.size();i++)
    {    
        if (!_exoNote[i].empty())
        {
            cout << i+1 <<" : ";

            for (int j = 0; j < _exoNote[i].size(); j++)
                cout << _exoNote[i][j] << "  ";

            cout << endl;
        }
    }
}

// Affichage des champs

void Utilisateur::affiche()
{
    cout << "ID : " << _id  << endl;
    cout << "MDP : " << _mdp << endl;
    afficherNote();
    cout << endl;
}


Utilisateur::~Utilisateur()
{
    //cout << "destruction de l'utilisateur " << endl;
}


// *************************

// fonctions utilitaires

// fonctions de conversion d'un tableau d'entiers en chaine de caractères

string vectToString(vector<int> vect)
{
    string str = "";

    for (int i = 0; i < vect.size(); i++)
    {
        str += to_string(vect[i]) + " ";
    }

    return str;
}

// fonctions amies

ostream& operator<<(ostream& flux, const Utilisateur& user)
{
    flux << user.getId() << endl;
    flux << user.getMdp() << endl;

    for (int i = 0; i < user.getExoNotes().size(); i++)
    {
        if (!user.getExoNotes()[i].empty())
            flux << vectToString(user.getExoNotes()[i]) << endl;
    }

    flux << "--//--" << endl;

    return flux;
}


