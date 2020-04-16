//Qt MVC is based on 2 widgets: QListview & QtableView
// They both provide real time search, edit, ordering and visualization over data
/*Adapter is the class necessary to communicate with our Model and Hierarchy
in order to make possible to use it with Qt MVC widgets*/

#ifndef MAGAZZINOADAPTER_H
#define MAGAZZINOADAPTER_H

#include <QAbstractTableModel>
#include<Model/model.h>

class magazzinoAdapter : public QAbstractTableModel
{
    Q_OBJECT

public:
    magazzinoAdapter();
    enum Role {
                  SortRole=Qt::UserRole
               };

        magazzinoAdapter(QObject *parent = nullptr, Model* = 0);
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant headerData(int,Qt::Orientation,int) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        bool insertRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
        bool removeRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
        void dataRefresh();
        bool setData(const QModelIndex&, const QVariant&, int) override;
        Qt::ItemFlags flags(const QModelIndex&) const override;
        bool searchMatchRegex(unsigned int, const QRegExp&, const QString&) const;
    signals:
        void editCompleted(const Strumento*);
private:
        Model* core;
};

#endif // MAGAZZINOADAPTER_H
