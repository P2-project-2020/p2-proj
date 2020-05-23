#include "insertView.h"

#include <QString>
#include <iostream>
#include <QMessageBox>
#include <QBuffer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>




insertView::insertView(QWidget* p):
    QDialog (p),
    instrumentType(new QComboBox(this)),
    price(new QLineEdit(this)),
    description(new QLineEdit(this)),
    brand(new QLineEdit(this)),
    instrumentTune(new QComboBox(this)),
    isSecondHand(new QCheckBox(this)),

    arcoType(new QComboBox(this)),
    isLutherie(new QCheckBox(this)),
    cordaType(new QComboBox(this)),
    stringsNumber(new QLineEdit(this)),
    guitarType(new QComboBox(this)),
    model(new QLineEdit(this)),
    bassType(new QComboBox(this)),
    isFretless(new QCheckBox(this)),

    pianoShape(new QComboBox(this)),
    keysMaterial(new QComboBox(this)),

    percussioneType(new QComboBox(this)),
    percussioneMaterial(new QComboBox(this)),
    isTuned(new QCheckBox(this)),
    isMetalSnare(new QCheckBox(this)),

    fiatoType(new QComboBox(this)),
    mouthPieceType(new QComboBox(this)),
    fiatoMaterial(new QComboBox(this)),

    addItem(new QPushButton("Inserisci",this)),
    resetFields(new QPushButton("Reset",this))
{
    QVBoxLayout *form = new QVBoxLayout(this);

    QVBoxLayout *generalForm= new QVBoxLayout;
    generalForm->setSpacing(5);

    instrumentType->addItem("Scegli il tipo di strumento");
    instrumentType->addItem("Arco");
    instrumentType->addItem("Corda");
    instrumentType->addItem("Percussione");
    instrumentType->addItem("Fiato");

    price->setPlaceholderText("Prezzo strumento");
    price->setValidator( new QDoubleValidator(0.01,100000,2,this));
    description->setPlaceholderText("Descrizione strumento");
    brand->setPlaceholderText("Marca strumento");

    instrumentTune->addItem("Scegli il tipo di tonalità");
    instrumentTune->addItem("Indefinita");
    instrumentTune->addItem("Soprano");
    instrumentTune->addItem("Contralto");
    instrumentTune->addItem("Tenore");
    instrumentTune->addItem("Baritono");
    instrumentTune->addItem("Basso");

    isSecondHand->setText("Strumento di seconda mano");



    generalForm->addWidget(instrumentType);
    generalForm->addWidget(price);
    generalForm->addWidget(description);
    generalForm->addWidget(brand);
    generalForm->addWidget(instrumentTune);
    generalForm->addWidget(isSecondHand);

    QVBoxLayout* specificForm = new QVBoxLayout;
    specificForm->setSpacing(5);

    QHBoxLayout *arcForm = new QHBoxLayout;
    arcForm->setSpacing(12);

    arcoType->addItem("Scegli il tipo di strumento ad arco");
    arcoType->addItem("Violino");
    arcoType->addItem("Viola");
    isLutherie->setText("Strumento di liuteria");

    arcForm->addWidget(arcoType);
    arcForm->addWidget(isLutherie);

    specificForm->addItem(arcForm);

    QHBoxLayout *stringForm = new QHBoxLayout;
    stringForm->setSpacing(12);

    cordaType->addItem("Scegli il tipo di strumento a corda");
    cordaType->addItem("Chitarra");
    cordaType->addItem("Basso");
    cordaType->addItem("Pianoforte");

    stringsNumber->setPlaceholderText("Numero di corde");

    stringForm->addWidget(cordaType);
    stringForm->addWidget(stringsNumber);

    specificForm->addItem(stringForm);

    QHBoxLayout *guitarForm = new QHBoxLayout;
    guitarForm->setSpacing(12);

    guitarType->addItem("Scegli il tipo di chitarra");
    guitarType->addItem("Elettrica");
    guitarType->addItem("Acustica");
    guitarType->addItem("Classica");
    model->setPlaceholderText("Modello di chitarra");

    guitarForm->addWidget(guitarType);
    guitarForm->addWidget(model);

    specificForm->addItem(guitarForm);

    QHBoxLayout *bassForm = new QHBoxLayout;
    bassForm->setSpacing(12);

    bassType->addItem("Scegli il tipo di basso");
    bassType->addItem("Elettrico");
    bassType->addItem("Acustico");
    isFretless->setText("Basso senza tasti");

    bassForm->addWidget(bassType);
    bassForm->addWidget(isFretless);

    specificForm->addItem(bassForm);

    QHBoxLayout *pianoForm = new QHBoxLayout;
    pianoForm->setSpacing(12);

    pianoShape->addItem("Scegli il tipo di pianoforte");
    pianoShape->addItem("Coda");
    pianoShape->addItem("Muro");
    keysMaterial->addItem("Scegli il materiale dei tasti");
    keysMaterial->addItem("Legno");
    keysMaterial->addItem("Plastica");
    keysMaterial->addItem("Avorio");

    pianoForm->addWidget(pianoShape);
    pianoForm->addWidget(keysMaterial);

    specificForm->addItem(pianoForm);

    QHBoxLayout *percussioneForm = new QHBoxLayout;
    percussioneForm->setSpacing(12);

    percussioneType->addItem("Scegli il tipo di strumento a percussione");
    percussioneType->addItem("Pianoforte");
    percussioneType->addItem("Kit Batteria");
    percussioneMaterial->addItem("Scegli il tipo di materiale");
    percussioneMaterial->addItem("Woodkit");
    percussioneMaterial->addItem("Plexiglass");
    isTuned->setText("Strumento con tonalità");


    percussioneForm->addWidget(percussioneType);
    percussioneForm->addWidget(percussioneMaterial);
    percussioneForm->addWidget(isTuned);

    specificForm->addItem(percussioneForm);


    isMetalSnare->setText("Rullante");

    specificForm->addWidget(isMetalSnare);

    QHBoxLayout *fiatoForm = new QHBoxLayout;
    fiatoForm->setSpacing(12);

    fiatoType->addItem("Scegli il tipo di strumento a fiato");
    fiatoType->addItem("Sassofono");
    fiatoType->addItem("Tromba");
    mouthPieceType->addItem("Scegli il tipo di bocchino");
    mouthPieceType->addItem("Legno");
    mouthPieceType->addItem("Ottone");
    fiatoMaterial->addItem("Scegli il tipo di materiale");
    fiatoMaterial->addItem("Argento");
    fiatoMaterial->addItem("Ottone");
    fiatoMaterial->addItem("Plastica");

    fiatoForm->addWidget(fiatoType);
    fiatoForm->addWidget(mouthPieceType);
    fiatoForm->addWidget(fiatoMaterial);

    specificForm->addItem(fiatoForm);


    /*
    QGroupBox* general = new QGroupBox("Informazioni generali");
    general->setLayout(generalForm);

    QGroupBox* specific = new QGroupBox("Dettaglio strumento");
    specific->setLayout(specificForm);

    */

    form->addItem(generalForm);
    form->addItem(specificForm);


      

    QHBoxLayout* buttonsLayout= new QHBoxLayout;
    buttonsLayout->addWidget(addItem);
    buttonsLayout->addWidget(resetFields);
    buttonsLayout->setSpacing(5);
    form->addItem(buttonsLayout);

    slotDisableElements(0);
    //slotDisableCorda(0);

    //this->setFixedSize(600,600);
    //window->viewIns->setSizeConstraint( QLayout::SetFixedSize );

    connect(instrumentType,SIGNAL(activated(int)),this,SLOT(slotDisableElements(int)));
    //connect(cordaType,SIGNAL(activated(int)),this,SLOT(slotDisableCorda(int)));
    connect(resetFields,SIGNAL(clicked()),this,SLOT(slotReset()));
    connect(this,SIGNAL(rejected()),this,SLOT(slotRestart()));


}




