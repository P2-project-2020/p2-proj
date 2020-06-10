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
#include "insertView.h"
#include "carrelloFilter.h"
#include "carrelloAdapter.h"

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

        insertView* getAddView() const;
        QLabel *getResultsNumber() const;
        QLabel *getEditEnabled() const;

    private:
        Model *core;

        carrelloAdapter *adapter;
        carrelloFilter *filter;
        QTableView *table;

        QPushButton *addNew;
        QPushButton *deleteAll;
        QPushButton *deleteSelected;

        QLineEdit *searchLine;
        QComboBox *instrumentType;

        insertView *addView;

        QLabel *resultsNumber; //risultati della ricerca
        QLabel *editEnabled; //QPushButton *editEnable;




    signals:

    public slots:
        void slotOpenInsertView() const;
        void slotStartFiltering() const;
};

#endif // carrelloVIEW_H
