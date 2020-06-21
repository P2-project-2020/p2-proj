#include "insertView.h"

#include <QString>
#include <iostream>
#include <QMessageBox>
#include <QBuffer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

#include "model/hierarchy/fiato.h"
#include "model/hierarchy/pianoforte.h"
#include "model/hierarchy/kitBatteria.h"
#include "model/hierarchy/strumento.h"


insertView::insertView(QWidget* p, Strumento* strumento):
    QDialog (p),
    instrumentPointer(strumento),
    instrumentType(new QComboBox(this)),
    title(new QLabel(this)),
    generalInfo(new QGroupBox(this)),
    price(new QLineEdit(this)),
    description(new QTextEdit(this)),
    brand(new QLineEdit(this)),
    model(new QLineEdit(this)),
    instrumentTune(new QComboBox(this)),
    isSecondHand(new QCheckBox(this)),
    quantity(new QSpinBox(this)),

    specificInfo(new QGroupBox(this)),
    arcoType(new QComboBox(this)),
    isLutherie(new QCheckBox(this)),
    cordaType(new QComboBox(this)),
    stringsNumber(new QLineEdit(this)),
    guitarType(new QComboBox(this)),
    bassType(new QComboBox(this)),
    isFretless(new QCheckBox(this)),

    pianoShape(new QComboBox(this)),
    keysMaterial(new QComboBox(this)),

    percussioneType(new QComboBox(this)),
    percussioneMaterial(new QComboBox(this)),
    isMetalSnare(new QCheckBox(this)),

    fiatoType(new QComboBox(this)),
    fiatoMaterial(new QComboBox(this)),

    addItem(new QPushButton("Inserisci",this)),
    editItem(new QPushButton("Modifica",this)),
    resetFields(new QPushButton("Reset",this)),

    image(new ImageControlBox(":/images/res/instruments.jpg", this)),
    imgPath("")
{
     // In pratica il nuovo layout visualizzato è insert_form, che ha
     // in QHBoxLayout ImageControlBox e il form come era prima
     QHBoxLayout *insert_form = new QHBoxLayout(this);
     QVBoxLayout *form = new QVBoxLayout;
     form->setSpacing(5);
     editItem->hide();
     editItem->setEnabled(false);

     title->setText("");
     form->addWidget(title);


    instrumentType->addItem("Scegli il tipo di strumento");
    instrumentType->addItem("Arco");
    instrumentType->addItem("Corda");
    instrumentType->addItem("Percussione");
    instrumentType->addItem("Fiato");
    form->addWidget(instrumentType);

    QVBoxLayout *generalForm= new QVBoxLayout;
    generalForm->setSpacing(5);

    generalInfo->setTitle("Informazioni generali");
    price->setPlaceholderText("Prezzo strumento");
    price->setToolTip("Prezzo");
    price->setValidator( new QDoubleValidator(0.01,100000,2,this));
    description->setPlaceholderText("Descrizione strumento");
    description->setToolTip("Descrizione");
    description->setLineWidth(200);
    brand->setPlaceholderText("Marca strumento");
    brand->setToolTip("Marca");
    model->setPlaceholderText("Modello strumento");
    model->setToolTip("Modello");
    instrumentTune->addItem("Scegli il tipo di tonalità");
    instrumentTune->setToolTip("Tonalità");
    for(auto& tune : Strumento::Tunes)
	 instrumentTune->addItem(QString::fromStdString(tune.second));
    
    isSecondHand->setText("Strumento di seconda mano");
    isSecondHand->setToolTip("Condizione");
    QFormLayout * quantityForm = new QFormLayout;
    quantityForm->setSpacing(5);
    quantity->setRange(1,100000);
    quantity->setValue(1);
    quantityForm->addRow(tr("Quantità"), quantity);

    generalForm->addWidget(price);
    generalForm->addWidget(description);
    generalForm->addWidget(brand);
    generalForm->addWidget(model);
    generalForm->addWidget(instrumentTune);
    generalForm->addWidget(isSecondHand);
    generalForm->addItem(quantityForm);
    generalInfo->setLayout(generalForm);

    QVBoxLayout* specificForm = new QVBoxLayout;
    specificForm->setSpacing(5);

    specificInfo->setTitle("Dettagli strumento");

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
    stringsNumber->setValidator( new QIntValidator(1,100000,this));
    stringForm->addWidget(cordaType);
    stringForm->addWidget(stringsNumber);

    specificForm->addItem(stringForm);

    guitarType->addItem("Scegli il tipo di chitarra");
    guitarType->addItem("Elettrica");
    guitarType->addItem("Acustica");
    guitarType->addItem("Classica");

    specificForm->addWidget(guitarType);

    QHBoxLayout *bassForm = new QHBoxLayout;
    bassForm->setSpacing(12);

    bassType->addItem("Scegli il tipo di basso");
    bassType->addItem("Elettrico");
    bassType->addItem("Acustico");
    isFretless->setText("Basso senza tasti");

    bassForm->addWidget(bassType);
    bassForm->addWidget(isFretless);

    specificForm->addItem(bassForm);

    percussioneType->addItem("Scegli il tipo di strumento a percussione");
    percussioneType->addItem("Pianoforte");
    percussioneType->addItem("Kit Batteria"); 

    specificForm->addWidget(percussioneType);

    QHBoxLayout *pianoForm = new QHBoxLayout;
    pianoForm->setSpacing(12);

    pianoShape->addItem("Scegli il tipo di pianoforte");
    pianoShape->addItem("Coda");
    pianoShape->addItem("Muro");
    keysMaterial->addItem("Scegli il materiale dei tasti");
    for(auto& material : Pianoforte::keys)
	 keysMaterial->addItem(QString::fromStdString(material));

    pianoForm->addWidget(pianoShape);
    pianoForm->addWidget(keysMaterial);

    specificForm->addItem(pianoForm);

    QHBoxLayout *percussioneForm = new QHBoxLayout;
    percussioneForm->setSpacing(12);

    percussioneMaterial->addItem("Scegli il tipo di materiale");
    for(auto& material : KitBatteria::materials)
	 percussioneMaterial->addItem(QString::fromStdString(material));

    isMetalSnare->setText("Rullante");

    percussioneForm->addWidget(percussioneMaterial);
    percussioneForm->addWidget(isMetalSnare);

    specificForm->addItem(percussioneForm);


    QHBoxLayout *fiatoForm = new QHBoxLayout;
    fiatoForm->setSpacing(12);

    fiatoType->addItem("Scegli il tipo di strumento a fiato");
    fiatoType->addItem("Tromba");
    fiatoType->addItem("Sassofono");
    fiatoMaterial->addItem("Scegli il tipo di materiale");
    for(auto& material : Fiato::materials)
	 fiatoMaterial->addItem(QString::fromStdString(material));    

    fiatoForm->addWidget(fiatoType);
    fiatoForm->addWidget(fiatoMaterial);

    specificForm->addItem(fiatoForm);

    specificInfo->setLayout(specificForm);

    form->addWidget(generalInfo);
    form->addWidget(specificInfo);
      

    QHBoxLayout* buttonsLayout= new QHBoxLayout;
    buttonsLayout->addWidget(addItem);
    buttonsLayout->addWidget(resetFields);
    buttonsLayout->addWidget(editItem);
    buttonsLayout->setSpacing(5);
    form->addItem(buttonsLayout);

    insert_form->setSizeConstraint(QLayout::SetFixedSize);

    insert_form->addWidget(image);
    insert_form->addItem(form);

    slotDisableElements(0);
    
    setStrumento(strumento);
    connect(instrumentType,SIGNAL(activated(int)),this,SLOT(slotDisableElements(int)));
    connect(arcoType, SIGNAL(activated(int)), this, SLOT(slotDisableArco(int)));
    connect(cordaType, SIGNAL(activated(int)), this, SLOT(slotDisableCorda(int)));
    connect(percussioneType, SIGNAL(activated(int)), this, SLOT(slotDisablePercussione(int)));
    connect(image, SIGNAL(signal_setImage(const QString&)), this, SLOT(slotSetImage(const QString&)));
    connect(resetFields,SIGNAL(clicked()),this,SLOT(slotReset()));
    connect(this,SIGNAL(rejected()),this,SLOT(slotRestart()));

}






