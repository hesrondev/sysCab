#include "loginview.h"

LoginView::LoginView() : WidgetParent(370, 400, "Authentification")
{
    _connexion = true;

    // Initialisations
    _loginLayout = new QVBoxLayout;
    _loginLayout->setMargin(0);
    setLayout(_loginLayout);

    _connexionWidget = new LoginConfiguration(true);
    _registerWidget = new LoginConfiguration(false);

    //
    placeCompsInWindow();

    // SIGNAUX ET SLOTS

    QObject::connect(_connexionWidget->_creerCompteAction, SIGNAL(triggered()), this, SLOT(registerConfigSlot()));
    QObject::connect(_registerWidget->_connexionAction, SIGNAL(triggered()), this, SLOT(connexionConfigSlot()));

    QObject::connect(_connexionWidget->_validButton, SIGNAL(clicked()), this, SLOT(connexionIdSlot()));
    QObject::connect(_registerWidget->_registerButton, SIGNAL(clicked()), this, SLOT(registerIdSlot()));

    QObject::connect(_connexionWidget->_passwordText, SIGNAL(returnPressed()), this, SLOT(connexionIdSlot()));
    QObject::connect(_registerWidget->_passwordText, SIGNAL(returnPressed()), this, SLOT(connexionIdSlot()));
    QObject::connect(_connexionWidget->_idText, SIGNAL(returnPressed()), this, SLOT(connexionIdSlot()));
    QObject::connect(_registerWidget->_idText, SIGNAL(returnPressed()), this, SLOT(connexionIdSlot()));

    QObject::connect(_connexionWidget->_idText, SIGNAL(textEdited(QString)), this, SLOT(resetIdsErrorSlot(QString)));
    QObject::connect(_connexionWidget->_passwordText, SIGNAL(textEdited(QString)), this, SLOT(resetIdsErrorSlot(QString)));
    QObject::connect(_registerWidget->_idText, SIGNAL(textEdited(QString)), this, SLOT(resetIdsErrorSlot(QString)));
    QObject::connect(_registerWidget->_passwordText, SIGNAL(textEdited(QString)), this, SLOT(resetIdsErrorSlot(QString)));

}


// Cette fonction place les composants dans la fenêtre

void LoginView::placeCompsInWindow()
{
    if (_connexion)
    {
        _loginLayout->addWidget(_connexionWidget);
    }

    else
    {
        _loginLayout->addWidget(_registerWidget);
    }

}

// Détache tous les widgets modifiables de la fenêtre

void LoginView::resetComps()
{
    _connexionWidget->setParent(NULL);
    _registerWidget->setParent(NULL);
}

void LoginView::viderChamps()
{
    // réinitialiser les widgets
    _connexionWidget->_idText->setText("");
    _connexionWidget->_passwordText->setText("");
    _connexionWidget->_incorrectIdsLabel->setText("");
    _registerWidget->_idText->setText("");
    _registerWidget->_passwordText->setText("");
    _registerWidget->_incorrectIdsLabel->setText("");
}


// Cette fonction affiche le message d'erreur "msg" en cas d'erreur de connexion

void LoginView::registerWarnings(const QString &msg)
{
    _registerWidget->_incorrectIdsLabel->setText(msg);
}

// Cette fonction affiche le message d'erreur "msg" en cas d'erreur d'enregistrement

void LoginView::connexionWarnings(const QString &msg)
{
    _connexionWidget->_incorrectIdsLabel->setText(msg);
}




/* ****** SLOTS ****** */

void LoginView::connexionConfigSlot()
{
    // on réinitialise le widget avant de le détacher de l'interface

    _registerWidget->setParent(NULL);
    _registerWidget->_idText->setText("");
    _registerWidget->_passwordText->setText("");
    _registerWidget->_incorrectIdsLabel->setText("");

    _connexion = true;
    placeCompsInWindow();
}

void LoginView::registerConfigSlot()
{
    _connexionWidget->setParent(NULL);
    _connexionWidget->_idText->setText("");
    _connexionWidget->_passwordText->setText("");
    _connexionWidget->_incorrectIdsLabel->setText("");

    _connexion = false;
    placeCompsInWindow();
}

// la connexion et la création génèrent chacun un signal qui envoie à son tour les valeurs des champs id et mdp

void LoginView::connexionIdSlot()
{

    // récupération et conversion des champs QString en string
    string id = _connexionWidget->_idText->text().toStdString();
    string mdp = _connexionWidget->_passwordText->text().toStdString();


    if (id != "" && mdp != "")
    {
        emit connexionIdSignal(id, mdp);
    }

    else
    {
        connexionWarnings("Veuillez remplir tous les champs obligatoires!");    // affichage du msg d'erreur
    }

}

void LoginView::registerIdSlot()
{
    // récupération et conversion des champs QString en string
    string id = _registerWidget->_idText->text().toStdString();
    string mdp = _registerWidget->_passwordText->text().toStdString();

    if (id != "" && mdp != "")
    {
        emit registerIdSignal(id, mdp);
    }

    else
    {
        registerWarnings("Veuillez remplir tous les champs obligatoires!");
    }
}


// Après erreur de remplissage, si on clique sur un des champs id ou mdp, on enlève le texte d'erreur

void LoginView::resetIdsErrorSlot(QString qs)
{
    if (_connexion)
    {
        if (_connexionWidget->_incorrectIdsLabel->text() != "")
            _connexionWidget->_incorrectIdsLabel->setText("");
    }

    else
    {
        if (_registerWidget->_incorrectIdsLabel->text() != "")
            _registerWidget->_incorrectIdsLabel->setText("");
    }
}




// Destructeur
LoginView::~LoginView()
{
    cout << "Destruction de loginView" << endl;

    std::cout << "Destruction de LoginView" << std::endl;

    delete _loginLayout;
    delete _connexionWidget;
    delete _registerWidget;

    std::cout << "-> Fin de la destruction" << std::endl;
}
