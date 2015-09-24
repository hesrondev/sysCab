#include "challengewidget.h"

ChallengeWidget::ChallengeWidget()
{
    // caractéristiques
    setWindowFlags(Qt::FramelessWindowHint);

    setModal(true);
    setFixedSize(450, 250);

    QGridLayout *glayout = new QGridLayout;
    glayout->setMargin(10);

    setObjectName("cadre");

    _challengeGbox = new QGroupBox("CHALLENGE N°");

    _titleLabel = new QLabel("Titre du challenge ici...");
    _descriptionLabel = new QLabel("Description de la mission ici...");
    _astuceLabel = new QLabel("Astuce : un petit conseil pour guider le pilote");
    _dureeLabel = new QLabel("Durée : 30 sec.");

    _beginButton = new QPushButton("Commencer");

    // IDS
    _titleLabel->setObjectName("title");

    //
    glayout->addWidget(_titleLabel, 1, 0, 1, 3);
    glayout->addWidget(_descriptionLabel, 2, 0, 1, 3);
    glayout->addWidget(_astuceLabel, 3, 0, 1, 3);
    glayout->addWidget(_dureeLabel, 4, 0, 1, 3);
    glayout->addWidget(_beginButton, 5, 2);

    //

    _challengeGbox->setLayout(glayout);

    QHBoxLayout *hl = new QHBoxLayout;
    hl->setMargin(1);
    hl->addWidget(_challengeGbox);

    setLayout(hl);

    QObject::connect(_beginButton, SIGNAL(clicked()), this, SLOT(beginSlot()));
}

void ChallengeWidget::setLabels(int numChallenge, const Exercice &exo)
{
    QString sChallenge = "CHALLENGE N° " + QString::number(numChallenge);
    QString titre = QString::fromStdString(exo.titre());
    QString description = QString::fromStdString(exo.description());

    QString astuces = QString::fromStdString(exo.astuces());;

    _challengeGbox->setTitle(sChallenge);
    _titleLabel->setText(titre);
    _descriptionLabel->setText(description);
    _astuceLabel->setText(astuces);
    _dureeLabel->setText("Durée : " + QString::number(exo.duree()) + " sec.");
}


void ChallengeWidget::beginSlot()
{
    hide();
    emit beginSignal();
}



// DESTRUCTEUR

ChallengeWidget::~ChallengeWidget()
{
    cout << "Destruction de ChallengeWidget" << endl;

    delete _titleLabel;
    delete _descriptionLabel;
    delete _astuceLabel;
    delete _dureeLabel;
    delete _beginButton;

    delete _challengeGbox;  // élément contenant

    std::cout << "-> Fin de la destruction" << std::endl;
}


