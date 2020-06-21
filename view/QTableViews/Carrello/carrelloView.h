#ifndef CARRELLOVIEW_H
#define CARRELLOVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextLine>
#include <QLineEdit>
#include <QTableView>
#include <QComboBox>

#include "model/model.h"
#include "view/QTableViews/Carrello/carrelloFilter.h"
#include "view/QTableViews/Carrello/carrelloAdapter.h"
#include "view/insertView.h"

class carrelloView : public QWidget
{
    Q_OBJECT
    public:
        explicit carrelloView(QWidget *parent = nullptr, Model* = nullptr);

        carrelloAdapter *getAdapter() const;
        carrelloFilter *getFilter() const;
        QTableView *getTable() const;

        QPushButton *getDeleteSelected() const;
        QPushButton *getDeleteAll() const;
        QPushButton *getProceedAndBuy() const;


        QLabel *getResultsNumber() const;
        QLabel *getEditEnabled() const; //USELESS
        insertView *getDetailView() const;

    private:
        Model *core;

        carrelloAdapter *adapter;
        carrelloFilter *filter;
        QTableView *table;

        QPushButton *deleteAll; //svuota carrello
        QPushButton *deleteSelected; //rimuovi dal carrello
        QPushButton *proceedAndBuy; //procedi con l'acquisto

        QLineEdit *searchLine;
        QComboBox *instrumentType;

        QLabel *resultsNumber; //risultati della ricerca
        QLabel *editEnabled; //QPushButton *editEnable; USELESS
        insertView *detailView;

    signals:

    public slots:

        void slotStartFiltering() const;
        void slotOpenDetailView() const;
};

#endif // carrelloVIEW_H
