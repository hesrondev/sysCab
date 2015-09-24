#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <iostream>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QTimer>

#include "scene.h"
#include "loginview.h"
#include "tableaudebord.h"
#include "barreoutils.h"
#include "indexview.h"
#include "exercicesview.h"
#include "configmodelwidget.h"
#include "challengewidget.h"
#include "notationwidget.h"
#include "notesuserview.h"

#include "customization.h"

using namespace std;


class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

    friend class SysCabClassePrincipale;

public:
    FenetrePrincipale(QWidget *parent = 0);

    void initComps();
    void centrerWidget(QWidget *widget);
    void resetComps();
    void customize();

    // Accesseurs
    int getH() const;
    int getW() const;
    void setH(int h);
    void setW(int w);

    // fonctions de placement
    void setIndexInterface();
    void setLoginInterface();
    void setExercicesInterface();
    void setSceneInterface();

    ~FenetrePrincipale();

public slots:
    void setIndexSlot();
    void setLoginSlot();
    void setExercicesSlot();
    void setSceneSlot();

signals:
    void modeLibreSignal();
    void homeSignal();
    void exercicesSignal();

protected:

    QHBoxLayout *_horiLayout;

    QWidget *_centralView;
    QStatusBar *_statusBar;
    Scene *_vueDeScene;
    LoginView *_loginView;
    BarreOutils *_toolbar;
    IndexView *_indexView;
    ExercicesView *_exercicesView;
    ConfigModelWidget *_configModelWidget;
    ChallengeWidget *_challengeWidget;
    NotationWidget *_notationWidget;
    NotesUserView *_notesUserTable;

    int _W, _H;

};

#endif // FENETREPRINCIPALE_H
