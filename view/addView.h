#ifndef ADDITEM_H
#define ADDITEM_H

#include <QComboBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QWidget>
#include <string>


class addView : public QDialog
{
  Q_OBJECT
private:

    QComboBox *instrumentType; //Arco | Corda | Percussione | Fiato

    QLineEdit *name;
    QLineEdit *description;
    QLineEdit *material;
    QLineEdit *brand;
    QLineEdit *productionYear;
    QLineEdit *basePrice;
    QCheckBox *isSecondHand;

//*******************************************
//Arco
    QComboBox *arcoType; //Violino | Viola
    QCheckBox *isLutherie;
//Violino
//Viola

//*******************************************
//Corda
    QComboBox *cordaType; //Chitarra | Basso | Pianoforte
    QLineEdit *stringsNumber;
//Chitarra
    QComboBox *guitarType; //Eletric | Acoustic | Classic
    QLineEdit *model;
//Basso
    QComboBox *bassType; //Eletric | Acoustic
    QCheckBox *isFretless;
//Pianoforte
    QComboBox *pianoShape; //Grand | Upright
    QComboBox *keysMaterial; //Wood | Plastic  Ivory


//*******************************************
//Percussione
    QComboBox *percussioneType; //Pianoforte | kit Batteria
    QCheckBox *hasSticks;
    QCheckBox *isTuned;
//Pianoforte
//Vedi Corda<-Pianoforte
//Kit Batteria
    QCheckBox *isMetalSnare;

//*******************************************
//Fiato
    QComboBox *fiatoType; //Sax | Tromba |
    QComboBox *mouthPieceType; //Woodwind | Brass
//Sax
//Tromba

//*******************************************
    QPushButton *addItem; //Aggiunge un nuovo item alla lista di quelli disponibili(al magazzino)
    QPushButton *resetFields; //Resetta i campi dell'item con i valori di default

   private slots:

    void slotReset();
    void slotRestart();

public:

    addView(QWidget * =nullptr);

    //Strumento
    QComboBox *getInstrumentType() const;

    QLineEdit *getName() const;
    QLineEdit *getDescription() const;
    QLineEdit *getMaterial() const;
    QLineEdit *getBrand() const;
    QLineEdit *getProductionYear() const;
    QLineEdit *getBasePrice() const;
    QCheckBox *getIsSecondHand() const;

    //Arco
    QComboBox *getArcoType() const;
    QCheckBox *getIsLutherie() const;

    //Corda
    QComboBox *getCordaType() const;
    QLineEdit *getStringsNumber() const;

    //Chitarra
    QComboBox *getGuitarType() const;
    QLineEdit *getModel() const;

    //Basso
    QComboBox *getBassType() const;
    QCheckBox *getIsFretless() const;

    //Pianoforte
    QComboBox *getPianoShape() const;
    QComboBox *getKeysMaterial() const;

    //Percussione
    QComboBox *getPercussioneType() const;
    QCheckBox *getHasSticks() const;
    QCheckBox *getIsTuned() const;

    //Kit Batteria
    QCheckBox *getIsMetalSnare() const;

    //Fiato
    QComboBox *getFiatoType() const;
    QComboBox *getMouthPieceType() const;


    QPushButton *getAddItemButton() const;
    //QPushButton *getResetFieldsButton() const;
    void showWarningDialog(QWidget* = nullptr, QString ="") const;

public slots:
    void slotDisableElements(int)const;
signals:
    void signalDisableElements(int);
};

#endif // ADDITEM_H
