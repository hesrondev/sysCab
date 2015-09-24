#include "exocustombutton.h"

ExoCustomButton::ExoCustomButton(const QString &name, int index) : QPushButton(QIcon("logIcons/locked"), name)
{
    _index = index;
    _bActive = false;
    setEnabled(false);

    // custom
    setFixedSize(50, 70);

    //signals
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(indexSlot()));
}



void ExoCustomButton::indexSlot()
{
    std::cout << "appuie sur un bouton exo " << _index << std::endl;
    emit indexSignal(_index);
}

// Setteurs

bool ExoCustomButton::bActive() const
{
    return _bActive;
}

void ExoCustomButton::setBActive(bool bActive)
{
    _bActive = bActive;

    if (bActive)
    {
        setEnabled(true);
        setIcon(QIcon("logIcons/none"));
    }

    else
    {
        setEnabled(true);
        setIcon(QIcon("logIcons/locked"));
        setEnabled(false);
    }
}


//

ExoCustomButton::~ExoCustomButton()
{
    std::cout << "Destruction ExoCustomButton" << std::endl;
    std::cout << "-> Fin de la destruction" << std::endl;
}


