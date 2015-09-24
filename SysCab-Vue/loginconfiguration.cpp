#include "loginconfiguration.h"

LoginConfiguration::LoginConfiguration(bool cnx)
{
    initComps();

    if (cnx)                // si vrai, on charge la configuration connexion sinon celle de la création
        connexionConfig();
    else
        registerConfig();

}

// Initialisation des composants
void LoginConfiguration::initComps()
{
    // Initialisations des labels
    _headerLabel = new QLabel;
    _compteLabel = new QLabel;
    _licenseLabel = new QLabel("En cliquant sur Créer compte, j'accepte les conditions\n"
                               "d'utilisation et la politique de confidentialité");

    _idLabel = new QLabel(tr("Identifiant"));
    _passwordLabel = new QLabel(tr("Mot de passe"));

    _idLabel->setFixedHeight(15);
    _passwordLabel->setFixedHeight(15);

    _idText = new QLineEdit;
    _passwordText = new QLineEdit;
    _passwordText->setEchoMode(QLineEdit::Password);

    _incorrectIdsLabel = new QLabel;

    _validButton = new QPushButton(tr("Connexion"));
    _registerButton = new QPushButton(tr("Créer un compte"));
    _actionRemberMe = new QAction(tr("Mot de passe oublié ?"), this);
    _connexionAction = new QAction(tr("Connexion"), this);
    _creerCompteAction = new QAction(tr("Créer un compte"), this);

    // dimensions
    _headerLabel->setFixedSize(320, 40);
    _licenseLabel->setFixedSize(260, 30);
    _idText->setFixedSize(260, 30);
    _passwordText->setFixedSize(260, 30);
    _validButton->setFixedSize(260, 30);
    _registerButton->setFixedSize(260, 30);

    _compteLabel->setFixedWidth(320);

    _headerLabel->setAlignment(Qt::AlignCenter);
    _compteLabel->setAlignment(Qt::AlignCenter);

    // identification des widgets
    _headerLabel->setObjectName("title");
    _incorrectIdsLabel->setObjectName("errorMsg");
    _licenseLabel->setObjectName("license");
    _compteLabel->setObjectName("compteLabel");
    _validButton->setObjectName("validButton");
    _registerButton->setObjectName("regButton");
}

// Groupe de widgets pour la connexion

void LoginConfiguration::connexionConfig()
{
    //

    QGroupBox *connexionGroupBox = new QGroupBox;
    connexionGroupBox->setFixedSize(320, 280);

    QVBoxLayout *connexionLayout = new QVBoxLayout;
    connexionLayout->setSpacing(0);

    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupLayout->setMargin(30);

    QSpacerItem* space1 = new QSpacerItem(380, 10);
    //QSpacerItem* idSpace = new QSpacerItem(380, 30);

    QToolBar *mdpToolbar = new QToolBar;
    mdpToolbar->setFixedWidth(260);
    mdpToolbar->addAction(_actionRemberMe);

    QToolBar *compteToolbar = new QToolBar;
    compteToolbar->setFixedWidth(260);

    _incorrectIdsLabel->setFixedSize(380, 15);

    // header
    _headerLabel->setText(tr("Connexion"));

     // body
    groupLayout->addWidget(_idLabel);
    groupLayout->addWidget(_idText);
    groupLayout->addSpacerItem(space1);
    groupLayout->addWidget(_passwordLabel);
    groupLayout->addWidget(_passwordText);
    groupLayout->addWidget(_incorrectIdsLabel);
    groupLayout->addWidget(_validButton);
    groupLayout->addWidget(mdpToolbar);             // ajout de la barre d'outils mot de passe oublié

    connexionGroupBox->setLayout(groupLayout);

    // footer

    _compteLabel->setText(tr("Pas de compte ?"));

    QWidget *emptyWidget = new QWidget;
    emptyWidget->setFixedWidth(110);
    compteToolbar->addWidget(emptyWidget);
    compteToolbar->addAction(_creerCompteAction);

    QSpacerItem* compteSpace = new QSpacerItem(380, 70);

    connexionLayout->addWidget(_headerLabel);
    connexionLayout->addWidget(connexionGroupBox);
    connexionLayout->addSpacerItem(compteSpace);
    connexionLayout->addWidget(_compteLabel);
    connexionLayout->addWidget(compteToolbar);

    setLayout(connexionLayout);
}

// Groupe de widgets pour la création d'un compte

void LoginConfiguration::registerConfig()
{
    //

    QGroupBox *registerGroupBox = new QGroupBox;
    registerGroupBox->setFixedSize(320, 280);

    QVBoxLayout *registerLayout = new QVBoxLayout;

    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupLayout->setMargin(30);

    QSpacerItem* space1 = new QSpacerItem(380, 10);
    //QSpacerItem* space2 = new QSpacerItem(380, 5);

    QToolBar *compteToolbar = new QToolBar;
    compteToolbar->setFixedWidth(260);

    _incorrectIdsLabel->setFixedSize(380, 15);

    // header
    _headerLabel->setText(tr("Créer un compte"));

    // body

    groupLayout->addWidget(_idLabel);
    groupLayout->addWidget(_idText);
    groupLayout->addSpacerItem(space1);
    groupLayout->addWidget(_passwordLabel);
    groupLayout->addWidget(_passwordText);
    groupLayout->addWidget(_incorrectIdsLabel);
    groupLayout->addWidget(_licenseLabel);
    groupLayout->addWidget(_registerButton);

    registerGroupBox->setLayout(groupLayout);

    // footer

    _compteLabel->setText(tr("Avez-vous déjà un compte ?"));
    QWidget *emptyWidget = new QWidget;
    emptyWidget->setFixedWidth(120);
    compteToolbar->addWidget(emptyWidget);
    compteToolbar->addAction(_connexionAction);

    QSpacerItem* compteSpace = new QSpacerItem(380, 70);

    registerLayout->addWidget(_headerLabel);
    registerLayout->addWidget(registerGroupBox);
    registerLayout->addSpacerItem(compteSpace);
    registerLayout->addWidget(_compteLabel);
    registerLayout->addWidget(compteToolbar);

    setLayout(registerLayout);
}



/* *** SLOTS *** */



/* ****** DESTRUCTEUR ****** */
LoginConfiguration::~LoginConfiguration()
{
    std::cout << "Destruction LoginConfiguration" << std::endl;
    delete _idText;
    delete _passwordText;

    delete _validButton;
    delete _registerButton;

    delete _actionRemberMe;
    delete _creerCompteAction;
    delete _connexionAction;
    delete _headerLabel;
    delete _compteLabel;
    delete _licenseLabel;
    delete _idLabel;
    delete _passwordLabel;
    delete _incorrectIdsLabel;
    std::cout << "-> Fin de la destruction" << std::endl;

}

