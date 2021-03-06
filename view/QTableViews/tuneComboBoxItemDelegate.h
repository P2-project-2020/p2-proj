#ifndef TuneComboBoxItemDelegate_H
#define TuneComboBoxItemDelegate_H

#include <QStyledItemDelegate>

class TuneComboBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TuneComboBoxItemDelegate(QObject *parent = nullptr);
    ~TuneComboBoxItemDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // TuneComboBoxItemDelegate_H
