#include "magazzinoView.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QPersistentModelIndex>
#include <QSortFilterProxyModel>


magazzinoView::magazzinoView(QWidget *parent, Model* model):

    QWidget(parent),
    core(model),
    addNew(new QPushButton),
    deleteAll(new QPushButton),
    deleteSelected(new QPushButton),
    searchLine(new QLineEdit),
    instrumentType(new QComboBox),
    _addView(new addView),
    resultsNumber(new QLabel),
    editEnabled(new QLabel),
    adapter(new magazzinoAdapter(this, core))
{
    addNew->setText("Nuovo strumento");

        QVBoxLayout *search = new QVBoxLayout();
        //search->setSpacing(10);

        QGroupBox * box = new QGroupBox("Ricerca stumenti");
        box->setStyleSheet("font-size:13px;");
        QHBoxLayout *form = new QHBoxLayout();
        form->setSpacing(100);
        searchLine->setPlaceholderText("Ricerca per categoria, tipo o brand");
        form->addWidget(searchLine, Qt::AlignLeft);
        instrumentType->addItem("Tutto");
        instrumentType->addItem("Opzione_1");
        instrumentType->addItem("Opzione_2");
        instrumentType->setToolTip("Filtra per:");
        form->addWidget(instrumentType);

        box->setLayout(form);
        search->addWidget(box);
        QBoxLayout *resultBar = new QBoxLayout(QBoxLayout::LeftToRight);
        resultBar->setSpacing(10);

        if(!core->getMagazzinoSize()){
            resultsNumber->setText("<b>Per iniziare, carica un salvataggio</b>");
            resultsNumber->setStyleSheet("color : orange");
        }else
        {
            resultsNumber->setText("<b>" + QString::number(core->getMagazzinoSize()) + "strumenti trovati</b>");
            resultsNumber->setStyleSheet("color : green");
        }

        resultBar->addWidget(resultsNumber);
        editEnabled->setText("");
        resultBar->addWidget(editEnabled);
        deleteSelected->setText("Elimina Selezionato");
        resultBar->addWidget(deleteSelected);
        //deleteSelected->setIcon(QIcon(":/res/img/negative.svg"));
        //deleteSelected->setIconSize(QSize(16,16));
        deleteAll->setText("Elimina Tutti");
        //deleteAll->setIcon(QIcon(":/res/img/delete.svg"));
        //deleteAll->setIconSize(QSize(16,16));
        resultBar->addWidget(deleteAll);
        addNew->setText("Nuovo prodotto");
        //addNew->setIcon(QIcon(":/res/img/plus.svg"));
        //addNew->setIconSize(QSize(16,16));
        resultBar->addWidget(addNew);
        search->addItem(resultBar);


        /* Creazione Tabella e configurazione filtraggio (ricerca) e sorting per ogni campo di essa */
            table = new QTableView;
            table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            table->setSortingEnabled(true);
            table->setSelectionBehavior(QAbstractItemView::SelectRows);

            filter = new magazzinoFilter(this,instrumentType);
            filter->setSourceModel(adapter);
            //Regola di ordinamento customizzata ( di default ordina prendendo tutto come stringa --> 8 > 70)
            filter->setSortRole(magazzinoAdapter::SortRole);
            table->setModel(filter);

        /* Creazione Tabella e configurazione filtraggio (ricerca) e sorting per ogni campo di essa */
            search->addWidget(table);
            setLayout(search);


        connect(addNew,SIGNAL(clicked()), this, SLOT(slotOpenInserisci()));
        connect(instrumentType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotStartFiltering()));
        connect(searchLine, SIGNAL(textChanged(QString)), this, SLOT(slotStartFiltering()));

    }

    magazzinoAdapter* magazzinoView::getAdapter() const{ return adapter;}

    void magazzinoView::slotOpenAddView() const{
        _addView->setModal(true);
        _addView->exec();//show
    }

    magazzinoFilter *magazzinoView::getFilter() const{ return filter;}

    QLabel *magazzinoView::getEditEnabled() const{ return editEnabled;}

    QTableView *magazzinoView::getTable() const{ return table;}

    QPushButton *magazzinoView::getDeleteSelected() const{ return deleteSelected;}
    QPushButton *magazzinoView::getDeleteAll() const{ return deleteAll;}

    addView *magazzinoView::getAddNew() const {  return _addView; }

    QLabel *magazzinoView::getResultsNumber() const{ return resultsNumber;}


    void magazzinoView::slotStartFiltering() const
    {

        QRegExp regex(searchLine->text(), Qt::CaseInsensitive, QRegExp::Wildcard);
        filter->setFilterRegExp(regex);
        int numberRes = filter->rowCount();
        if(numberRes){
            resultsNumber->setText("<b>" + QString::number(numberRes) + " risultati trovati </b>");
            resultsNumber->setStyleSheet("color: green;");
        }else{
            if(core->getMagazzinoSize()){
                resultsNumber->setText("<b>Nessun risultato trovato </b>");
                resultsNumber->setStyleSheet("color: red");
            }
            else{
                resultsNumber->setText("Nessuno strumento presente");
                resultsNumber->setStyleSheet("color : orange");
            }
        }
    }


