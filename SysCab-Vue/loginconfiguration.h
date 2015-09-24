#ifndef LOGINCONFIGURATION_H
#define LOGINCONFIGURATION_H


#include <iostream>

using namespace std;

#include <QLabel>
#include <QAction>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPalette>
#include <QGroupBox>
#include <QToolBar>

#include "widgetparent.h"

class LoginConfiguration : public QWidget
{
    Q_OBJECT

    friend class LoginView;

public:
    LoginConfiguration(bool cnx);

    void initComps();
    void connexionConfig();
    void registerConfig();

    ~LoginConfiguration();


private:
    QLineEdit *_idText;
    QLineEdit *_passwordText;

    QPushButton *_validButton;
    QPushButton *_registerButton;

    QAction *_actionRemberMe;
    QAction *_creerCompteAction;
    QAction *_connexionAction;
    QLabel  *_headerLabel;
    QLabel *_compteLabel;
    QLabel *_licenseLabel;
    QLabel *_idLabel;
    QLabel *_passwordLabel;
    QLabel *_incorrectIdsLabel;

};
#endif // LOGINCONFIGURATION_H