void insertView::slotRestart(){

    instrumentType->setCurrentIndex(0);
    instrumentType->show();

    image->hide();
    title->hide();

    generalInfo->hide();
    specificInfo->hide();



    slotReset();

    instrumentType->setEnabled(true);
    image->setEnabled(false);
    title->setEnabled(false);
    price->setEnabled(false);
    description->setEnabled(false);
    brand->setEnabled(false);
    model->setEnabled(false);
    instrumentTune->setEnabled(false);
    isSecondHand->setEnabled(false);
    quantity->setEnabled(false);
    arcoType->setEnabled(false);
    isLutherie->setEnabled(false);
    cordaType->setEnabled(false);
    stringsNumber->setEnabled(false);
    guitarType->setEnabled(false);
    bassType->setEnabled(false);
    isFretless->setEnabled(false);
    pianoShape->setEnabled(false);
    keysMaterial->setEnabled(false);
    percussioneType->setEnabled(false);
    percussioneMaterial->setEnabled(false);
    isMetalSnare->setEnabled(false);
    fiatoType->setEnabled(false);
    fiatoMaterial->setEnabled(false);


}

    void insertView::slotReset(){


    price->setText("");
    description->setText("");
    brand->setText("");
    model->setText("");
    instrumentTune->setCurrentIndex(0);
    isSecondHand->setChecked(false);
    quantity->setValue(1);

    arcoType->setCurrentIndex(0);
    isLutherie->setChecked(false);
//Violino
//Viola

//*******************************************
//Corda
    //cordaType->setCurrentIndex(0);
    stringsNumber->setText("");
//Chitarra
    guitarType->setCurrentIndex(0);
//Basso
    bassType->setCurrentIndex(0);
    isFretless->setChecked(false);
//Pianoforte
    pianoShape->setCurrentIndex(0);
    keysMaterial->setCurrentIndex(0);


//*******************************************
//Percussione
    percussioneMaterial->setCurrentIndex(0);
//Pianoforte
//Vedi Corda<-Pianoforte!
//Kit Batteria
    isMetalSnare->setChecked(false);

//*******************************************
//Fiato
    fiatoMaterial->setCurrentIndex(0);

}

