#ifndef MATERIALCOMBOBOXITEMDELEGATE_H
#define MATERIALCOMBOBOXITEMDELEGATE_H
#include <QStyledItemDelegate>


class MaterialComboBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
     MaterialComboBoxItemDelegate(QObject *parent = nullptr);
    ~MaterialComboBoxItemDelegate();

     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
     void setEditorData(QWidget *editor, const QModelIndex &index) const override;
     void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // MATERIALCOMBOBOXITEMDELEGATE_H

