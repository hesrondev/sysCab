#include "graphicetatrm.h"

GraphicEtatRM::GraphicEtatRM(const qreal& x, const qreal& y): GraphicComposantItem(), _pointDepart(x, y),
    _levelRes1("VIDE"), _levelRes2("VIDE"), _levelRes3("VIDE"), _totalLevel("0"), _resMoteur1("--"), _resMoteur2("--"),
    _resMoteur3("--"), _consoMoteur1("-"), _consoMoteur2("-"), _consoMoteur3("-")
{

    //
    _res1ProgressBar = new QProgressBar;
    _res1ProgressBar->setOrientation(Qt::Horizontal);
    _res1ProgressBar->setTextVisible(false);
    _res1ProgressBar->setValue(0);

    _res2ProgressBar = new QProgressBar;
    _res2ProgressBar->setOrientation(Qt::Horizontal);
    _res2ProgressBar->setTextVisible(false);
    _res2ProgressBar->setValue(0);

    _res3ProgressBar = new QProgressBar;
    _res3ProgressBar->setOrientation(Qt::Horizontal);
    _res3ProgressBar->setTextVisible(false);
    _res3ProgressBar->setValue(0);

    _res1ProgressBar->setFixedSize(60, 13);
    _res2ProgressBar->setFixedSize(60, 13);
    _res3ProgressBar->setFixedSize(60, 13);
    Customization::customProgressBar(_res1ProgressBar);
    Customization::customProgressBar(_res2ProgressBar);
    Customization::customProgressBar(_res3ProgressBar);

}


// Updates

void GraphicEtatRM::updateBarValues(int val1, int val2, int val3)
{
    _res1ProgressBar->setValue(val1);
    _res2ProgressBar->setValue(val2);
    _res3ProgressBar->setValue(val3);
}

void GraphicEtatRM::updateLevelRes(const QString &s1, const QString &s2, const QString &s3, const QString &s4)
{
    _levelRes1 = s1;
    _levelRes2 = s2;
    _levelRes3 = s3;

    _totalLevel = s4;
}

void GraphicEtatRM::updateResMoteur(const QString& s1, const QString& s2, const QString& s3)
{
    _resMoteur1 = s1;
    _resMoteur2 = s2;
    _resMoteur3 = s3;
}

void GraphicEtatRM::updateConsoMoteur(const QString &s1, const QString &s2, const QString &s3)
{
    _consoMoteur1 = s1;
    _consoMoteur2 = s2;
    _consoMoteur3 = s3;
}



// Drawing
QRectF GraphicEtatRM::boundingRect() const
{
    return QRectF(_pointDepart.x(), _pointDepart.y(), 240, 60);
}

void GraphicEtatRM::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal x = _pointDepart.x();
    qreal y = _pointDepart.y();

    qreal z = x+400;


    QRectF rectValues = boundingRect();
    QRectF rectTitre = QRectF(x+70, y-9, 100, 13);

    QRectF rectValues2 = QRectF(z, y, 240, 60);
    QRectF rectTitre2 = QRectF(z+70, y-9, 100, 13);

    pen.setColor(QColor(93, 66, 193));
    painter->setPen(pen);
    painter->setBrush(brushDefault);


    painter->drawRoundedRect(rectValues, 5, 5);
    painter->drawRoundedRect(rectValues2, 5, 5);

    //
    painter->fillRect(rectTitre, brushDefault);
    painter->fillRect(rectTitre2, brushDefault);

    //
    painter->drawText(rectTitre, "CARB  QTY  QMAX", QTextOption(Qt::AlignCenter));
    painter->drawText(rectTitre2, "REACT. STATES", QTextOption(Qt::AlignCenter));

    //
    painter->drawText(QRectF(x+10, y+10, 71, 12), "TANK1", QTextOption(Qt::AlignCenter));       // les espaces sont pour centrer le texte
    painter->drawText(QRectF(x+83.5, y+10, 71, 12), "TANK2", QTextOption(Qt::AlignCenter));
    painter->drawText(QRectF(x+157, y+10, 71, 12), "TANK3", QTextOption(Qt::AlignCenter));

    painter->drawText(QRectF(z+10, y+10, 71, 12), "MOTEUR1", QTextOption(Qt::AlignCenter));
    painter->drawText(QRectF(z+83.5, y+10, 71, 12), "MOTEUR2", QTextOption(Qt::AlignCenter));
    painter->drawText(QRectF(z+157, y+10, 71, 12), "MOTEUR3", QTextOption(Qt::AlignCenter));

    painter->drawText(QRectF(z+10, y+27, 71, 12), _resMoteur1, QTextOption(Qt::AlignCenter));
    painter->drawText(QRectF(z+83.5, y+27, 71, 12), _resMoteur2, QTextOption(Qt::AlignCenter));
    painter->drawText(QRectF(z+157, y+27, 71, 12), _resMoteur3, QTextOption(Qt::AlignCenter));

    painter->drawText(QRectF(z+10, y+42, 71, 10), _consoMoteur1, QTextOption(Qt::AlignCenter));
    painter->drawText(QRectF(z+83.5, y+42, 71, 10), _consoMoteur2, QTextOption(Qt::AlignCenter));
    painter->drawText(QRectF(z+157, y+42, 71, 10), _consoMoteur3, QTextOption(Qt::AlignCenter));

    //
    painter->drawText(QRectF(x+10, y+70, 40, 20), "TOTAL", QTextOption(Qt::AlignLeft));
    painter->drawText(QRectF(x+60, y+70, 100, 20), _totalLevel, QTextOption(Qt::AlignLeft));


    // Conversion des progressar en pixmap

    QPixmap pixmap = _res1ProgressBar->grab();
    painter->drawPixmap(x+15, y+27, 60, 13, pixmap);

    pixmap = _res2ProgressBar->grab();
    painter->drawPixmap(x+88.5, y+27, 60, 13, pixmap);

    pixmap = _res3ProgressBar->grab();
    painter->drawPixmap(x+162, y+27, 60, 13, pixmap);

    //
    painter->drawText(QRectF(x+10, y+42, 71, 10), _levelRes1, QTextOption(Qt::AlignCenter));
    painter->drawText(QRectF(x+83.5, y+42, 71, 10), _levelRes2, QTextOption(Qt::AlignCenter));
    painter->drawText(QRectF(x+157, y+42, 71, 10), _levelRes3, QTextOption(Qt::AlignCenter));

}


GraphicEtatRM::~GraphicEtatRM()
{
    // Destruction des objets alloués dynamiquement


    delete _res1ProgressBar;
    delete _res2ProgressBar;
    delete _res3ProgressBar;
}

