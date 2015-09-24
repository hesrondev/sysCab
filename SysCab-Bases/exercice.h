#ifndef EXOS_H
#define EXOS_H

using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


class Exercice
{
public:
    Exercice(vector<int> vectPannes, vector<int> vectLatences);
    //int getPanne(int i);
    //int getLatence(int i);
    vector<int> getPannes() const;
    vector<int> getLatences() const;
    void afficher();
    ~Exercice();

    double Config(int i) const;
    vector<int> Config() const;
    void setConfig(const vector<int> &Config);

    int duree() const;
    void setDuree(int duree);

    string titre() const;
    void setTitre(const string &titre);

    string description() const;
    void setDescription(const string &description);

    string astuces() const;
    void setAstuces(const string &astuces);

private:
    vector<int> _Pannes;
    vector<int> _Latences;
    vector<int> _Config;
    int _duree;
    string _titre;
    string _description;
    string _astuces;
};

#endif // EXOS_H
