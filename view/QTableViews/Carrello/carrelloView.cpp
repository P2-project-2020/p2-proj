#include "view/QTableViews/Carrello/carrelloView.h"
#include "view/QTableViews/tuneComboBoxItemDelegate.h"
#include "view/QTableViews/materialComboBoxItemDelegate.h"

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
    adapter(new carrelloAdapter(this, core)),
    deleteAll(new QPushButton),
    deleteSelected(new QPushButton),
    proceedAndBuy(new QPushButton),
    searchLine(new QLineEdit),
    instrumentType(new QComboBox),
    resultsNumber(new QLabel),
    editEnabled(new QLabel),
    detailView(new insertView)
{


        QVBoxLayout *search = new QVBoxLayout();
        //search->setSpacing(10);

        QGroupBox * box = new QGroupBox("Ricerca stumenti");
        box->setStyleSheet("font-size:13px;");
        QHBoxLayout *form = new QHBoxLayout();
        form->setSpacing(100);
        searchLine->setPlaceholderText("Ricerca per quantità, strumento, brand, tipo, materiale...");
        form->addWidget(searchLine, Qt::AlignLeft);
        instrumentType->addItem("Tutto");
        instrumentType->addItem("Archi");
        instrumentType->addItem("Corde");
        instrumentType->addItem("Percussioni");
        instrumentType->addItem("Fiati");
        instrumentType->setToolTip("Filtra per famiglia strumento:");
        form->addWidget(instrumentType);

        box->setLayout(form);
        search->addWidget(box);
        QBoxLayout *resultBar = new QBoxLayout(QBoxLayout::LeftToRight);
        resultBar->setSpacing(10);

        if(!core->getCarrelloSize()){
            resultsNumber->setText("<b>Per iniziare, aggiungi un prodotto da magazzino</b>");
            resultsNumber->setStyleSheet("color : orange");
        }else
        {
            resultsNumber->setText("<b>" + QString::number(core->getCarrelloSize()) + "strumenti trovati</b>");
            resultsNumber->setStyleSheet("color : green");
        }

        resultBar->addWidget(resultsNumber);
        editEnabled->setText("");
        resultBar->addWidget(editEnabled);
        deleteSelected->setText(" Rimuovi Selezionato");
        resultBar->addWidget(deleteSelected);
        deleteSelected->setIcon(QIcon::fromTheme("list-remove"));
        deleteSelected->setIconSize(QSize(13,13));
        deleteAll->setText(" Svuota Carrello");
        deleteAll->setIcon(QIcon::fromTheme("edit-delete"));
        deleteAll->setIconSize(QSize(13,13));
        resultBar->addWidget(deleteAll);
        proceedAndBuy->setText(" Procedi e Acquista");
        proceedAndBuy->setIcon(QIcon(":/icons/res/buy_icon.png"));
        deleteAll->setIconSize(QSize(10,10));
        resultBar->addWidget(proceedAndBuy);
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


        connect(instrumentType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotStartFiltering()));
        connect(searchLine, SIGNAL(textChanged(QString)), this, SLOT(slotStartFiltering()));

    }

    insertView *carrelloView::getDetailView() const{ return detailView; }
    carrelloAdapter* carrelloView::getAdapter() const{ return adapter;}

    carrelloFilter *carrelloView::getFilter() const{ return filter;}

    QLabel *carrelloView::getEditEnabled() const{ return editEnabled;}

    QTableView *carrelloView::getTable() const{ return table;}

    QPushButton *carrelloView::getDeleteSelected() const{ return deleteSelected;}
    QPushButton *carrelloView::getDeleteAll() const{ return deleteAll;}
    QPushButton *carrelloView::getProceedAndBuy() const {  return proceedAndBuy; }

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

    void carrelloView::slotOpenDetailView() const{
        detailView->setModal(true);
        detailView->exec();//show

    }