void insertView::slotRestart(){

    instrumentType->show();
    price->hide();
    description->hide();
    brand->hide();
    instrumentTune->hide();
    isSecondHand->hide();
    arcoType->hide();
    isLutherie->hide();
    cordaType->hide();
    stringsNumber->hide();
    guitarType->hide();
    model->hide();
    bassType->hide();
    isFretless->hide();
    pianoShape->hide();
    keysMaterial->hide();
    percussioneType->hide();
    percussioneMaterial->hide();
    isTuned->hide();
    isMetalSnare->hide();
    fiatoType->hide();
    mouthPieceType->hide();
    fiatoMaterial->hide();

    slotReset();

    instrumentType->setEnabled(true);
    price->setEnabled(false);
    description->setEnabled(false);
    brand->setEnabled(false);
    instrumentTune->setEnabled(false);
    isSecondHand->setEnabled(false);
    arcoType->setEnabled(false);
    isLutherie->setEnabled(false);
    cordaType->setEnabled(false);
    stringsNumber->setEnabled(false);
    guitarType->setEnabled(false);
    model->setEnabled(false);
    bassType->setEnabled(false);
    isFretless->setEnabled(false);
    pianoShape->setEnabled(false);
    keysMaterial->setEnabled(false);
    percussioneType->setEnabled(false);
    percussioneMaterial->setEnabled(false);
    isTuned->setEnabled(false);
    isMetalSnare->setEnabled(false);
    fiatoType->setEnabled(false);
    mouthPieceType->setEnabled(false);
    fiatoMaterial->setEnabled(false);


}

    void insertView::slotReset(){

    instrumentType->setCurrentIndex(0);
    price->setText("");
    description->setText("");
    brand->setText("");
    instrumentTune->setCurrentIndex(0);
    isSecondHand->setChecked(false);

    arcoType->setCurrentIndex(0);
    isLutherie->setChecked(false);
//Violino
//Viola

//*******************************************
//Corda
    cordaType->setCurrentIndex(0);
    stringsNumber->setText("");
//Chitarra
    guitarType->setCurrentIndex(0);
    model->setText("");
//Basso
    bassType->setCurrentIndex(0);
    isFretless->setChecked(false);
//Pianoforte
    pianoShape->setCurrentIndex(0);
    keysMaterial->setCurrentIndex(0);


//*******************************************
//Percussione
    percussioneType->setCurrentIndex(0);
    percussioneMaterial->setCurrentIndex(0);
    isTuned->setChecked(false);
//Pianoforte
//Vedi Corda<-Pianoforte!
//Kit Batteria
    isMetalSnare->setChecked(false);

//*******************************************
//Fiato
    fiatoType->setCurrentIndex(0);
    mouthPieceType->setCurrentIndex(0);
    fiatoMaterial->setCurrentIndex(0);

}

