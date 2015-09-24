#include "baseutilisateurs.h"


BaseUtilisateurs::BaseUtilisateurs()
{
    //
    _cheminFichier = "fic/baseUsers.scb";
    chargerBase();
}


bool BaseUtilisateurs::ajouterUtilisateur(const string& identif, const string& motDePasse)
{
    // vérification de l'id unique

    for (list<Utilisateur>::iterator u = _listeUtilisateurs.begin(); u != _listeUtilisateurs.end(); u++)
    {
        if ((*u).getId() == identif)
            return false;
    }

    // ok si taille id [3, 20], taille mdp [4, 50]

    int idSz = identif.size();
    int mdpSz = motDePasse.size();

    if (idSz < 3 || mdpSz < 4 || idSz > 20 || mdpSz > 50)
    {
        cout << "ID ou MDP trop court/long" << endl;
        return false;
    }

    else
    {
        _listeUtilisateurs.push_back(Utilisateur(identif, motDePasse));
        return true;
    }

}

void BaseUtilisateurs::ajouterUtilisateur(const Utilisateur &user)
{
    _listeUtilisateurs.push_back(user);
}

/* Sauvegarder la base d'utilisateur dans un ficher
 * Parcourt la liste des utilisateurs et écris chaque utilisateur dans le fichier
 * */

void BaseUtilisateurs::sauverBase()
{
    ofstream fluxDeSauvegarde;
    fluxDeSauvegarde.open(_cheminFichier, ios::out | ios::trunc);

    if(fluxDeSauvegarde)
    {
        for (list<Utilisateur>::iterator u = _listeUtilisateurs.begin(); u != _listeUtilisateurs.end(); u++)
        {
            fluxDeSauvegarde << *u;
        }

        fluxDeSauvegarde.close();
    }

    else
        cerr << "[SAUVEGARDE Users] Erreur d'ouverture du fichier" << _cheminFichier << endl;
}

/* Charger la base d'utilisateur à partir d'un fichier
 * Parcourt le fichier et recrées les utilisateurs avec les valeurs stockées
 * */

void BaseUtilisateurs::chargerBase()
{

   ifstream fluxLecture;
   fluxLecture.open(_cheminFichier);

   if (fluxLecture)
   {
       Utilisateur *user;

       string sId;
       string sMdp;
       string s_ligne;
       int n_ligne = 1;

        while (!fluxLecture.eof())
        {
            getline(fluxLecture, s_ligne);

            if (s_ligne == "--//--")  //on passe à un autre utilisateur
            {
                ajouterUtilisateur(*user);
                n_ligne = 1;
                delete user;
            }

            else if (!s_ligne.empty())
            {
                if (n_ligne == 1)
                    sId = s_ligne;

                else if (n_ligne == 2)
                {
                    sMdp = s_ligne;
                    user = new Utilisateur(sId, sMdp);
                }

                else
                {
                    (*user).setVectNotes(n_ligne-3, strToVectNotes(s_ligne));
                }

                n_ligne++;
            }

            else
                cout << "[WARNING] Le fichier a été modifié" << endl;
        }
   }

   else
       cerr << "[CHARGEMENT Users] Erreur d'ouverture du fichier " << _cheminFichier << endl;
}


list<Utilisateur> BaseUtilisateurs::getUserListe() const
{
    return _listeUtilisateurs;
}

int BaseUtilisateurs::getNbUtilisateurs() const
{
    return _nbUtilisateur;
}

//

void BaseUtilisateurs::afficher()
{
    for (list<Utilisateur>::iterator u = _listeUtilisateurs.begin(); u != _listeUtilisateurs.end(); u++)
    {
        (*u).affiche();
    }
}


// Recherche d'un utilisateur dans la base d'utilisateur

Utilisateur* BaseUtilisateurs::rechercherUtilisateur(const string &id, const string &mdp)
{
    for (list<Utilisateur>::iterator u = _listeUtilisateurs.begin(); u != _listeUtilisateurs.end(); u++)
    {
        if ((*u).getId() == id && (*u).getMdp() == mdp)
            return &(*u);
    }

    return NULL;
}

BaseUtilisateurs::~BaseUtilisateurs()
{

}



//fontions utilitaires

// Conversion d'un string (de int) en un tableau de notes (entiers)

vector<int> BaseUtilisateurs::strToVectNotes(const string &ligneFichier)
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

