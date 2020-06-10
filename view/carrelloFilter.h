#ifndef CARRELLOFILTER_H
#define CARRELLOFILTER_H

#include <QSortFilterProxyModel>
#include <QComboBox>

#include "carrelloAdapter.h"

// Crea un modello virtuale utilizzato per la ricerca dei dati su QTableView

class carrelloFilter : public QSortFilterProxyModel
{
private:
        const QComboBox *instrumentType;
protected:
        bool filterAcceptsRow(int, const QModelIndex&) const override;
public:
        carrelloFilter(QObject* = nullptr, const QComboBox* = nullptr);
        bool insertRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
        void removeServerResults();

};

#endif // carrelloFILTER_H
