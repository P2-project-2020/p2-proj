#ifndef PDFFACTORY_H
#define PDFFACTORY_H

#include <QAbstractTableModel>
#include "model/model.h"

class PdfFactory
{
private:
    QAbstractTableModel *magazzinoAdapter;
    QAbstractTableModel *carrelloAdapter;
    Model *model;
public:
    PdfFactory(QAbstractTableModel*,QAbstractTableModel*, Model*);
    bool printTable(int, QString);
    bool printReceipt(QString);
};

#endif // PDFFACTORY_H
