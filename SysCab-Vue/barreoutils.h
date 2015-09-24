#ifndef BARREOUTILS_H
#define BARREOUTILS_H

#include <iostream>
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

#include "optionsview.h"

class BarreOutils : public QToolBar
{
    friend class FenetrePrincipale;
    friend class SysCabClassePrincipale;

public:
    BarreOutils();
    void initComps();
    ~BarreOutils();

private:
    QMenu *_resumeMenu;

    QAction *_idAction;

    QAction *_loginAction;
    QAction *_saveAction;
    QAction *_notesAction;
    QAction *_classementAction;
    QAction *_myIdsAction;
    QAction *_deconnexion;
    QAction *_pauseAction;

    QComboBox *_reservoirMenu;
    QPushButton *_configButton;
    QAction *_pannePrimaireAction;
    QAction *_panneSecoursAction;
    QAction *_panneViderAction;
    QAction *_panneAleatAction;

    OptionsView *_optionsView;

};

#endif // BARREOUTILS_H
