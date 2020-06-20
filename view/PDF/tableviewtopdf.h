#ifndef TABLEVIEWTOPDF_H
#define TABLEVIEWTOPDF_H

#include "view/QTableViews/Magazzino/magazzinoView.h"
#include "view/QTableViews/Carrello/carrelloView.h"
#include <QVBoxLayout>

class tableViewToPdf
{
public:
    tableViewToPdf();
    void printPdf();

private:
    QTableView *table;
    QAbstractItemModel *adapter;


};

#endif // TABLEVIEWTOPDF_H
