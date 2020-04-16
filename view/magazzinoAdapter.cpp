//Qt MVC is based on 2 widgets: QListview & QtableView
// They both provide real time search, edit, ordering and visualization over da$
/*Adapter is the class necessary to communicate with our Model and Hierarchy
in order to make possible to use it with Qt MVC widgets*/

#include "magazzinoAdapter.h"
#include <QFont>
#include <QColor>
#include <QBrush>
#include <QVariant>
#include <QPushButton>
#include <QRegExp>
#include <QDebug>

#include <model/hierarchy/arco.h>
#include <model/hierarchy/violino.h>
#include <model/hierarchy/viola.h>
#include <model/hierarchy/corda.h>
#include <model/hierarchy/chitarra.h>
#include <model/hierarchy/basso.h>
#include <model/hierarchy/percussione.h>
#include <model/hierarchy/kitBatteria.h>
#include <model/hierarchy/pianoforte.h>
#include <model/hierarchy/fiato.h>
#include <model/hierarchy/tromba.h>
#include <model/hierarchy/sax.h>


magazzinoAdapter::magazzinoAdapter(QObject* parent, Model *model) :
    QAbstractTableModel(parent),
    core(model)
{

}


int magazzinoAdapter::rowCount(const QModelIndex &) const {
    return core->getMagazzinoSize();
}

int magazzinoAdapter::columnCount(const QModelIndex &) const {
    return 12;
}

QVariant magazzinoAdapter::headerData(int section, Qt::Orientation orientation, int role) const
{

    if(role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return QString("Strumento"); //Chitarra | Basso | Violino | ... -> NON MODIFICABILI

            case 1:
                return QString("Tipo"); //Se c'è Elettrica | Acustica | Classica, cambia in base a Strumento -> alcuni non lo hanno


            case 2:
                return QString("Brand");
            case 3:
                return QString("Materiale");
            case 4:
                return QString("Tonalità");
            case 5:
                return QString("Descrizione");
            case 6:
                return QString("Condizione"); //Nuovo | Usato
            /*
            case 6:
                return QString("Luteria"); //Solo Arco
            case 7:
                return QString("Numero corde"); //Solo Chitarra?
            case 8:
                return QString("Modello"); //Solo Chitarra?
            case 9:
                return QString("Senza tasti"); //Solo Basso?
            case 10:
                return QString("Materiale tasti"); //Solo Pianoforte?
            case 11:
                return QString("Tipo bocchino"); //Solo Fiato
            */

            case 7:
                return QString("Prezzo");
            default:
                return QVariant();
        }
    }
    return QVariant();
}

QVariant magazzinoAdapter::data(const QModelIndex& index, int role) const
{
    unsigned int row = abs(index.row());

    if (!index.isValid() || row >= core->getMagazzinoSize())
            return QVariant();

    Strumento *strumento = core->magazzinoAt(row);

    switch(role)
    {
        case Qt::BackgroundRole:
            return QVariant(QBrush(QColor( (row % 2 == 0) ? "#EEE" : "#FFF")));
        case Qt::TextAlignmentRole:
            return QVariant ( Qt::AlignVCenter | Qt::AlignHCenter );
        case Qt::SizeHintRole:
            return QSize(500, 0 );

    case Qt::EditRole:{// Per fare in modo di non cancellare il contenuto della cella durante l'editing

        switch(index.column())
        {

        case 1:
            return this->index(row,index.column()).data();
        case 2:
            return this->index(row,index.column()).data();
        case 3:
            return this->index(row,index.column()).data();
        case 4:
            return strumento->tune();
        case 5:
            return this->index(row,index.column()).data();
        case 6:
            return strumento->isUsed();
        case 7:
            return strumento->getPrice();
        }
    }
        case Qt::DisplayRole:
        {
            switch(index.column())
            {

            case 0:
                 if(dynamic_cast<Violino*>(strumento))
                       return QString("Violino");
                 else if(dynamic_cast<Viola*>(strumento))
                            return QString("Viola");
                 else if(dynamic_cast<Chitarra*>(strumento))
                            return QString("Chitarra");
                 else if(dynamic_cast<Basso*>(strumento))
                            return QString("Basso");
                 else if(dynamic_cast<Pianoforte*>(strumento))
                            return QString("Pianoforte");
                 else if(dynamic_cast<KitBatteria*>(strumento))
                            return QString("KitBatteria");
                 else if(dynamic_cast<Tromba*>(strumento))
                            return QString("Tromba");
                 else if(dynamic_cast<Sax*>(strumento))
                            return QString("Sax");

                 break;

            case 1:


                if(dynamic_cast<Chitarra*>(strumento)){
                    Chitarra *chitarra = dynamic_cast<Chitarra*>(strumento);

                    if(chitarra) {

                        if(chitarra->getType() == Chitarra::guitarType::classic)
                            return QString("Classica");
                        else if(chitarra->getType() == Chitarra::guitarType::acoustic)
                            return QString("Acustica");
                        else
                            return QString("Elettrica");

                    }

                }

                else if(dynamic_cast<Basso*>(strumento)){
                    Basso *basso = dynamic_cast<Basso*>(strumento);
                    if(basso) {

                        if(basso->getType() == Basso::bassType::acoustic)
                            return QString("Acustico");
                        else
                            return QString("Elettrico");

                    }

                }

                else
                    return QString("Standard");

                break;

            case 2:
                return QString::fromStdString(strumento->getBrand());
                break;
            case 3:
                return QString::fromStdString(strumento->getMaterial());
                break;
            case 4:
                return QString(strumento->tune());
                break;
            case 5:
                return QString::fromStdString(strumento->getDescription());
                break;
            case 6:
                return QString::fromStdString(strumento->isUsed() ? "Usato" : "Nuovo");
                break;
            case 7:
                return QString::number(strumento->getPrice()) + " €";
                break;

            default:
                return QVariant();
                break;
            }
        }

        case SortRole:{

            switch (index.column()){

            case 0:
                return this->index(row,index.column()).data();
                break;
            case 1:
                return this->index(row,index.column()).data();
                break;
            case 2:
                return this->index(row,index.column()).data();
                break;
            case 3:
                return this->index(row,index.column()).data();
                break;
            case 4:
                return this->index(row,index.column()).data();
                break;
            case 5:
                return strumento->tune();
                break;
            case 6:
                return strumento->isUsed();
                break;
            case 7:
                return strumento->getPrice();
                break;


        }

    }//UserRole --> Setting custom sorting role
    }

    return QVariant();
}

