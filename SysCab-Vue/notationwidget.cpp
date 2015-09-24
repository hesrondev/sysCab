#include "notationwidget.h"

NotationWidget::NotationWidget()
{

    //
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(300, 200);
    setModal(true);

    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect;
    sh->setBlurRadius(50);
    setGraphicsEffect(sh);

    _retryButton = new QPushButton(QIcon("logIcons/retry"), "");
    _nextChalButton = new QPushButton(QIcon("logIcons/next"), "");
    _exercicesButton = new QPushButton(QIcon("logIcons/liste"), "");

    _titleLabel = new QLabel("Bravo! Challenge réussi");
    _pointsLabel = new QLabel("Vous avez obtenu 9 points");
    _noteCarbLabel = new QLabel("Gestion carburant : 4 points");
    _noteDecisionLabel  = new QLabel("Prise de décision : 5 points");

    // IDS
    _titleLabel->setObjectName("title");

    _noteCarbLabel->setFixedHeight(20);
    _noteDecisionLabel->setFixedHeight(20);

    QWidget *ewd = new QWidget;
    ewd->setFixedHeight(20);

    _titleLabel->setAlignment(Qt::AlignCenter);
    _pointsLabel->setAlignment(Qt::AlignCenter);

    QGridLayout *glayout = new QGridLayout;
    glayout->setMargin(10);

    glayout->addWidget(_titleLabel, 0, 0, 1, 5);
    glayout->addWidget(_pointsLabel, 1, 0, 1, 5);
    glayout->addWidget(_noteCarbLabel, 2, 0, 1, 5);
    glayout->addWidget(_noteDecisionLabel, 3, 0, 1, 5);
    glayout->addWidget(ewd, 4, 0, 1, 5);
    glayout->addWidget(_exercicesButton, 5, 1);
    glayout->addWidget(_retryButton, 5, 2);
    glayout->addWidget(_nextChalButton, 5, 3);

    QGroupBox *gbox = new QGroupBox;
    QHBoxLayout *hl = new QHBoxLayout;
    hl->setMargin(1);

    gbox->setLayout(glayout);

    hl->addWidget(gbox);
    setLayout(hl);

    //
    QObject::connect(_retryButton, SIGNAL(clicked()), this, SLOT(retrySlot()));
    QObject::connect(_nextChalButton, SIGNAL(clicked()), this, SLOT(nextSlot()));
    QObject::connect(_exercicesButton, SIGNAL(clicked()), this, SLOT(exosSlot()));

}

//

void NotationWidget::setLabels(bool b, int numExo, int noteCarb, int noteDecision, int nbPannes)
{
    QString sPoint = "Vous avez obtenu " + QString::number(noteCarb + noteDecision) + " points";
    QString scarb = "Résolus : " + QString::number(noteCarb) + "/" + QString::number(nbPannes);
    QString sdec = "Décision : " + QString::number(noteDecision) + "/" + QString::number(noteCarb);

    // on active que si exo réussi et si pas dernier de la liste

    _nextChalButton->setEnabled(false);

    if (b)
    {
        _titleLabel->setText("Bravo! Challenge effectué");
        _pointsLabel->setText(sPoint);
        _noteCarbLabel->setText(scarb);
        _noteDecisionLabel->setText(sdec);

        // si ce n'est pas le dernier exo, activer le bouton next challenge
        if (numExo < 14)
            _nextChalButton->setEnabled(true);
    }

    else
    {
        _titleLabel->setText("Oups! Challenge échoué");
        _pointsLabel->setText("Vous avez obtenu 0 point");
        _noteCarbLabel->setText("");
        _noteDecisionLabel->setText("");
    }

}

//

void NotationWidget::retrySlot()
{
    hide();
    emit retryChallengeSignal();
}

void NotationWidget::nextSlot()
{
    hide();
    emit nextChallengeSignal();
}

void NotationWidget::exosSlot()
{
    hide();
    emit listeExosSignal();
}


NotationWidget::~NotationWidget()
{
    std::cout << "Destruction de NotationWidget" << std::endl;
    delete _retryButton;
    delete _nextChalButton;
    delete _exercicesButton;
    delete _titleLabel;
    delete _pointsLabel;
    delete _noteCarbLabel;
    delete _noteDecisionLabel;
    std::cout << "-> Fin de la destruction" << std::endl;
}


