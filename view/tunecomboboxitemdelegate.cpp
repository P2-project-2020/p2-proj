#include "TuneComboBoxItemDelegate.h"
#include <QComboBox>

TuneComboBoxItemDelegate::TuneComboBoxItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


TuneComboBoxItemDelegate::~TuneComboBoxItemDelegate()
{
}


QWidget *TuneComboBoxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Create the combobox and populate it
    QComboBox *cb = new QComboBox(parent);
    const int row = index.row();
    cb->addItem(QString("undefined %1").arg(row));
    cb->addItem(QString("soprano %1").arg(row));
    cb->addItem(QString("contralto %1").arg(row));
    cb->addItem(QString("tenore %1").arg(row));
    cb->addItem(QString("baritono %1").arg(row));
    cb->addItem(QString("basso %1").arg(row));
    return cb;
}


void TuneComboBoxItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
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


void TuneComboBoxItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    model->setData(index, cb->currentText(), Qt::EditRole);
}
