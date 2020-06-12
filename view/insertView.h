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
#include <QWidget>
#include <string>


class insertView : public QDialog
{
  Q_OBJECT
private:

    QComboBox *instrumentType; //Arco | Corda | Percussione | Fiato

    QGroupBox* generalInfo;
    QLineEdit *price;
    QLineEdit *description;
    QLineEdit *brand;
    QComboBox *instrumentTune;
    QCheckBox *isSecondHand;

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
    QComboBox *percussioneMaterial; //Legno | Plexiglass
    QCheckBox *isTuned;

//Pianoforte
//Vedi Corda<-Pianoforte
//Kit Batteria
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

   private slots:

   void slotReset();
   void slotRestart();

public:

   insertView(QWidget * =nullptr);

    //Strumento
    QComboBox *getInstrumentType() const;
    QLineEdit *getPrice() const;
    QLineEdit *getDescription() const;
    QLineEdit *getBrand() const;
    QComboBox *getInstrumentTune() const;
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
    QComboBox *getPercussioneMaterial() const;
    QCheckBox *getIsTuned() const;

    //Kit Batteria
    QCheckBox *getIsMetalSnare() const;

    //Fiato
    QComboBox *getFiatoType() const;
    QComboBox *getFiatoMaterial() const;


    QPushButton *getAddItemButton() const;
    QPushButton *getResetFieldsButton() const;
    void showWarningDialog(QWidget* = nullptr, QString ="") const;

public slots:
    void slotDisableElements(int) const;
    void slotDisableCorda(int) const;
    void slotDisablePercussione(int) const;


signals:
    void signalDisableElements(int);
    void signalDisableCorda(int);
    void signalDisablePercussione(int);

};

#endif // INSERTVIEW_H
