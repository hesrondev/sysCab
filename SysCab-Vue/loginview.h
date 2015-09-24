#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <iostream>
#include "widgetparent.h"
#include "loginconfiguration.h"

using namespace std;

#include <QVBoxLayout>



class LoginView : public WidgetParent
{
    Q_OBJECT

    friend class FenetrePrincipale;

public:
    LoginView();

    void placeCompsInWindow();
    void resetComps();
    void viderChamps();
    void connexionWarnings(const QString &msg);
    void registerWarnings(const QString &msg);

    ~LoginView();

public slots:
    void connexionConfigSlot();
    void registerConfigSlot();
    void connexionIdSlot();
    void registerIdSlot();

    void resetIdsErrorSlot(QString qs);

signals:
    void connexionIdSignal(string id, string mdp);
    void registerIdSignal(string id, string mdp);


private:

    QVBoxLayout *_loginLayout;
    LoginConfiguration *_connexionWidget;
    LoginConfiguration *_registerWidget;

    bool _connexion;

};

#endif // LOGINVIEW_H
