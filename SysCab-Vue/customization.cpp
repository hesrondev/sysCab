#include "customization.h"

Customization::Customization()
{

}



void Customization::customExercicesView(QWidget *bs)
{
    QString qs = "QPushButton {"
                 "background: #eee;"
                 "font: bold 14px Arial;"
                 "border: 2px solid #478bf9;"
                 "border-radius: 8px;"
                 "color: #555;"
                 "}"

                 "QPushButton:disabled {"
                 "border: 1px inset #ccc;"
                 "background: #eee;}"

                 "QPushButton:hover {"
                 "background: #3bbd7b;"
                 "font-size: 17px;"
                 "color: #fff;"
                 "border: none;"
                 "}"

                 "QGroupBox {"
                 "font: normal 25px 'Trebuchet MS', Helvetica, sans-serif;"
                 "color: #555;"
                 "font-variant: small-caps;"
                 "border: 1px solid #ccc;"
                 "border-radius: 5px;"
                 "margin-top: 1ex;"
                 "}"

                 "QGroupBox::title {"
                 "subcontrol-origin: margin;"
                 "subcontrol-position: top center;"
                 "padding: 0 3px;"
                 "}";

    bs->setStyleSheet(qs);
}

void Customization::customIndexView(QWidget *bs)
{
    QString qs = "QPushButton {"

                 "padding: 6px 0 6px 0;"
                 "border-radius: 5px;"
                 "border: none;"
                 "background: #eee;"
                 "color: #555;"
                 "font: bold 13px Arial;"
                 "border: 2px solid #bbb;"
                 "}"

                 "QPushButton#cnxButton:hover {"
                 "background: #f3f3f3;"
                 "color: #478bf9;"
                 "border: 2px solid #478bf9;"
                 "}"

                 "QPushButton#libreButton:hover {"
                 "background: #f3f3f3;"
                 "color: #478bf9;"
                 "border: 2px solid #478bf9;"
                 "}"

                 "QLabel#title {"
                 "font: bold 18px 'Trebuchet MS', Helvetica, sans-serif;"
                 "color: #555;"
                 "}"

                 "QLabel {"
                 "font: bold 20px 'Trebuchet MS', Helvetica, sans-serif;"
                 "font-variant: small-caps;"
                 "color: #cc6633;"
                 "}";

    bs->setStyleSheet(qs);
}

void Customization::customLoginView(QWidget *bs)
{
    QString qs = "QPushButton {"
                 "border-style: outset;"
                 "border: 1px solid #bbb;"
                 "padding: 6px 0 6px 0;"
                 "border-radius: 5px;"
                 "background: #eee;"
                 "font: bold 13px Arial;"
                 "color: #555;"
                 "}"

                 "QPushButton#validButton:hover {"
                 "background: #3bbd7b;"
                 "color: #fff;"
                 "border: none;"
                 "}"

                 "QPushButton#regButton:hover {"
                 "background: #3bbd7b;"
                 "color: #fff;"
                 "border: none;"
                 "}"

                 "QGroupBox {"
                 "border: 1px solid #ccc;"
                 "border-radius: 5px;"
                 "}"

                 "QLabel {"
                 "font: normal 12px 'Trebuchet MS', Helvetica, sans-serif;"
                 "color: #444;"
                 "}"

                 "QLabel#license {"
                 "font: normal 10px 'Trebuchet MS', Helvetica, sans-serif;"
                 "color: #555;"
                 "}"

                 "QLabel#title {"
                 "font-variant: small-caps;"
                 "font: bold 25px 'Trebuchet MS', Helvetica, sans-serif;"
                 "color: #3bbd7b;"
                 "}"

                 "QLabel#errorMsg {"
                 "font: normal 12px 'Trebuchet MS', Helvetica, sans-serif;"
                 "color: red;"
                 "}"

                 "QLabel#compteLabel {"
                 "font: normal 12px 'Trebuchet MS', Helvetica, sans-serif;"
                 "text-decoration: underline;"
                 "color: blue;"
                 "}"

                 "QLineEdit {"
                 "border: 2px solid #bbb;"
                 "border-radius: 5px;"
                 "background: white;"
                 "}";

    bs->setStyleSheet(qs);
}

