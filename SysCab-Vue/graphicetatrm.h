#ifndef GRAPHICETATRESERVOIRS_H
#define GRAPHICETATRESERVOIRS_H

#include "graphiccomposantitem.h"
#include "customization.h"

#include <QProgressBar>

class GraphicEtatRM : public GraphicComposantItem
{
    friend class SystemeCarburant;

public:
    GraphicEtatRM(const qreal& x, const qreal& y);

    void updateBarValues(int val1, int val2, int val3);
    void updateLevelRes(const QString& s1, const QString& s2, const QString& s3, const QString &s4);
    void updateResMoteur(const QString& s1, const QString& s2, const QString& s3);
    void updateConsoMoteur(const QString& s1, const QString& s2, const QString& s3);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    ~GraphicEtatRM();

private:
    QPointF _pointDepart;

    QProgressBar *_res1ProgressBar;
    QProgressBar *_res2ProgressBar;
    QProgressBar *_res3ProgressBar;

    QString _levelRes1;
    QString _levelRes2;
    QString _levelRes3;

    QString _resMoteur1;
    QString _resMoteur2;
    QString _resMoteur3;

    QString _consoMoteur1;
    QString _consoMoteur2;
    QString _consoMoteur3;

    QString _totalLevel;
};

#endif // GRAPHICETATRESERVOIRS_H
