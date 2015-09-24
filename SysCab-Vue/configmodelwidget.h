#ifndef CONFIGMODELEWIDGET_H
#define CONFIGMODELEWIDGET_H

#include <iostream>

using namespace std;

#include <QDialog>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QGridLayout>

class ConfigModelWidget : public QDialog
{
    Q_OBJECT

public:
    ConfigModelWidget();
    void initComps();
    ~ConfigModelWidget();

public slots:
    void res2CapaciteSlot(double v);
    void validSlot();
    void cancelSlot();

signals:
    void capacitesSlot(double r1, double r2, double r3, double m1, double m2, double m3);

private:
    QDoubleSpinBox *_res1SpBox;
    QDoubleSpinBox *_res2SpBox;
    QDoubleSpinBox *_res3SpBox;

    QDoubleSpinBox *_m1SpBox;
    QDoubleSpinBox *_m2SpBox;
    QDoubleSpinBox *_m3SpBox;

    QPushButton *_validButton;
    QPushButton *_cancelButton;

};

#endif // CONFIGMODELEWIDGET_H
