#include "view/QTableViews/Magazzino/magazzinoView.h"
#include "view/QTableViews/tuneComboBoxItemDelegate.h"
#include "view/QTableViews/materialComboBoxItemDelegate.h"

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
    adapter(new magazzinoAdapter(this, core)),
    addNew(new QPushButton),
    deleteAll(new QPushButton),
    deleteSelected(new QPushButton),
    addToCart(new QPushButton),
    searchLine(new QLineEdit),
    instrumentType(new QComboBox),
    addView(new insertView),
    resultsNumber(new QLabel),
    editEnabled(new QLabel)

{
    addNew->setText("Nuovo strumento");

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

        if(!core->getMagazzinoSize()){
            resultsNumber->setText("<b>Per iniziare, carica un salvataggio</b>");
            resultsNumber->setStyleSheet("color : orange");
        }else
        {
            resultsNumber->setText("<b>" + QString::number(core->getMagazzinoSize()) + " strumenti trovati</b>");
            resultsNumber->setStyleSheet("color : green");
        }

        resultBar->addWidget(resultsNumber);
        editEnabled->setText("");
        resultBar->addWidget(editEnabled);
        deleteSelected->setText(" Elimina Selezionato");
        resultBar->addWidget(deleteSelected);
        deleteSelected->setIcon(QIcon::fromTheme("list-remove"));
        deleteSelected->setIconSize(QSize(13,13));
        deleteAll->setText(" Elimina Tutti");
        deleteAll->setIcon(QIcon::fromTheme("edit-delete"));
        deleteAll->setIconSize(QSize(13,13));
        resultBar->addWidget(deleteAll);
        addToCart->setText(" Aggiungi al carrello");
        addToCart->setIcon(QIcon(":/icons/res/cart.png"));
        addNew->setIconSize(QSize(13,13));
        resultBar->addWidget(addToCart);
        addNew->setText(" Nuovo prodotto");
        addNew->setIcon(QIcon::fromTheme("list-add"));
        addNew->setIconSize(QSize(13,13));
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

            TuneComboBoxItemDelegate *tuneComboDelegate = new TuneComboBoxItemDelegate(this);
            MaterialComboBoxItemDelegate *materialComboDelegate = new MaterialComboBoxItemDelegate(this);
            table->setItemDelegateForColumn(5,tuneComboDelegate );// Inserisce QComboBOx su colonna 4
            table->setItemDelegateForColumn(4,materialComboDelegate );// Inserisce QComboBOx su colonna 4

        /* Creazione Tabella e configurazione filtraggio (ricerca) e sorting per ogni campo di essa */
            search->addWidget(table);
            setLayout(search);


        connect(addNew,SIGNAL(clicked()), this, SLOT(slotOpenInsertView()));
        connect(instrumentType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotStartFiltering()));
        connect(searchLine, SIGNAL(textChanged(QString)), this, SLOT(slotStartFiltering()));

    }

    magazzinoAdapter* magazzinoView::getAdapter() const{ return adapter;}

    void magazzinoView::slotOpenInsertView() const{
        addView->setModal(true);
        addView->exec();//show

    }

    magazzinoFilter *magazzinoView::getFilter() const{ return filter;}

    QLabel *magazzinoView::getEditEnabled() const{ return editEnabled;}

    QTableView *magazzinoView::getTable() const{ return table;}

    QPushButton *magazzinoView::getDeleteSelected() const{ return deleteSelected; }
    QPushButton *magazzinoView::getDeleteAll() const{ return deleteAll; }
    QPushButton *magazzinoView::getAddToCart() const { return addToCart; }
    insertView *magazzinoView::getAddView() const { return addView; }
    void magazzinoView::setAddView(Strumento* strumento)  { this->addView = new insertView(this,strumento); }

    QLabel *magazzinoView::getResultsNumber() const{ return resultsNumber; }


    void magazzinoView::slotStartFiltering() const
    {

        QRegExp regex(searchLine->text(), Qt::CaseInsensitive, QRegExp::Wildcard);
        filter->setFilterRegExp(regex);
        int numberRes = filter->rowCount();
        if(numberRes) {
            resultsNumber->setText("<b>" + QString::number(numberRes) + " risultati trovati </b>");
            resultsNumber->setStyleSheet("color: green;");
        }
        else {
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