bool magazzinoAdapter::insertRows(int begin, int count, const QModelIndex& parent) {
    beginInsertRows(parent, begin, begin + count - 1);
    // Aggiunta di nuove righe
    endInsertRows();
    return true;
}

bool magazzinoAdapter::removeRows(int begin, int count, const QModelIndex& parent)
{
    beginRemoveRows(parent, begin, begin + count - 1);
    core->eraseMagazzino(begin);
    endRemoveRows();
    return true;
}

void magazzinoAdapter::dataRefresh()
{
    beginResetModel();
    endResetModel();
}

//REVISE
bool magazzinoAdapter::setData(const QModelIndex& index, const QVariant& value, int role)
{
    Strumento *strumento = core->magazzinoAt(index.row());//Il prodotto da modificare

    if (role == Qt::EditRole) {

        switch(index.column()){

        case 2: //brand
            strumento->setBrand(value.toString().toStdString());
            break;

        //E' opportuno inserire setMaterial() e setTune() nei sottooggetti che lo necessitano
        /*case 3: //material
            strumento->setMaterial(value.toString().toStdString());
            break;

        case 4: //tune
            strumento->tune(value.toDouble());
            break;
*/
        case 5: //description
            strumento->setDescription(value.toString().toStdString());
            break;

        case 6: //
            strumento->setUsed(value.toBool());
            break;

        case 7: //price
            strumento->setPrice(value.toDouble());
            break;


        default: //Strumento(0) non può essere mdoificato
            return false;
            break;

        }
        emit editCompleted(strumento);
        QModelIndex editIndex = createIndex(index.row(),index.column());
        emit dataChanged(editIndex,editIndex,{Qt::DisplayRole});
        return true;
    }
    return false;
}//setData

Qt::ItemFlags magazzinoAdapter::flags(const QModelIndex& index) const
{
    int col = index.column();
    if( col == 0 || col==1 || col ==8 || col == 10)
        return  Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    else
        return Qt::ItemIsEditable | QAbstractTableModel::flags(index);

}


//REVISE
bool magazzinoAdapter::searchMatchRegex(unsigned int ind, const QRegExp& exp, const QString& instrumentType) const
{
    Strumento* strumento = core->magazzinoAt(ind);
    if(instrumentType == "Tutto")
        return (QString::fromStdString(strumento->className())).contains(exp) ||
               (QString::fromStdString(strumento->getBrand())).contains(exp);
    /*
    else if(thc == "Psicoattivo")
        return ((prod->getThc() > 0.5) && QString::fromStdString(prod->getStrain()).contains(exp)) ||
               ((prod->getThc() > 0.5) && QString::fromStdString(prod->getCategory()).contains(exp));
    else if(thc == "Non psicoattivo")
        return ((prod->getThc() <= 0.5) && QString::fromStdString(prod->getStrain()).contains(exp)) ||
               ((prod->getThc() <= 0.5) && QString::fromStdString(prod->getCategory()).contains(exp));
*/
else
        return false;
}


