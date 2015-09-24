#include "exercice.h"

Exercice::Exercice(vector<int> vectPannes, vector<int> vectLatences) : _Pannes(vectPannes), _Latences(vectLatences), _Config()
{
    _Config.reserve(6);
}

vector<int> Exercice::getPannes() const
{
    return _Pannes;
}

vector<int> Exercice::getLatences() const
{
    return _Latences;
}

void Exercice::afficher()
{
    cout << "----------" << endl;
    cout << _titre << endl;
    cout << _description << endl;
    cout << _astuces << endl;
    cout << "Duree : " << _duree << endl;
    cout << "_Config : " << endl;

    for (int i = 0; i < _Config.size(); i++)
        cout << _Config[i] << " ";
    cout << endl;

    cout << "_Pannes : " << endl;

    for (int i = 0; i < _Pannes.size(); i++)
        cout << _Pannes[i] << " ";
    cout << endl;

    cout << "_Latences : " << endl;

    for (int i = 0; i < _Latences.size(); i++)
        cout << _Latences[i] << " ";
    cout << endl;
}

Exercice::~Exercice()
{

}

double Exercice::Config(int i) const
{
    if (i >= 0 && i < _Config.size())
        return _Config[i];

    else
        return 0;       // par défaut!
}
vector<int> Exercice::Config() const
{
    return _Config;
}

void Exercice::setConfig(const vector<int> &Config)
{
    _Config = Config;
}
int Exercice::duree() const
{
    return _duree;
}

void Exercice::setDuree(int duree)
{
    _duree = duree;
}
string Exercice::titre() const
{
    return _titre;
}

void Exercice::setTitre(const string &titre)
{
    _titre = titre;
}
string Exercice::description() const
{
    return _description;
}

void Exercice::setDescription(const string &description)
{
    _description = description;
}
string Exercice::astuces() const
{
    return _astuces;
}

void Exercice::setAstuces(const string &astuces)
{
    _astuces = astuces;
}






