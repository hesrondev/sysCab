#include "optionsview.h"



OptionsView::OptionsView(QObject *parent) : QWidgetAction(parent)
{
    // Au départ le système est à l'arrêt
    _bEnPause = true;

    initComps();
    etatInitialComps();

    // Signaux
    QObject::connect(_startAction, SIGNAL(triggered()), this, SLOT(startPauseSlot()));
    QObject::connect(_restartAction, SIGNAL(triggered()), this, SLOT(restartSlot()));
    QObject::connect(_exercicesAction, SIGNAL(triggered()), this, SLOT(exercicesSlot()));
    QObject::connect(_astucesAction, SIGNAL(triggered()), this, SLOT(astuceSlot()));
    QObject::connect(_homeAction, SIGNAL(triggered()), this, SLOT(homeSlot()));

}

void OptionsView::initComps()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *vlayout = new QVBoxLayout;
    QToolBar *toolbar = new QToolBar;

    vlayout->setMargin(0);
    toolbar->setOrientation(Qt::Vertical);
    toolbar->setIconSize(QSize(24, 24));

    _startAction = new QAction(QIcon(":/logIcons/start"), "Lancer la simulation", this);
    _restartAction = new QAction(QIcon(":/logIcons/restart"), "Réinitialiser", this);
    _exercicesAction = new QAction(QIcon(":/logIcons/exercices"), "Liste des exercices", this);
    _astucesAction = new QAction(QIcon(":/logIcons/astuces"), "Astuces", this);
    _homeAction = new QAction(QIcon(":/logIcons/home"), "Quitter la simulation", this);

    toolbar->addAction(_startAction);
    toolbar->addAction(_restartAction);
    toolbar->addAction(_astucesAction);
    toolbar->addSeparator();
    toolbar->addAction(_exercicesAction);
    toolbar->addAction(_homeAction);

    vlayout->addWidget(toolbar);
    widget->setLayout(vlayout);

    setDefaultWidget(widget);
}

void OptionsView::etatInitialComps()
{
    _startAction->setEnabled(false);
    _restartAction->setEnabled(false);
    _exercicesAction->setEnabled(false);
    _astucesAction->setEnabled(false);
}

void OptionsView::resetPauseAction()
{
    _bEnPause = true;
    _startAction->setIcon(QIcon(":/logIcons/start"));
    _startAction->setToolTip("Lancer la simulation");
}


// SLOTS
void OptionsView::startPauseSlot()
{
    if (_bEnPause)
    {
        _bEnPause = !_bEnPause;
        _startAction->setIcon(QIcon(":/logIcons/pause"));
        _startAction->setToolTip("Mettre en pause la simulation");

        emit startPauseSignal(_bEnPause);
    }

    else
    {
        _bEnPause = !_bEnPause;
        _startAction->setIcon(QIcon(":/logIcons/start"));
        _startAction->setToolTip("Reprendre la simulation");

        emit startPauseSignal(_bEnPause);
    }
}

void OptionsView::restartSlot()
{
    emit restartSignal();
}

void OptionsView::exercicesSlot()
{
    emit exercicesSignal();
}

void OptionsView::homeSlot()
{
    emit homeSignal();
}

void OptionsView::astuceSlot()
{
    emit astuceSignal();
}


// Destructeur
OptionsView::~OptionsView()
{
    std::cout << "Destruction de OptionsView" << std::endl;
    delete _startAction;
    delete _restartAction;
    delete _exercicesAction;
    delete _astucesAction;
    delete _homeAction;
    std::cout << "-> Fin de la destruction" << std::endl;
}