void insertView::slotDisableElements(int index) const
{

    switch (index) {
    case 1://Arco

        instrumentType->show();
        price->show();
        description->show();
        brand->show();
        instrumentTune->show();
        isSecondHand->show();
        arcoType->show();
        isLutherie->show();
        cordaType->hide();
        stringsNumber->hide();
        guitarType->hide();
        model->hide();
        bassType->hide();
        isFretless->hide();
        pianoShape->hide();
        keysMaterial->hide();
        percussioneType->hide();
        percussioneMaterial->hide();
        isTuned->hide();
        isMetalSnare->hide();
        fiatoType->hide();
        mouthPieceType->hide();
        fiatoMaterial->hide();

        instrumentType->setEnabled(true);
        price->setEnabled(true);
        description->setEnabled(true);
        brand->setEnabled(true);
        instrumentTune->setEnabled(true);
        isSecondHand->setEnabled(true);
        arcoType->setEnabled(true);
        isLutherie->setEnabled(true);
        cordaType->setEnabled(false);
        stringsNumber->setEnabled(false);
        guitarType->setEnabled(false);
        model->setEnabled(false);
        bassType->setEnabled(false);
        isFretless->setEnabled(false);
        pianoShape->setEnabled(false);
        keysMaterial->setEnabled(false);
        percussioneType->setEnabled(false);
        percussioneMaterial->setEnabled(false);
        isTuned->setEnabled(false);
        isMetalSnare->setEnabled(false);
        fiatoType->setEnabled(false);
        mouthPieceType->setEnabled(false);
        fiatoMaterial->setEnabled(false);

        break;
    case 2://Corda



        instrumentType->show();
        price->show();
        description->show();
        brand->show();
        instrumentTune->show();
        isSecondHand->show();
        arcoType->hide();
        isLutherie->hide();
        cordaType->show();
        stringsNumber->show();

        //-----------------------------
        guitarType->hide();
        model->hide();
        bassType->hide();
        isFretless->hide();
        pianoShape->hide();
        keysMaterial->hide();
        //----------------------------

        percussioneType->hide();
        percussioneMaterial->hide();
        isTuned->hide();
        isMetalSnare->hide();
        fiatoType->hide();
        mouthPieceType->hide();
        fiatoMaterial->hide();

        instrumentType->setEnabled(true);
        price->setEnabled(true);
        description->setEnabled(true);
        brand->setEnabled(true);
        instrumentTune->setEnabled(true);
        isSecondHand->setEnabled(true);
        arcoType->setEnabled(false);
        isLutherie->setEnabled(false);
        cordaType->setEnabled(true);
        stringsNumber->setEnabled(true);

        guitarType->setEnabled(false);
        model->setEnabled(false);
        bassType->setEnabled(false);
        isFretless->setEnabled(false);
        pianoShape->setEnabled(false);
        keysMaterial->setEnabled(false);

        percussioneType->setEnabled(false);
        percussioneMaterial->setEnabled(false);
        isTuned->setEnabled(false);
        isMetalSnare->setEnabled(false);
        fiatoType->setEnabled(false);
        mouthPieceType->setEnabled(false);
        fiatoMaterial->setEnabled(false);


        break;

    case 3://Percussione
        instrumentType->show();
        price->show();
        description->show();
        brand->show();
        instrumentTune->show();
        isSecondHand->show();
        arcoType->hide();
        isLutherie->hide();
        cordaType->hide();
        stringsNumber->hide();

        guitarType->hide();
        model->hide();
        bassType->hide();
        isFretless->hide();
        pianoShape->hide();
        keysMaterial->hide();

        percussioneType->show();
        percussioneMaterial->show();
        isTuned->show();
        /*-----------------------------------*/
        isMetalSnare->hide();
        /*-----------------------------------*/
        fiatoType->hide();
        mouthPieceType->hide();
        fiatoMaterial->hide();

        instrumentType->setEnabled(true);
        price->setEnabled(true);
        description->setEnabled(true);
        brand->setEnabled(true);
        instrumentTune->setEnabled(true);
        isSecondHand->setEnabled(true);
        arcoType->setEnabled(false);
        isLutherie->setEnabled(false);
        cordaType->setEnabled(false);
        stringsNumber->setEnabled(false);

        guitarType->setEnabled(false);
        model->setEnabled(false);
        bassType->setEnabled(false);
        isFretless->setEnabled(false);
        pianoShape->setEnabled(false);
        keysMaterial->setEnabled(false);

        percussioneType->setEnabled(true);
        percussioneMaterial->setEnabled(true);
        isTuned->setEnabled(true);
        /*----------------------------------------*/
        isMetalSnare->setEnabled(false);
        /*----------------------------------------*/
        fiatoType->setEnabled(false);
        mouthPieceType->setEnabled(false);
        fiatoMaterial->setEnabled(false);

        break;

    case 4://Fiato

        instrumentType->show();
        price->show();
        description->show();
        brand->show();
        instrumentTune->show();
        isSecondHand->show();
        arcoType->hide();
        isLutherie->hide();
        cordaType->hide();
        stringsNumber->hide();

        guitarType->hide();
        model->hide();
        bassType->hide();
        isFretless->hide();
        pianoShape->hide();
        keysMaterial->hide();

        percussioneType->hide();
        percussioneMaterial->hide();
        isTuned->hide();
        isMetalSnare->hide();
        fiatoType->show();
        mouthPieceType->show();
        fiatoMaterial->show();

        instrumentType->setEnabled(true);
        price->setEnabled(true);
        description->setEnabled(true);
        brand->setEnabled(true);
        instrumentTune->setEnabled(true);
        isSecondHand->setEnabled(true);
        arcoType->setEnabled(false);
        isLutherie->setEnabled(false);
        cordaType->setEnabled(false);
        stringsNumber->setEnabled(false);
        guitarType->setEnabled(false);
        model->setEnabled(false);
        bassType->setEnabled(false);
        isFretless->setEnabled(false);
        pianoShape->setEnabled(false);
        keysMaterial->setEnabled(false);
        percussioneType->setEnabled(false);
        percussioneMaterial->setEnabled(false);
        isTuned->setEnabled(false);
        isMetalSnare->setEnabled(false);
        fiatoType->setEnabled(true);
        mouthPieceType->setEnabled(true);
        fiatoMaterial->setEnabled(true);


        break;

    default:

        instrumentType->show();
        price->hide();
        description->hide();
        brand->hide();
        instrumentTune->hide();
        isSecondHand->hide();
        arcoType->hide();
        isLutherie->hide();
        cordaType->hide();
        stringsNumber->hide();

        guitarType->hide();
        model->hide();
        bassType->hide();
        isFretless->hide();
        pianoShape->hide();
        keysMaterial->hide();

        percussioneType->hide();
        percussioneMaterial->hide();
        isTuned->hide();
        isMetalSnare->hide();
        fiatoType->hide();
        mouthPieceType->hide();
        fiatoMaterial->hide();

        instrumentType->setEnabled(true);
        price->setEnabled(false);
        description->setEnabled(false);
        brand->setEnabled(false);
        instrumentTune->setEnabled(false);
        isSecondHand->setEnabled(false);
        arcoType->setEnabled(false);
        isLutherie->setEnabled(false);
        cordaType->setEnabled(false);
        stringsNumber->setEnabled(false);
        guitarType->setEnabled(false);
        model->setEnabled(false);
        bassType->setEnabled(false);
        isFretless->setEnabled(false);
        pianoShape->setEnabled(false);
        keysMaterial->setEnabled(false);
        percussioneType->setEnabled(false);
        percussioneMaterial->setEnabled(false);
        isTuned->setEnabled(false);
        isMetalSnare->setEnabled(false);
        fiatoType->setEnabled(false);
        mouthPieceType->setEnabled(false);
        fiatoMaterial->setEnabled(false);
    }
}