void insertView::slotDisableElements(int index) const
{

    switch (index) {
    case 1://Arco

        instrumentType->show();
        title->hide();
        generalInfo->show();
        specificInfo->show();
	image->show();

        price->show();
        description->show();
        instrumentTune->hide();
        brand->show();
        model->show();

        isSecondHand->show();
        quantity->show();
        arcoType->show();
        isLutherie->show();
        cordaType->hide();
        stringsNumber->hide();

        guitarType->hide();
        bassType->hide();
        isFretless->hide();
        pianoShape->hide();
        keysMaterial->hide();

        percussioneType->hide();
        percussioneMaterial->hide();

        isMetalSnare->hide();

        fiatoType->hide();
        fiatoMaterial->hide();


        instrumentType->setEnabled(true);
        title->setEnabled(false);
        image->setEnabled(true);
        price->setEnabled(true);
        description->setEnabled(true);
        brand->setEnabled(true);
        model->setEnabled(true);
        isSecondHand->setEnabled(true);
        quantity->setEnabled(true);
        arcoType->setEnabled(true);
        isLutherie->setEnabled(true);
        cordaType->setEnabled(false);
        stringsNumber->setEnabled(false);
        guitarType->setEnabled(false);
        bassType->setEnabled(false);
        isFretless->setEnabled(false);
        pianoShape->setEnabled(false);
        keysMaterial->setEnabled(false);
        percussioneType->setEnabled(false);
        percussioneMaterial->setEnabled(false);
        isMetalSnare->setEnabled(false);
        fiatoType->setEnabled(false);
        fiatoMaterial->setEnabled(false);

        break;
    case 2://Corda

        slotDisableCorda(0);

        instrumentType->show();
        title->hide();
        generalInfo->show();
        specificInfo->show();
        image->show();

        price->show();
        description->show();
        brand->show();
        model->show();
        instrumentTune->hide();
        isSecondHand->show();
        quantity->show();
        arcoType->hide();
        isLutherie->hide();
        cordaType->show();

        //gestione di cordaType affidata a slotDisableCorda(int)

        percussioneType->hide();
        percussioneMaterial->hide();
        isMetalSnare->hide();
        fiatoType->hide();
        fiatoMaterial->hide();

        instrumentType->setEnabled(true);
        title->setEnabled(false);
        image->setEnabled(true);
        price->setEnabled(true);
        description->setEnabled(true);
        brand->setEnabled(true);
        model->setEnabled(true);
        instrumentTune->setEnabled(false);
        isSecondHand->setEnabled(true);
        quantity->setEnabled(true);
        arcoType->setEnabled(false);
        isLutherie->setEnabled(false);
        cordaType->setEnabled(true);
        percussioneType->setEnabled(false);
        percussioneMaterial->setEnabled(false);
        isMetalSnare->setEnabled(false);
        fiatoType->setEnabled(false);
        fiatoMaterial->setEnabled(false);


        break;

    case 3://Percussione

        slotDisablePercussione(0);

        instrumentType->show();
        title->hide();
        generalInfo->show();
        specificInfo->show();
        image->show();

        price->show();
        description->show();
        brand->show();
        model->show();
        instrumentTune->hide();
        isSecondHand->show();
        quantity->show();
        arcoType->hide();
        isLutherie->hide();
        cordaType->hide();
        stringsNumber->hide();

        guitarType->hide();
        bassType->hide();
        isFretless->hide();

        percussioneType->show();

        //gestione percussioneType affidata a slotDisablePercussione

        fiatoType->hide();
        fiatoMaterial->hide();

        instrumentType->setEnabled(true);
        title->setEnabled(false);
        image->setEnabled(true);
        price->setEnabled(true);
        description->setEnabled(true);
        brand->setEnabled(true);
        model->setEnabled(true);
        instrumentTune->setEnabled(false);
        isSecondHand->setEnabled(true);
        quantity->setEnabled(true);
        arcoType->setEnabled(false);
        isLutherie->setEnabled(false);
        cordaType->setEnabled(false);
        stringsNumber->setEnabled(false);

        guitarType->setEnabled(false);
        bassType->setEnabled(false);
        isFretless->setEnabled(false);

        percussioneType->setEnabled(true);

        fiatoType->setEnabled(false);
        fiatoMaterial->setEnabled(false);

        break;

    case 4://Fiato

        instrumentType->show();
        title->hide();
        generalInfo->show();
        specificInfo->show();
        image->show();

        price->show();
        description->show();
        brand->show();
        model->show();
        instrumentTune->show();
        isSecondHand->show();
        quantity->show();
        arcoType->hide();
        isLutherie->hide();
        cordaType->hide();
        stringsNumber->hide();

        guitarType->hide();
        bassType->hide();
        isFretless->hide();
        pianoShape->hide();
        keysMaterial->hide();

        percussioneType->hide();
        percussioneMaterial->hide();

        isMetalSnare->hide();

        fiatoType->show();
        fiatoMaterial->show();

        instrumentType->setEnabled(true);
        title->setEnabled(false);
        image->setEnabled(true);
        price->setEnabled(true);
        description->setEnabled(true);
        brand->setEnabled(true);
        model->setEnabled(true);
        instrumentTune->setEnabled(true);
        isSecondHand->setEnabled(true);
        quantity->setEnabled(true);
        arcoType->setEnabled(false);
        isLutherie->setEnabled(false);
        cordaType->setEnabled(false);
        stringsNumber->setEnabled(false);


        guitarType->setEnabled(false);
        bassType->setEnabled(false);
        isFretless->setEnabled(false);  
        pianoShape->setEnabled(false);
        keysMaterial->setEnabled(false);

        percussioneType->setEnabled(false);
        percussioneMaterial->setEnabled(false);

        isMetalSnare->setEnabled(false);

        fiatoType->setEnabled(true);
        fiatoMaterial->setEnabled(true);


        break;

    default:
        instrumentType->setCurrentIndex(0);

        instrumentType->show();
         title->hide();
        generalInfo->hide();
        specificInfo->hide();
        image->hide();

        instrumentType->setEnabled(true);
        title->setEnabled(false);
        price->setEnabled(false);
        description->setEnabled(false);
        brand->setEnabled(false);
        model->setEnabled(false);
        instrumentTune->setEnabled(false);
        isSecondHand->setEnabled(false);
        quantity->setEnabled(false);
        arcoType->setEnabled(false);
        isLutherie->setEnabled(false);
        cordaType->setEnabled(false);
        stringsNumber->setEnabled(false);
        guitarType->setEnabled(false);
        bassType->setEnabled(false);
        isFretless->setEnabled(false);
        pianoShape->setEnabled(false);
        keysMaterial->setEnabled(false);
        percussioneType->setEnabled(false);
        percussioneMaterial->setEnabled(false);
        isMetalSnare->setEnabled(false);
        fiatoType->setEnabled(false);
        fiatoMaterial->setEnabled(false);
        image->setEnabled(false);
    }
}

