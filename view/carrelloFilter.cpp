#include "carrelloFilter.h"

carrelloFilter::carrelloFilter(QObject* parent, const QComboBox * filterComboBox)
    : QSortFilterProxyModel (parent), instrumentType(filterComboBox)
{ }

bool carrelloFilter::insertRows(int begin, int count, const QModelIndex& parent)
{
    bool result = sourceModel()->insertRows(begin, count, parent);
    invalidateFilter();
    return result;
}

bool carrelloFilter::filterAcceptsRow(int row_source, const QModelIndex&) const
{
    return static_cast<carrelloAdapter*>(sourceModel())->searchMatchRegex(static_cast<unsigned int>(row_source),
                                                                        filterRegExp(),
                                                                        instrumentType->currentText());
}

void carrelloFilter::removeServerResults()
{
    while(rowCount())
        removeRows(0,1); // Rimuovo ciascun nodo visualizzato
}
