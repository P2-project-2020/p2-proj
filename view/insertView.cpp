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
    name(new QLineEdit(this)),
    description(new QLineEdit(this)),
    material(new QLineEdit(this)),
    brand(new QLineEdit(this)),
    productionYear(new QLineEdit(this)),
    basePrice(new QLineEdit(this)),
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
  hasSticks(new QCheckBox(this)),
  isTuned(new QCheckBox(this)),
  isMetalSnare(new QCheckBox(this)),

  fiatoType(new QComboBox(this)),
  mouthPieceType(new QComboBox(this)),

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

    name->setPlaceholderText("Nome strumento");


  //da sostituire con QTextEdit
  description->setPlaceholderText("Descrizione strumento");
  material->setPlaceholderText("Materiale strumento");
  brand->setPlaceholderText("Marca strumento");
  productionYear->setPlaceholderText("Anno di produzione strumento");
  basePrice->setPlaceholderText("Prezzo strumento");
  basePrice->setValidator( new QDoubleValidator(0.01,100000,2,this));
  isSecondHand->setText("Strumento di seconda mano");



  generalForm->addWidget(instrumentType);
  generalForm->addWidget(name);
  generalForm->addWidget(description);
  generalForm->addWidget(material);
  generalForm->addWidget(brand);
  generalForm->addWidget(productionYear);
  generalForm->addWidget(basePrice);
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
  hasSticks->setText("Bacchette incluse");
  isTuned->setText("Strumento con tonalità");


  percussioneForm->addWidget(percussioneType);
  percussioneForm->addWidget(hasSticks);
  percussioneForm->addWidget(isTuned);

  specificForm->addItem(percussioneForm);

  QHBoxLayout *kitBatteriaForm = new QHBoxLayout;
  kitBatteriaForm->setSpacing(12);

  isMetalSnare->setText("Rullante");

  kitBatteriaForm->addWidget(isMetalSnare);

  specificForm->addItem(kitBatteriaForm);

  QHBoxLayout *fiatoForm = new QHBoxLayout;
  fiatoForm->setSpacing(12);

  fiatoType->addItem("Scegli il tipo di strumento a fiato");
  fiatoType->addItem("Sassofono");
  fiatoType->addItem("Tromba");
  mouthPieceType->addItem("Scegli il tipo di bocchino");
  mouthPieceType->addItem("Legno");
  mouthPieceType->addItem("Ottone");

  fiatoForm->addWidget(fiatoType);
  fiatoForm->addWidget(mouthPieceType);

  specificForm->addItem(fiatoForm);

  //QHBoxLayout* instrumentForm = new QHBoxLayout;
  //instrumentForm->setSpacing(20);

  //instrumentForm->addItem(generalForm);
  //instrumentForm->addItem(specificForm);

  //form->addItem(instrumentForm);

  form->addItem(generalForm);
  form->addItem(specificForm);

  /*
  QGroupBox* generalBox = new QGroupBox("General info");
  QGroupBox* specificBox = new QGroupBox("Specific info");

  generalBox->setLayout(generalForm);
  specificBox->setLayout(specificForm);
   */




  QHBoxLayout* buttonsLayout= new QHBoxLayout;
  buttonsLayout->addWidget(addItem);
  buttonsLayout->addWidget(resetFields);
  buttonsLayout->setSpacing(5);
  form->addItem(buttonsLayout);

   slotDisableElements(0);

    //this->setFixedSize(600,600);
    //window->viewIns->setSizeConstraint( QLayout::SetFixedSize );

    connect(instrumentType,SIGNAL(activated(int)),this,SLOT(slotDisableElements(int)));
    //connect(cordaType,SIGNAL(activated(int)),instrumentForm,SLOT(slotDisableString(int)));
    connect(resetFields,SIGNAL(clicked()),this,SLOT(slotReset()));
    connect(this,SIGNAL(rejected()),this,SLOT(slotRestart()));


}




void insertView::slotRestart(){

    instrumentType->show();
    name->hide();
    description->hide();
    material->hide();
    productionYear->hide();
    brand->hide();
    basePrice->hide();
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
    hasSticks->hide();
    isTuned->hide();
    isMetalSnare->hide();
    fiatoType->hide();
    mouthPieceType->hide();

    slotReset();

    /*
    instrumentType->setEnabled(true);
    name->setEnabled(false);
    description->setEnabled(false);
    material->setEnabled(false);
    productionYear->setEnabled(false);
    brand->setEnabled(false);
    basePrice->setEnabled(false);
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
    hasSticks->setEnabled(false);
    isTuned->setEnabled(false);
    isMetalSnare->setEnabled(false);
    fiatoType->setEnabled(false);
    mouthPieceType->setEnabled(false);
    */

}

    void insertView::slotReset(){

    instrumentType->setCurrentIndex(0);
    name->setText("");

    description->setText("");
    material->setText("");
    brand->setText("");
    productionYear->setText("");
    basePrice->setText("");
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
    hasSticks->setChecked(false);
    isTuned->setChecked(false);
//Pianoforte
//Vedi Corda<-Pianoforte!
//Kit Batteria
    isMetalSnare->setChecked(false);

//*******************************************
//Fiato
    fiatoType->setCurrentIndex(0);
    mouthPieceType->setCurrentIndex(0);

}

