#ifndef MAGAZZINOFILTER_H
#define MAGAZZINOFILTER_H

#include <QSortFilterProxyModel>
#include <QComboBox>

#include "magazzinoAdapter.h"

// Crea un modello virtuale utilizzato per la ricerca dei dati su QTableView

class magazzinoFilter : public QSortFilterProxyModel
{
private:
        const QComboBox *instrumentType;
protected:
        bool filterAcceptsRow(int, const QModelIndex&) const override;
public:
        magazzinoFilter(QObject* = nullptr, const QComboBox* = nullptr);
        bool insertRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
        void removeServerResults();

};

#endif // MAGAZZINOFILTER_H
