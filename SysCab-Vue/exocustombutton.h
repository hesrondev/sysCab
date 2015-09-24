#ifndef EXOCUSTOMBUTTON_H
#define EXOCUSTOMBUTTON_H

#include <iostream>
#include <QPushButton>
#include <QWidget>

class ExoCustomButton : public QPushButton
{
    Q_OBJECT

public:
    ExoCustomButton(const QString& name, int index);
    ~ExoCustomButton();

    bool bActive() const;
    void setBActive(bool bActive);

public slots:
    void indexSlot();

signals:
    void indexSignal(int index);

private:
    int _index;
    bool _bActive;

};

#endif // EXOCUSTOMBUTTON_H