void insertView::slotDisableElements(int index) const
{

    switch (index) {
    case 1://Arco
        instrumentType->show();
        name->show();
        description->show();
        material->show();
        productionYear->show();
        brand->show();
        basePrice->show();
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
        hasSticks->hide();
        isTuned->hide();

       isMetalSnare->hide();

        fiatoType->hide();
        mouthPieceType->hide();


        break;
    case 2://Corda
        instrumentType->show();
        name->show();
        description->show();
        material->show();
        productionYear->show();
        brand->show();
        basePrice->show();
        isSecondHand->show();

        arcoType->hide();
        isLutherie->hide();

        cordaType->show();
        stringsNumber->show();
        //inserire switch case per cordaType
        guitarType->hide();
        model->hide();

        bassType->hide();
        isFretless->hide();

        pianoShape->hide();
        keysMaterial->hide();


        percussioneType->hide();
        hasSticks->hide();
        isTuned->hide();

       isMetalSnare->hide();

        fiatoType->hide();
        mouthPieceType->hide();

        break;

    case 3://Percussione
        instrumentType->show();
        name->show();
        description->show();
        material->show();
        productionYear->show();
        brand->show();
        basePrice->show();
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
        hasSticks->show();
        isTuned->show();

       isMetalSnare->hide();

        fiatoType->hide();
        mouthPieceType->hide();
        break;

    case 4://Percussione
        instrumentType->show();
        name->show();
        description->show();
        material->show();
        productionYear->show();
        brand->show();
        basePrice->show();
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
        hasSticks->hide();
        isTuned->hide();

       isMetalSnare->hide();

        fiatoType->show();
        mouthPieceType->show();

        break;

    default:

        instrumentType->show();
        name->hide();
        description->hide();
        material->hide();
        productionYear->hide();
        brand->hide();
        basePrice->hide();
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
        hasSticks->hide();
        isTuned->hide();

       isMetalSnare->hide();

        fiatoType->hide();
        mouthPieceType->hide();

        break;
    }
}
/*
void insertView::slotDisableString(int index) const
{
    switch (index) {
    case 1://Guitar

        instrumentType->show();
        name->show();
        description->show();
        material->show();
        productionYear->show();
        brand->show();
        basePrice->show();
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
        hasSticks->hide();
        isTuned->hide();

       isMetalSnare->hide();

        fiatoType->hide();
        mouthPieceType->hide();
        break;
    case 2://Bass

        instrumentType->show();
        name->show();
        description->show();
        material->show();
        productionYear->show();
        brand->show();
        basePrice->show();
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
        hasSticks->hide();
        isTuned->hide();

       isMetalSnare->hide();

        fiatoType->hide();
        mouthPieceType->hide();

        break;

    case 3://Piano
        instrumentType->show();
        name->show();
        description->show();
        material->show();
        productionYear->show();
        brand->show();
        basePrice->show();
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
        hasSticks->hide();
        isTuned->hide();

       isMetalSnare->hide();

        fiatoType->hide();
        mouthPieceType->hide();
        break;


    default:

        instrumentType->show();
        name->show();
        description->show();
        material->show();
        productionYear->show();
        brand->show();
        basePrice->show();
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
        hasSticks->hide();
        isTuned->hide();

       isMetalSnare->hide();

        fiatoType->hide();
        mouthPieceType->hide();

        break;
    }
}
*/


    QComboBox* insertView::getInstrumentType() const {
        return instrumentType;
    }

    QLineEdit* insertView::getName() const {
        return name;
    }

    QLineEdit* insertView::getDescription() const {
        return description;
    }

    QLineEdit* insertView::getMaterial() const {
        return material;
    }

    QLineEdit* insertView::getBrand() const {
        return brand;
    }

    QLineEdit* insertView::getProductionYear() const {
        return productionYear;
    }

    QLineEdit* insertView::getBasePrice() const {
        return basePrice;
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

    QCheckBox* insertView::getHasSticks() const {
        return hasSticks;
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


