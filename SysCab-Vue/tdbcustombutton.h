#ifndef TBDCUSTOMBUTTON_H
#define TBDCUSTOMBUTTON_H

#include <iostream>

#include <QPushButton>

class TdbCustomButton : public QPushButton
{
    Q_OBJECT

public:
    TdbCustomButton(const QString &txt, int W, int H);

    void pressedConfig();
    void resetConfig();

    ~TdbCustomButton();

public slots:
    void clickedSlot();

signals:
    void clickedSignal();


private:
    bool _bPressed;

    QString _designStrPressed;
    QString _designStrNotPressed;

};

#endif // TBDCUSTOMBUTTON_H
