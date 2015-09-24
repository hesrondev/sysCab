#ifndef NOTATIONWIDGET_H
#define NOTATIONWIDGET_H
#include <iostream>

#include <QDialog>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QGraphicsDropShadowEffect>

class NotationWidget : public QDialog
{
    Q_OBJECT

public:
    NotationWidget();
    void setLabels(bool b, int numExo, int noteCarb = 0, int noteDecision = 0, int nbPannes = 2);
    ~NotationWidget();

public slots:
    void retrySlot();
    void nextSlot();
    void exosSlot();

signals:
    void retryChallengeSignal();
    void nextChallengeSignal();
    void listeExosSignal();

private:
    QPushButton *_retryButton;
    QPushButton *_nextChalButton;
    QPushButton *_exercicesButton;
    QLabel *_titleLabel;
    QLabel *_pointsLabel;
    QLabel *_noteCarbLabel;
    QLabel *_noteDecisionLabel;
};

#endif // NOTATIONWIDGET_H
