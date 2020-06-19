#include "magazzinoFilter.h"

magazzinoFilter::magazzinoFilter(QObject* parent, const QComboBox * filterComboBox)
    : QSortFilterProxyModel (parent), instrumentType(filterComboBox)
{ }

bool magazzinoFilter::insertRows(int begin, int count, const QModelIndex& parent)
{
    bool result = sourceModel()->insertRows(begin, count, parent);
    invalidateFilter();
    return result;
}

bool magazzinoFilter::filterAcceptsRow(int row_source, const QModelIndex&) const
{
    return static_cast<magazzinoAdapter*>(sourceModel())->searchMatchRegex(static_cast<unsigned int>(row_source),
                                                                        filterRegExp(),
                                                                        instrumentType->currentText());
}

