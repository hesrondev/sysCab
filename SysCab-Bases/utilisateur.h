#ifndef UTILISATEUR_H
#define UTILISATEUR_H

using namespace std;


#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//#include "fonctionsUtilitaires.cpp"

class Utilisateur
{
    friend ostream& operator<<(ostream& flux, const Utilisateur& user);

public:

    Utilisateur(const string& user, const string& motDePasse);

    void ajouterNote(int numExo, int note);
    void setVectNotes(int numExo, vector<int> vNotes);

    int getNbExosRealises();
    string getId() const;
    string getMdp() const;
    vector <vector <int> > getExoNotes() const;

    void setId(const string& id);
    void setMdp(const string& mdp);

    void afficherNote();
    void affiche();
    
    

    ~Utilisateur();

private:
    string _id;
    string _mdp;
    vector <vector<int>> _exoNote;

};


#endif // UTILISATEUR_H
