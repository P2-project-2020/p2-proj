#include "materialComboBoxItemDelegate.h"
#include <QComboBox>
#include "model/hierarchy/strumento.h"
#include "model/hierarchy/pianoforte.h"
#include "model/hierarchy/tromba.h"
#include "model/hierarchy/fiato.h"

#include <QDebug>

MaterialComboBoxItemDelegate::MaterialComboBoxItemDelegate(QObject *parent) :  QStyledItemDelegate(parent)
{

}



MaterialComboBoxItemDelegate::~MaterialComboBoxItemDelegate()
{
}

QWidget *MaterialComboBoxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Create the combobox and populate it
     QComboBox *cb = new QComboBox(parent);
     const int row = index.row();

     QString rowType = index.data().toString();
     qDebug()<<rowType;

     if(rowType == "Pianoforte" )
     for(auto& it: Pianoforte::keys )
     cb->addItem(QString::fromStdString(it));
     return cb;

}

void MaterialComboBoxItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    // get the index of the text in the combobox that matches the current value of the item
    const QString currentText = index.data(Qt::EditRole).toString();
    const int cbIndex = cb->findText(currentText);
    // if it is valid, adjust the combobox
    if (cbIndex >= 0)
       cb->setCurrentIndex(cbIndex);
}

void MaterialComboBoxItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    model->setData(index, cb->currentText(), Qt::EditRole);
}



