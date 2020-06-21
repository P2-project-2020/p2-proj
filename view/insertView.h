#ifndef INSERTVIEW_H
#define INSERTVIEW_H


#include <QComboBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QDialog>
#include <QTextEdit>
#include <QWidget>
#include <string>
#include <QSpinBox>
#include "imageControlBox.h"
#include "model/hierarchy/strumento.h"

class insertView : public QDialog
{
  Q_OBJECT
private:

    Strumento *instrumentPointer;
    QComboBox *instrumentType; //Arco | Corda | Percussione | Fiato

    QLabel* title;
    QGroupBox* generalInfo;
    QLineEdit *price;
    QTextEdit *description;
    QLineEdit *brand;
    QLineEdit *model;
    QComboBox *instrumentTune;
    QCheckBox *isSecondHand;
    QSpinBox *quantity;

    QGroupBox* specificInfo;
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
    //Basso
    QComboBox *bassType; //Eletric | Acoustic
    QCheckBox *isFretless;
//Pianoforte
    QComboBox *pianoShape; //Grand | Upright
    QComboBox *keysMaterial; //Wood | Plastic  Ivory


//*******************************************
//Percussione
    QComboBox *percussioneType; //Pianoforte | kit Batteria

//Pianoforte
//Vedi Corda<-Pianoforte
//Kit Batteria
    QComboBox *percussioneMaterial; //Legno | Plexiglass
    QCheckBox *isMetalSnare;

//*******************************************
//Fiato
    QComboBox *fiatoType; //Sax | Tromba
    QComboBox *fiatoMaterial; //Argento | Ottone | Plastica
//Sax
//Tromba

//*******************************************
     QPushButton *addItem; //Aggiunge un nuovo item alla lista di quelli disponibili(al magazzino)
     QPushButton *resetFields; //Resetta i campi dell'item con i valori di default
     QPushButton *editItem; //Utilizzabile solo per editare
     
     ImageControlBox* image;
     QString imgPath;

   private slots:

     void slotReset();
     void slotRestart();
     void slotSetImage(const QString&);

public:

     insertView(QWidget* = nullptr, Strumento* = nullptr);

    //Strumento
     QComboBox *getInstrumentType() const;
     QLabel *getTitle() const;
     QLineEdit *getPrice() const;
     QTextEdit *getDescription() const;
     QLineEdit *getBrand() const;
     QLineEdit *getModel() const;
     QComboBox *getInstrumentTune() const;
     QCheckBox *getIsSecondHand() const;
     QSpinBox *getQuantity() const;
     QString getImgPath() const;
     Strumento* getStrumento() const;

    //Arco
    QComboBox *getArcoType() const;
    QCheckBox *getIsLutherie() const;

    //Corda
    QComboBox *getCordaType() const;
    QLineEdit *getStringsNumber() const;

    //Chitarra
    QComboBox *getGuitarType() const;

    //Basso
    QComboBox *getBassType() const;
    QCheckBox *getIsFretless() const;

    //Pianoforte
    QComboBox *getPianoShape() const;
    QComboBox *getKeysMaterial() const;

    //Percussione
    QComboBox *getPercussioneType() const;

    //Kit Batteria
    QComboBox *getPercussioneMaterial() const;
    QCheckBox *getIsMetalSnare() const;

    //Fiato
    QComboBox *getFiatoType() const;
    QComboBox *getFiatoMaterial() const;

    QPushButton *getAddItemButton() const;
    QPushButton *getEditItemButton() const;
    void setStrumento(Strumento*,bool=true);
    QPushButton *getResetFieldsButton() const;
    void showWarningDialog(QWidget* = nullptr, QString ="") const;

public slots:
    void slotDisableElements(int) const;
    void slotDisableCorda(int) const;
    void slotDisablePercussione(int) const;
    void slotDisableArco(int) const;


signals:
    void signalDisableElements(int);
    void signalDisableCorda(int);
    void signalDisablePercussione(int);
    void signalDisableArcoe(int);

};

#endif // INSERTVIEW_H
