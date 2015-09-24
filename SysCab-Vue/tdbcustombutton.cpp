#include "tdbcustombutton.h"

TdbCustomButton::TdbCustomButton(const QString& txt, int W, int H) : QPushButton(txt)
{
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    setFixedSize(W, H);

    _bPressed = false;



    //
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(clickedSlot()));
}

// Config

void TdbCustomButton::pressedConfig()
{
    if (_bPressed)
    {
        _bPressed = !_bPressed;
        setFlat(false);
    }

    else
    {
        _bPressed = !_bPressed;
        setFlat(true);
    }

}

void TdbCustomButton::resetConfig()
{
    _bPressed = false;
    setFlat(false);
}


// Slots
void TdbCustomButton::clickedSlot()
{
    pressedConfig();
    emit clickedSignal();
}



TdbCustomButton::~TdbCustomButton()
{
    std::cout << "Destruction de TdbCustomButton" << std::endl;
    std::cout << "-> Fin de la destruction" << std::endl;
}

