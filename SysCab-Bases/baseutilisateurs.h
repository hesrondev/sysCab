#ifndef BASEUTILISATEUR_H
#define BASEUTILISATEUR_H


#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <ostream>

#include "utilisateur.h"

using namespace std;


class BaseUtilisateurs
{


public:

    BaseUtilisateurs();

    bool ajouterUtilisateur(const string& identif, const string& motDePasse);
    void ajouterUtilisateur(const Utilisateur& user);

    void sauverBase();
    void chargerBase();

    Utilisateur* rechercherUtilisateur(const string& id, const string& mdp);

    list<Utilisateur> getUserListe() const;

    int getNbUtilisateurs() const;

    void afficher();

    static vector<int> strToVectNotes(const string &ligneFichier);

    ~BaseUtilisateurs();

private:

    int _nbUtilisateur;
    list<Utilisateur> _listeUtilisateurs;
    string _cheminFichier;

};

#endif // BASEUTILISATEUR_H