void Customization::customConfigModel(QWidget *bs)
{
    QString qs = "QGroupBox {"
                 "font: normal 25px 'Trebuchet MS', Helvetica, sans-serif;"
                 "color: #555;"
                 "font-variant: small-caps;"
                 "border: 1px solid #ccc;"
                 "border-bottom-left-radius: 2px;"
                 "border-bottom-right-radius: 2px;"
                 "margin-top: 2ex;"
                 "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #f8f8f8);"
                 "}"

                 "QGroupBox::title {"
                 "subcontrol-origin: margin;"
                 "subcontrol-position: top center;"
                 "padding: 0 3px;"
                 "}"

                 "QLabel {"
                 "font: normal 12px 'Trebuchet MS', Helvetica, sans-serif;"
                 "color: #444;"
                 "}"

                 "QPushButton {"
                 "width:70px;"
                 "height:15px;"
                 "padding: 4px 0 4px 0;"
                 "border-radius: 8px;"
                 "background: #f5f5f5;"
                 "border: none;"
                 "color: #555;"
                 "font: bold 12px Arial;"
                 "border: 1px solid #bbb;"
                 "}"

                 "QPushButton#validButton:hover {"
                 "background: #3bbd7b;"
                 "color: #fff;"
                 "border: none;"
                 "}"

                 "QPushButton#cancelButton:hover {"
                 "background: #d34836;"
                 "color: #fff;"
                 "border: none;"
                 "}"

                 "QDoubleSpinBox {"
                 "width: 60px;"
                 "height: 20px;"
                 "border: 1px solid #aaa;"
                 "border-radius: 2px;"
                 "}"

                 "QDoubleSpinBox:disabled {"
                 "background: #eee;"
                 "}"
                 "QDialog#cadre {"
                 "border: 1px solid #9c9b9b;"
                 "border-bottom-left-radius: 3px;"
                 "border-bottom-right-radius: 3px;"
                 "}";

    bs->setStyleSheet(qs);
}

void Customization::customToolBar(QWidget *bs)
{
    QString qs = "QPushButton {"
                 "width:60px;"
                 "height:15px;"
                 "padding: 2px 0 2px 0;"
                 "border-radius: 8px;"
                 "background: #f5f5f5;"
                 "border: none;"
                 "color: #555;"
                 "font: bold 11px Arial;"
                 "border: 1px solid #bbb;"
                 "}"

                 "QPushButton:hover {"
                 "color: #3bbd7b;"
                 "border: 1px solid #3bbd7b;"
                 "}"

                 "QComboBox {"
                 "height: 15 px;"
                 "border: 1px solid #bbb;"
                 "border-radius: 8px;"
                 "padding: 1px 10px 1px 3px;"
                 "min-width: 6em;"
                 "color: #555;"
                 "font: bold 11px Arial;"
                 "}"

                 "QComboBox::drop-down {"
                 "subcontrol-origin: padding;"
                 "subcontrol-position: top right;"
                 "border-left:none;"
                 "border-top-right-radius: 3px; "
                 "border-bottom-right-radius: 3px;}"

                 "QComboBox:hover {"
                 "color: #3bbd7b;"
                 "border: 1px solid #3bbd7b;"
                 "}"

                 "QToolBar {"
                 "border: none;"
                 "spacing: 2px;"
                 "}";

    bs->setStyleSheet(qs);
}

void Customization::customProgressBar(QWidget *bs)
{
    QString qs = "QProgressBar {"
                 "background: #fff;"
                 "border: 1px solid grey;"
                 "border-radius: 2px;"
                 "text-align: center;"
                 "}"
                 "QProgressBar::chunk {"
                 "background: #CD96CD;}"

                 ;

    bs->setStyleSheet(qs);
}