/*
void insertView::slotDisableCorda(int index) const {

    switch (index) {
    case 1://Guitar

        instrumentType->show();
        price->show();
        description->show();
        brand->show();
        instrumentTune->show();
        isSecondHand->show();
        arcoType->hide();
        isLutherie->hide();
        cordaType->show();
        stringsNumber->show();

        guitarType->show();
        model->show();

        bassType->hide();
        isFretless->hide();

        pianoShape->hide();
        keysMaterial->hide();


        percussioneType->hide();
        percussioneMaterial->hide();
        isTuned->hide();
        isMetalSnare->hide();
        fiatoType->hide();
        mouthPieceType->hide();
        fiatoMaterial->hide();

        break;

    case 2://Bass

        instrumentType->show();
        price->show();
        description->show();
        brand->show();
        instrumentTune->show();
        isSecondHand->show();
        arcoType->hide();
        isLutherie->hide();
        cordaType->show();
        stringsNumber->show();

        guitarType->hide();
        model->hide();

        bassType->show();
        isFretless->show();

        pianoShape->hide();
        keysMaterial->hide();


        percussioneType->hide();
        percussioneMaterial->hide();
        isTuned->hide();
        isMetalSnare->hide();
        fiatoType->hide();
        mouthPieceType->hide();
        fiatoMaterial->hide();

        break;

    case 3://Piano

        instrumentType->show();
        price->show();
        description->show();
        brand->show();
        instrumentTune->show();
        isSecondHand->show();
        arcoType->hide();
        isLutherie->hide();
        cordaType->show();
        stringsNumber->show();

        guitarType->hide();
        model->hide();

        bassType->hide();
        isFretless->hide();

        pianoShape->show();
        keysMaterial->show();

        percussioneType->hide();
        percussioneMaterial->hide();
        isTuned->hide();
        isMetalSnare->hide();
        fiatoType->hide();
        mouthPieceType->hide();
        fiatoMaterial->hide();

        break;


    default:

        instrumentType->show();
        price->show();
        description->show();
        brand->show();
        instrumentTune->show();
        isSecondHand->show();
        arcoType->hide();
        isLutherie->hide();
        cordaType->show();
        stringsNumber->show();

        guitarType->hide();
        model->hide();

        bassType->hide();
        isFretless->hide();

        pianoShape->hide();
        keysMaterial->hide();


        percussioneType->hide();
        percussioneMaterial->hide();
        isTuned->hide();
        isMetalSnare->hide();
        fiatoType->hide();
        mouthPieceType->hide();
        fiatoMaterial->hide();

        break;
    }


}
*/

