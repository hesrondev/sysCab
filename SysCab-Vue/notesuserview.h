#ifndef NOTESUSERVIEW_H
#define NOTESUSERVIEW_H

#include <iostream>

#include <QDialog>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QTableView>
#include <QStandardItemModel>

#include <vector>

using namespace std;


class NotesUserView : public QDialog
{

    Q_OBJECT

public:
    NotesUserView();

    void updateUserNotes(const vector < vector <int> >& vectNotes);

    ~NotesUserView();

public slots:
    void cancelHideSlot();

private:
    QPushButton *_cancelButton;
    QLabel *_titleLabel;
    QTableView *_userNotesTable;
    QTableView *_classementTable;
    QGridLayout *_gridLayout;

    QStandardItemModel *_notesModel;
    QStandardItemModel *_classementModel;
};

#endif // NOTESUSERVIEW_H
