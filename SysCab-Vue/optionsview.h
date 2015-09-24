#ifndef OPTIONSVIEW_H
#define OPTIONSVIEW_H

using namespace std;
#include <iostream>

#include <QLabel>
#include <QVBoxLayout>
#include <QToolBar>
#include <QWidgetAction>
#include <QAction>

class OptionsView : public QWidgetAction
{
    Q_OBJECT

    friend class FenetrePrincipale;
    friend class SysCabClassePrincipale;

public:
    OptionsView(QObject *parent);
    void initComps();
    void etatInitialComps();
    void resetPauseAction();
    ~OptionsView();

public slots:
    void startPauseSlot();
    void restartSlot();
    void exercicesSlot();
    void homeSlot();
    void astuceSlot();

signals:
    void startPauseSignal(bool);
    void restartSignal();
    void exercicesSignal();
    void homeSignal();
    void astuceSignal();

private:
    QAction *_startAction;
    QAction *_restartAction;
    QAction *_exercicesAction;
    QAction *_astucesAction;
    QAction *_homeAction;

    bool _bEnPause;
};

#endif // OPTIONSVIEW_H