void insertView::slotDisableArco(int index) const {
    switch (index) {
    case 1://Violino
        instrumentTune->hide();
        instrumentTune->setEnabled(false);
         break;
    case 2://Viola
        instrumentTune->show();
        instrumentTune->setEnabled(true);
         break;
    default:
         cordaType->setCurrentIndex(0);
         instrumentTune->hide();
         instrumentTune->setEnabled(false);
          break;
    }

}


void insertView::setStrumento(Strumento* s, bool editable){
    if(s){
        instrumentPointer = s;
     title->setText(QString::fromStdString(s->className()));
     title->setStyleSheet("font-weight: bold");
     title->show();
     instrumentType->hide();
     instrumentType->setEnabled(false);
     arcoType->setEnabled(false);
     cordaType->setEnabled(false);
     guitarType->setEnabled(false);
     bassType->setEnabled(false);

     addItem->hide();
     addItem->setEnabled(false);
     editItem->show();
     editItem->setEnabled(editable);
     resetFields->setEnabled(editable);

     image->show();
     image->setEnabled(editable);
     if(s->getImgPath() != "")
          image->setImage(QString::fromStdString(s->getImgPath()));

     title->setEnabled(editable);
     price->setEnabled(editable);
     description->setEnabled(editable);
     brand->setEnabled(editable);
     model->setEnabled(editable);
     isSecondHand->setEnabled(editable);
     quantity->setEnabled(editable);

     generalInfo->show();
     generalInfo->setEnabled(editable);

     instrumentTune->show();
     instrumentTune->setEnabled(editable);

     price->setText(QString::number(s->getPrice()));
     description->setText(QString::fromStdString(s->getDescription()));
     brand->setText(QString::fromStdString(s->getBrand()));
     model->setText(QString::fromStdString(s->getModel()));
     instrumentTune->setCurrentText(QString::fromStdString(Strumento::Tunes.at(s->tune())));
     isSecondHand->setChecked(s->isUsed());
     quantity->setValue(s->getQuantity());
    }
}//setStrumento


