#ifndef CUSTOMIZATION_H
#define CUSTOMIZATION_H


#include <QWidget>

class Customization
{
public:
    Customization();

    static void customExercicesView(QWidget *bs);
    static void customIndexView(QWidget *bs);
    static void customLoginView(QWidget *bs);
    static void customConfigModel(QWidget *bs);
    static void customToolBar(QWidget *bs);
    static void customProgressBar(QWidget *bs);
    static void customChallengeDesc(QWidget *bs);
    static void customNotationWidget(QWidget *bs);
    static void customTdbWidget(QWidget *bs);
    static void customNotesUserWidget(QWidget *bs);

    ~Customization();
};

#endif // CUSTOMIZATION_H