/*
void insertView::slotDisableCorda(int index) const
{

    switch (index) {
    case 1://Guitar

        guitarType->show();
        model->show();

        bassType->hide();
        isFretless->hide();

        pianoShape->hide();
        keysMaterial->hide();

        break;

    case 2://Bass

        guitarType->hide();
        model->hide();

        bassType->show();
        isFretless->show();

        pianoShape->hide();
        keysMaterial->hide();


        break;

    case 3://Piano

        guitarType->hide();
        model->hide();

        bassType->hide();
        isFretless->hide();

        pianoShape->show();
        keysMaterial->show();

        break;


    default:

        guitarType->hide();
        model->hide();

        bassType->hide();
        isFretless->hide();

        pianoShape->hide();
        keysMaterial->hide();


        break;
    }
}

*/


    QComboBox* insertView::getInstrumentType() const {
        return instrumentType;
    }

    QLineEdit* insertView::getPrice() const {
        return price;
    }

    QLineEdit* insertView::getDescription() const {
        return description;
    }

    QLineEdit* insertView::getBrand() const {
        return brand;
    }

    QComboBox* insertView::getInstrumentTune() const {
        return instrumentTune;
    }

    QCheckBox* insertView::getIsSecondHand() const {
        return isSecondHand;
    }

    //Arco
    QComboBox* insertView::getArcoType() const {
        return arcoType;
    }
    QCheckBox* insertView::getIsLutherie() const {
        return isLutherie;
    }

    //Corda
    QComboBox* insertView::getCordaType() const {
        return cordaType;
    }

    QLineEdit* insertView::getStringsNumber() const {
        return stringsNumber;
    }

    //Chitarra
    QComboBox* insertView::getGuitarType() const {
        return guitarType;
    }

    QLineEdit* insertView::getModel() const {
        return model;
    }

    //Basso
    QComboBox* insertView::getBassType() const {
        return bassType;
    }

    QCheckBox* insertView::getIsFretless() const {
        return isFretless;
    }

    //Pianoforte
    QComboBox* insertView::getPianoShape() const {
        return pianoShape;
    }

    QComboBox* insertView::getKeysMaterial() const {
        return keysMaterial;
    }

    //Percussione
    QComboBox* insertView::getPercussioneType() const {
        return percussioneType;
    }

    QComboBox* insertView::getPercussioneMaterial() const {
        return percussioneMaterial;
    }

    QCheckBox* insertView::getIsTuned() const {
        return isTuned;
    }

    //Kit Batteria
    QCheckBox* insertView::getIsMetalSnare() const {
        return isMetalSnare;
    }

    //Fiato
    QComboBox* insertView::getFiatoType() const {
        return fiatoType;
    }

    QComboBox* insertView::getMouthPieceType() const {
        return mouthPieceType;
    }

    QComboBox* insertView::getFiatoMaterial() const {
        return fiatoMaterial;
    }

    QPushButton* insertView::getAddItemButton() const {
        return addItem;
    }

    QPushButton* insertView::getResetFieldsButton() const {
        return resetFields;
    }

    void insertView::showWarningDialog(QWidget* p, QString what) const {

        QString str= "Devi inserire il campo: ";
        str.append(what);
        QMessageBox::warning(p, "Attenzione",str);
    }