void insertView::slotDisableCorda(int index) const
{

    switch (index) {
    case 1://Guitar
        stringsNumber->show();
        guitarType->show();

        bassType->hide();
        isFretless->hide();

        pianoShape->hide();
        keysMaterial->hide();

        stringsNumber->setEnabled(true);
        guitarType->setEnabled(true);

        bassType->setEnabled(false);
        isFretless->setEnabled(false);
        pianoShape->setEnabled(false);
        keysMaterial->setEnabled(false);

        break;

    case 2://Bass
        stringsNumber->show();
        guitarType->hide();

        bassType->show();
        isFretless->show();

        pianoShape->hide();
        keysMaterial->hide();

        stringsNumber->setEnabled(true);
        guitarType->setEnabled(false);

        bassType->setEnabled(true);
        isFretless->setEnabled(true);

        pianoShape->setEnabled(false);
        keysMaterial->setEnabled(false);

        break;

    case 3://Piano
        stringsNumber->hide();
        guitarType->hide();

        bassType->hide();
        isFretless->hide();

        pianoShape->show();
        keysMaterial->show();

        stringsNumber->setEnabled(false);
        guitarType->setEnabled(false);
        bassType->setEnabled(false);
        isFretless->setEnabled(false);

        pianoShape->setEnabled(true);
        keysMaterial->setEnabled(true);

        break;


    default:

        cordaType->setCurrentIndex(0);
        stringsNumber->hide();
        guitarType->hide();

        bassType->hide();
        isFretless->hide();


        pianoShape->hide();
        keysMaterial->hide();

        stringsNumber->setEnabled(false);
        guitarType->setEnabled(false);
        bassType->setEnabled(false);
        isFretless->setEnabled(false);
        pianoShape->setEnabled(false);
        keysMaterial->setEnabled(false);


        break;
    }
}