void Customization::customChallengeDesc(QWidget *bs)
{

    QString qs = "QGroupBox {"
                 "font: normal 20px 'Trebuchet MS', Helvetica, sans-serif;"
                 "color: #555;"
                 "font-variant: small-caps;"
                 "border: 1px solid #ccc;"
                 "border-bottom-left-radius: 3px;"
                 "border-bottom-right-radius: 3px;"
                 "margin-top: 2ex;"
                 "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #f8f8f8);"
                 "}"

                 "QGroupBox::title {"
                 "subcontrol-origin: margin;"
                 "subcontrol-position: top center;"
                 "padding: 0 3px;"
                 "}"

                 "QLabel {"
                 "font: normal 13px 'Trebuchet MS', Helvetica, sans-serif;"
                 "color: #444;"
                 "}"

                 "QLabel#title {"
                 "font: bold 15px 'Trebuchet MS', Helvetica, sans-serif;"
                 "text-decoration: underline;"
                 "}"

                 "QPushButton {"
                 "width:70px;"
                 "height:15px;"
                 "padding: 4px 0 4px 0;"
                 "border-radius: 8px;"
                 "background: #f5f5f5;"
                 "border: none;"
                 "color: #555;"
                 "font: bold 12px Arial;"
                 "border: 1px solid #bbb;"
                 "}"

                 "QPushButton:hover {"
                 "background: #3bbd7b;"
                 "color: #fff;"
                 "border: none;"
                 "}"
                 "QDialog#cadre {"
                 "border: 1px solid #9c9b9b;"
                 "border-bottom-left-radius: 3px;"
                 "border-bottom-right-radius: 3px;"
                 "}";
    bs->setStyleSheet(qs);
}

void Customization::customNotationWidget(QWidget *bs)
{
    QString qs = "QGroupBox {"
                 "border: 1px solid #ccc;"
                 "border-bottom-left-radius: 3px;"
                 "border-bottom-right-radius: 3px;"
                 "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #f8f8f8);"
                 "}"

                 "QLabel {"
                 "font: normal 13px 'Trebuchet MS', Helvetica, sans-serif;"
                 "color: #444;"
                 "}"

                 "QLabel#title {"
                 "font: bold 15px 'Trebuchet MS', Helvetica, sans-serif;"
                 "text-decoration: underline;"
                 "}"

                 "QPushButton {"
                 "width:70px;"
                 "height:15px;"
                 "padding: 4px 0 4px 0;"
                 "border-radius: 8px;"
                 "background: #f5f5f5;"
                 "border: none;"
                 "color: #555;"
                 "font: bold 12px Arial;"
                 "border: 1px solid #bbb;"
                 "}"

                 "QPushButton::disabled {border:none;}"


                 "QPushButton:hover {"
                 "border: 2px solid #3bbd7b;"
                 "}";

    bs->setStyleSheet(qs);
}

void Customization::customTdbWidget(QWidget *bs)
{
    QString qs = "QPushButton {"
                 "width:70px;"
                 "height:15px;"
                 "padding: 4px 0 4px 0;"
                 "border-radius: 8px;"
                 "background: #f5f5f5;"
                 "border: none;"
                 "color: #555;"
                 "font: bold 12px Arial;"
                 "border: 1px solid #bbb;"
                 "}"

                 "QPushButton::flat {"
                 "background: #fff;"
                 "color: #3bbd7b;"
                 "border:2px solid #3bbd7b;"
                 "}"

                 "QPushButton:hover {"
                 "color: #3bbd7b;"
                 "border: 2px solid #3bbd7b;"
                 "}";

    bs->setStyleSheet(qs);
}

void Customization::customNotesUserWidget(QWidget *bs)
{
    QString qs = "QLabel#title {"
                 "font-variant: small-caps;"
                 "font: bold 25px 'Trebuchet MS', Helvetica, sans-serif;"
                 "color: #636363;"
                 "}"

                 "QPushButton {"
                 "width:70px;"
                 "height:15px;"
                 "padding: 4px 0 4px 0;"
                 "border-radius: 8px;"
                 "background: #f5f5f5;"
                 "border: none;"
                 "color: #555;"
                 "font: bold 12px Arial;"
                 "border: 1px solid #bbb;"
                 "}"

                 "QPushButton:hover {"
                 "border: 2px solid #d34836;"
                 "}"

                 "QDialog#cadre {"
                 "border: 1px solid #9c9b9b;"
                 "border-bottom-left-radius: 5px;"
                 "border-bottom-right-radius: 5px;"
                 "}";

    bs->setStyleSheet(qs);
}




// Destructeur

Customization::~Customization()
{

}

