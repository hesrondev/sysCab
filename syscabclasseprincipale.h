#ifndef SYSCABCLASSEPRINCIPALE_H
#define SYSCABCLASSEPRINCIPALE_H




/*
*
*    CLASSE PRINCIPALE DU PROJET SYSCAB
*
*/

#include <QWidget>
#include <QTimer>

#include "SysCab-Modele/systemecarburant.h"
#include "SysCab-Vue/fenetreprincipale.h"
#include "SysCab-Bases/baseexercices.h"
#include "SysCab-Bases/baseutilisateurs.h"
#include "SysCab-Bases/utilisateur.h"


class SysCabClassePrincipale : public QWidget
{
    Q_OBJECT

public:
    SysCabClassePrincipale();

    void hideMenu();
    void refreshSceneView();
    void refreshWindows_v2();

    void setModeUserPermissions(bool b);
    void setModeLibrePermissions(bool b);
    void setConfigPermissions(bool b);
    void setExercicesPermissions(bool b);

    void mettreEnPause();

    ~SysCabClassePrincipale();


public slots:

    void homeSlot();
    void exercicesWidgetSlot();

    void modeLibreSlot();
    void configWidgetSlot();
    void configModelSlot(double r1, double r2, double r3, double m1, double m2, double m3);

    //void modeUserSlot();

    void VTSlot(int i);
    void VSlot(int i);
    void pompeSecoursSlot(int i);
    void consommationSlot();
    void startPauseSlot(bool EnPause);
    void resetSimulationSlot();
    void astucesWidgetSlot();

    void pannePrimaireSlot();
    void panneSecoursSlot();
    void panneViderResSlot();
    void panneAleatoireSlot();

    void stopSimulationSlot();

    //
    void connexionVerificationSlot(string id, string mdp);
    void registerVerificationSlot(string id, string mdp);

    //
    void tableDeNotesSlot();
    void deconnexionSlot();

    // signaux concernant les challenges

    void openChallengeWidgetSlot(int numExo);
    void startChallengeSlot();
    void stopChallengeSlot();
    void spChallengeSlot(bool bStart);

    void genererChallengePanneSlot();
    void nextChallengeSlot();
    void retryChallengeSlot();



private:
    QTimer *_consoTimer;
    QTimer *_challengeTimer;
    QTimer *_latenceTimer;
    int _tpChallengeRestant;
    int _tpLatenceRestant;

    FenetrePrincipale *_fen;
    TableauDeBord *_tableauDeBord;

    SystemeCarburant _modele;
    BaseExercices _baseExos;
    BaseUtilisateurs _baseUsers;
    Utilisateur *_currentUser;
    int _exoIndex;
    int _latIndex;

    // Permissions
    bool _modeLibre;
    bool _modeUser;

    bool _validConfig;
    bool _activeExoMode;

    bool _activeSimulation;

};

#endif // SYSCABCLASSEPRINCIPALE_H
