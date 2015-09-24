#ifndef CHALLENGEWIDGET_H
#define CHALLENGEWIDGET_H


#include <QDialog>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>

#include "SysCab-Bases/exercice.h"


class ChallengeWidget : public QDialog
{

    Q_OBJECT

public:
    ChallengeWidget();
    void setLabels(int numChallenge, const Exercice &exo);
    ~ChallengeWidget();

public slots:
    void beginSlot();

signals:
    void beginSignal();

private:
    QGroupBox *_challengeGbox;

    QLabel *_chLabel;
    QLabel *_titleLabel;
    QLabel *_descriptionLabel;
    QLabel *_astuceLabel;
    QLabel *_dureeLabel;
    QPushButton *_beginButton;
};

#endif // CHALLENGEWIDGET_H
