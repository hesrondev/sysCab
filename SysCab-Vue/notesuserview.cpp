#include "notesuserview.h"

NotesUserView::NotesUserView()
{

    //
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(806, 400);
    setModal(true);

    setObjectName("cadre");

    _titleLabel = new QLabel("Notes");
    _userNotesTable = new QTableView;
    _classementTable = new QTableView;
    _cancelButton = new QPushButton("Fermer");

    _titleLabel->setFixedHeight(20);
    _titleLabel->setAlignment(Qt::AlignCenter);
    _titleLabel->setObjectName("title");

    _cancelButton->setMaximumWidth(120);

    _notesModel = new QStandardItemModel(20, 15);
    _classementModel = new QStandardItemModel(5, 3);

    _userNotesTable->setModel(_notesModel);
    _classementTable->setModel(_classementModel);

    for (int i = 0; i < 15; i++)
    {
        _notesModel->setHorizontalHeaderItem(i, new QStandardItem("Chal. "+QString::number(i+1)));
        _userNotesTable->setColumnWidth(i, 50);
    }

    _classementModel->setHorizontalHeaderItem(0, new QStandardItem("Rang"));
    _classementModel->setHorizontalHeaderItem(1, new QStandardItem("Identifiant"));
    _classementModel->setHorizontalHeaderItem(2, new QStandardItem("Moyenne"));
    _classementTable->resizeColumnsToContents();
    _classementTable->resizeRowsToContents();

    _userNotesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


    // Cacher la table non encore éditée

    _classementTable->hide();

    _gridLayout = new QGridLayout;
    _gridLayout->setMargin(7);

    _gridLayout->addWidget(_titleLabel, 0, 0, 1, 3);
    _gridLayout->addWidget(_userNotesTable, 1, 0, 1, 3);
    _gridLayout->addWidget(_classementTable, 2, 0, 1, 3);
    _gridLayout->addWidget(_cancelButton, 3, 2);

     setLayout(_gridLayout);


    //
    QObject::connect(_cancelButton, SIGNAL(clicked()), this, SLOT(cancelHideSlot()));

}


// Ajout des notes de l'utilisateur dans le modèle (tableau)

void NotesUserView::updateUserNotes(const vector<vector<int> >& vectNotes)
{
    for (int i = 0; i < vectNotes.size(); i++)
        for (int j = 0; j < vectNotes[i].size(); j++)
        {
            _notesModel->setItem(j, i, new QStandardItem(QString::number(vectNotes[i][j])));
        }
}

// Cacher le tableau après appuie sur 'fermer'

void NotesUserView::cancelHideSlot()
{
    hide();
}


NotesUserView::~NotesUserView()
{
    std::cout << "Destruction de NotesUserView" << std::endl;
    delete _cancelButton;
    delete _titleLabel;
    delete _userNotesTable;
    delete _classementTable;
    delete _gridLayout;

    delete _notesModel;
    delete _classementModel;
    std::cout << "-> Fin de la destruction" << std::endl;
}


