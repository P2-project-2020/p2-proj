#ifndef MAGAZZINOVIEW_H
#define MAGAZZINOVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextLine>
#include <QLineEdit>
#include <QTableView>
#include <QComboBox>

#include "Model/model.h"
#include "addView.h"
#include "magazzinoFilter.h"
#include "magazzinoAdapter.h"

class magazzinoView : public QWidget
{
    Q_OBJECT
    public:
        explicit magazzinoView(QWidget *parent = nullptr, Model* = nullptr);

        magazzinoAdapter *getAdapter() const;
        magazzinoFilter *getFilter() const;
        QTableView *getTable() const;

        QPushButton *getDeleteSelected() const;
        QPushButton *getDeleteAll() const;

        addView* getAddNew() const;
        QLabel *getResultsNumber() const;
        QLabel *getEditEnabled() const;

    private:
        Model *core;

        magazzinoAdapter *adapter;
        magazzinoFilter *filter;
        QTableView *table;

        QPushButton *addNew;
        QPushButton *deleteAll;
        QPushButton *deleteSelected;

        QLineEdit *searchLine;
        QComboBox *instrumentType;

        addView *addView;

        QLabel *resultsNumber; //risultati della ricerca
        QLabel *editEnabled; //QPushButton *editEnable;




    signals:

    public slots:
        void slotOpenAddView() const;
        void slotStartFiltering() const;
};

#endif // MAGAZZINOVIEW_H