void insertView::slotDisablePercussione(int index) const
{

    switch (index) {
    case 1://Piano

        pianoShape->show();
        keysMaterial->show();
        percussioneMaterial->hide();
        isMetalSnare->hide();

        pianoShape->setEnabled(true);
        keysMaterial->setEnabled(true);
        percussioneMaterial->setEnabled(false);
        isMetalSnare->setEnabled(false);

        break;

    case 2://Kit Batteria

        pianoShape->hide();
        keysMaterial->hide();
        percussioneMaterial->show();
        isMetalSnare->show();

        pianoShape->setEnabled(false);
        keysMaterial->setEnabled(false);
        percussioneMaterial->setEnabled(true);
        isMetalSnare->setEnabled(true);


        break;


    default:
        percussioneType->setCurrentIndex(0);
        pianoShape->hide();
        keysMaterial->hide();
        percussioneMaterial->hide();
        isMetalSnare->hide();

        pianoShape->setEnabled(false);
        keysMaterial->setEnabled(false);
        percussioneMaterial->setEnabled(false);
        isMetalSnare->setEnabled(false);

        break;
    }
}

void insertView::slotSetImage(const QString& new_path){
     imgPath = new_path;
}

    QComboBox* insertView::getInstrumentType() const {
        return instrumentType;
    }

    QLineEdit* insertView::getPrice() const {
        return price;
    }

    QTextEdit* insertView::getDescription() const {
        return description;
    }

    QLineEdit* insertView::getBrand() const {
        return brand;
    }

    QLineEdit* insertView::getModel() const {
        return model;
    }


    QComboBox* insertView::getInstrumentTune() const {
        return instrumentTune;
    }

    QCheckBox* insertView::getIsSecondHand() const {
        return isSecondHand;
    }

    QSpinBox* insertView::getQuantity() const {
        return quantity;
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

    //Kit Batteria
    QCheckBox* insertView::getIsMetalSnare() const {
        return isMetalSnare;
    }

    //Fiato
    QComboBox* insertView::getFiatoType() const {
        return fiatoType;
    }


    QComboBox* insertView::getFiatoMaterial() const {
        return fiatoMaterial;
    }

    QPushButton* insertView::getAddItemButton() const {
        return addItem;
    }

    QPushButton* insertView::getEditItemButton() const {
        return editItem;
    }

    QPushButton* insertView::getResetFieldsButton() const {
        return resetFields;
    }

QString insertView::getImgPath() const {
     return imgPath;
     // ritorna una copia non dovrebbe essere troppo grossa, e viene
     // fatto solo una volta
}

Strumento* insertView::getStrumento() const {
     return instrumentPointer;
     // ritorna una copia non dovrebbe essere troppo grossa, e viene
     // fatto solo una volta
}

    void insertView::showWarningDialog(QWidget* p, QString what) const {

        QString str= "Devi inserire il campo: ";
        str.append(what);
        QMessageBox::warning(p, "Attenzione",str);
    }


