#include "carrelloView.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QPersistentModelIndex>
#include <QSortFilterProxyModel>


carrelloView::carrelloView(QWidget *parent, Model* model):

    QWidget(parent),
    core(model),
    addNew(new QPushButton),
    deleteAll(new QPushButton),
    deleteSelected(new QPushButton),
    searchLine(new QLineEdit),
    instrumentType(new QComboBox),
    addView(new insertView),
    resultsNumber(new QLabel),
    editEnabled(new QLabel),
    adapter(new carrelloAdapter(this, core))
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

        if(!core->getCarrelloSize()){
            resultsNumber->setText("<b>Per iniziare, carica un salvataggio</b>");
            resultsNumber->setStyleSheet("color : orange");
        }else
        {
            resultsNumber->setText("<b>" + QString::number(core->getCarrelloSize()) + "strumenti trovati</b>");
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

            filter = new carrelloFilter(this,instrumentType);
            filter->setSourceModel(adapter);
            //Regola di ordinamento customizzata ( di default ordina prendendo tutto come stringa --> 8 > 70)
            filter->setSortRole(carrelloAdapter::SortRole);
            table->setModel(filter);

        /* Creazione Tabella e configurazione filtraggio (ricerca) e sorting per ogni campo di essa */
            search->addWidget(table);
            setLayout(search);


        connect(addNew,SIGNAL(clicked()), this, SLOT(slotOpenInsertView()));
        connect(instrumentType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotStartFiltering()));
        connect(searchLine, SIGNAL(textChanged(QString)), this, SLOT(slotStartFiltering()));

    }

    carrelloAdapter* carrelloView::getAdapter() const{ return adapter;}

    void carrelloView::slotOpenInsertView() const{
        addView->setModal(true);
        addView->exec();//show

    }

    carrelloFilter *carrelloView::getFilter() const{ return filter;}

    QLabel *carrelloView::getEditEnabled() const{ return editEnabled;}

    QTableView *carrelloView::getTable() const{ return table;}

    QPushButton *carrelloView::getDeleteSelected() const{ return deleteSelected;}
    QPushButton *carrelloView::getDeleteAll() const{ return deleteAll;}

    insertView *carrelloView::getAddView() const {  return addView; }

    QLabel *carrelloView::getResultsNumber() const{ return resultsNumber;}


    void carrelloView::slotStartFiltering() const
    {

        QRegExp regex(searchLine->text(), Qt::CaseInsensitive, QRegExp::Wildcard);
        filter->setFilterRegExp(regex);
        int numberRes = filter->rowCount();
        if(numberRes){
            resultsNumber->setText("<b>" + QString::number(numberRes) + " risultati trovati </b>");
            resultsNumber->setStyleSheet("color: green;");
        }else{
            if(core->getCarrelloSize()){
                resultsNumber->setText("<b>Nessun risultato trovato </b>");
                resultsNumber->setStyleSheet("color: red");
            }
            else{
                resultsNumber->setText("Nessuno strumento presente");
                resultsNumber->setStyleSheet("color : orange");
            }
        }
    }


