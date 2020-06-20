
#include "controller.h"
#include <QHBoxLayout>
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QGroupBox>
#include <QSpinBox>

#include <QJsonDocument>
#include <QJsonObject>
#include <QAction>
#include <QPrinter>
#include <QPainter>

#include <QDebug>

#include "model/hierarchy/strumento.h"
#include "model/hierarchy/violino.h"
#include "model/hierarchy/viola.h"
#include "model/hierarchy/chitarra.h"
#include "model/hierarchy/basso.h"
#include "model/hierarchy/kitBatteria.h"
#include "model/hierarchy/pianoforte.h"
#include "model/hierarchy/tromba.h"
#include "model/hierarchy/sax.h"



/*
#include "GERARCHIA IN BASE ALLE NECESSITÀ
*/


Controller::Controller(Model* m,QWidget *parent) :
    QWidget (parent),
    menuBar(new Menu(this)),
    core(m),
    pagine(new QTabWidget),
    Vmagazzino(new magazzinoView(this,core)),
    Vcarrello(new carrelloView(this,core)),
    mainLayout(new QBoxLayout(QBoxLayout::TopToBottom,this)),
    headerLayout(new QHBoxLayout),
    statusBar(new QHBoxLayout),
    itemCounter(new QLabel(this)),
    saveStatus(new QLabel(this)),
    loadSample(new QPushButton(this))
{

    QGroupBox *logoBox = new QGroupBox();



    setStyleSheet("QTabWidget::pane {border: 0px;}");
    headerLayout->setSpacing(10);
    headerLayout->addWidget(menuBar);
    logoBox->setLayout(headerLayout);


    pagine->insertTab(0,Vmagazzino,QIcon(":/icons/res/factory.png"),"Magazzino");
    pagine->insertTab(1,Vcarrello,QIcon(":/icons/res/cart.png"),"Carrello");
    mainLayout->addWidget(pagine);



    loadSample->setText("Importa il file sample");

    statusBar->addWidget(itemCounter,Qt::AlignRight);
    statusBar->addWidget(saveStatus,Qt::AlignRight);
    statusBar->addWidget(loadSample,Qt::AlignLeft);
    mainLayout->addItem(statusBar);
    setLayout(mainLayout);

    this->layout()->setMenuBar(menuBar);

    slotUpdatePage();

    connect(pagine, SIGNAL(currentChanged(int)), this, SLOT(slotUpdatePage()));
    connect(Vmagazzino->getAddView()->getAddItemButton(),SIGNAL(clicked()), this, SLOT(slotInserisci()));
    connect(Vmagazzino->getDeleteSelected(),SIGNAL(clicked()),this,SLOT(slotDeleteMagazzinoItem()));
    connect(Vmagazzino->getDeleteAll(),SIGNAL(clicked()),this,SLOT(slotResetMagazzino()));
    connect(Vmagazzino->getAddToCart(),SIGNAL(clicked()),this,SLOT(slotAddToCart())); //NEW
    connect(Vcarrello->getDeleteSelected(),SIGNAL(clicked()),this,SLOT(slotDeleteCarrelloItem()));
    connect(Vcarrello->getDeleteAll(),SIGNAL(clicked()),this,SLOT(slotResetCarrello()));
    //salvataggio
    connect(this->loadSample,SIGNAL(clicked()),this,SLOT(slotLoadSample()));
    connect(menuBar->getSave(),SIGNAL(triggered()),this,SLOT(slotSave()));
    //Per sapere che i dati sono stati modificati in real time
    connect(Vmagazzino->getAdapter(),SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(slotDataChanged()));
    connect(Vcarrello->getAdapter(),SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(slotDataChanged()));


}

QString Controller::getCurrentFile() const{ return currentFile;}


/*PDF Print for receipt */
void Controller::slotPrint() {

    QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("/Users/erik/Documents/p2-2020/p2-proj/nonwritable.pdf");
        QPainter painter;
        if (! painter.begin(&printer)) { // failed to open file
            qWarning("failed to open file, is it writable?");
            //return 1;
        }
        painter.drawText(10, 10, "Test");
        if (! printer.newPage()) {
            qWarning("failed in flushing page to disk, disk full?");
            //return 1;
        }
        painter.drawText(10, 10, "Test 2");
        painter.end();

}

/*PDF Print for receipt */

void Controller::slotLoadSample(){

    QJsonDocument doc;
    QByteArray data_json;
    QFile input(":/json/sample.json");
    if(input.open(QIODevice::ReadOnly | QIODevice::Text)){
        data_json = input.readAll();
        doc = doc.fromJson(data_json);
        if(core->unserializeData(doc.object())){
        QMessageBox::information(this,tr("Messaggio"),tr("Documento JSON letto correttamente"));
        core->setDataSaved(true);
        currentFile = "sample_save.json";
        slotUpdatePage();
        }else
            throw inputException("Errore nella lettura del JSON");
    }else
        throw inputException("Errore nell' apertura del file");
}

void Controller::slotSave(){

    /*
   if(core->isDataSaved()){
        QMessageBox::information(this,"Informazione","No Worries! I dati correnti sono gia' salvati");
        return;
    } */
 QString json_filter = "JSON (*.json)";
    bool overr = false;
    QString filename;
   QAction* send = qobject_cast<QAction*>(sender());
   if(send && send->text() == "Salva"){
       //Salvataggio sullo stesso file se la funzione e' chiamata da un certo oggetto
       filename = currentFile;
       overr = true;
}else
       filename=
                QFileDialog::getSaveFileName(
                    this,
                    tr("Scegli dove salvare il file"),
                    QDir::currentPath(),
                    json_filter,&json_filter,QFileDialog::DontUseNativeDialog);

 if(filename.isEmpty())
     QMessageBox::warning(this,"Attenzione!","File scelto non valido");
 else{
     QFile output(filename);
     if(output.open(QIODevice::WriteOnly) | QIODevice::Text){
         QJsonObject saveObj;
        core->serializeData(saveObj); //Delego il salvataggio al Model
        QJsonDocument doc(saveObj);
        output.write(doc.toJson());
        core->setDataSaved(true);
        currentFile = filename;
        slotUpdatePage();

        if(overr)//Salvataggio sullo stesso file
            QMessageBox::information(this,"Successo!","File JSON sovrascritto correttamente");
        else
            QMessageBox::information(this,"Successo!","File JSON salvato correttamente");
     }else//Errore nella lettura del file di salvataggio
         QMessageBox::critical(this,"Errore!","Errore nel salvataggio del file scelto");

}

}//slotSave

void Controller::slotLoad(){

    if(core->getMagazzinoSize() || core->getCarrelloSize()){
        QMessageBox::StandardButton reply= QMessageBox::question(this,"Attenzione!","Cosi' facendo sovrascriverai i dati presenti, vuoi continuare?",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::No)
            return;
//Elimino i dati presenti prima di continuare
        slotResetTables();
    }

    try{
    QString json_filter = "JSON, (*.json)";
        QString filename=
                QFileDialog::getOpenFileName(
                    this,
                    tr("Scegli il file da aprire"),
                    QDir::currentPath(),
                    json_filter,&json_filter,QFileDialog::DontUseNativeDialog);

    if(filename.isEmpty())
        throw inputException("Attenzione! File scelto non valido");
    else{
        QJsonDocument doc;
        QByteArray data_json;
        QFile input(filename);
        if(input.open(QIODevice::ReadOnly | QIODevice::Text)){
            data_json = input.readAll();
            doc = doc.fromJson(data_json);
            if(core->unserializeData(doc.object())){
            QMessageBox::information(this,tr("Messaggio"),tr("Documento JSON letto correttamente"));
            core->setDataSaved(true);
            currentFile = filename;
            slotUpdatePage();
            }else
                throw inputException("Errore nella lettura del JSON");
        }else
            throw inputException("Errore nell' apertura del file");


        }//filename
    }catch(inputException exc){QMessageBox::warning(this, "Error",exc.getErrore());}

}//slotLoadData


void Controller::slotInserisci(){

    insertView *insert = Vmagazzino->getAddView();
    Strumento* toPush = nullptr;

    try {

        int type= insert->getInstrumentType()->currentIndex();

        double price = insert->getPrice()->text().toDouble();
        std::string description = insert->getDescription()->text().toStdString();
        std::string brand = insert->getBrand()->text().toStdString();
        std::string model = insert->getModel()->text().toStdString();
        std::string instrumentTune = insert->getInstrumentTune()->currentText().toStdString();
        bool isSecondHand = insert->getIsSecondHand()->isChecked();
        unsigned int quantity = insert->getQuantity()->text().toUInt();
	std::string path = (insert->getImgPath()).toStdString();

        if(type) {

            if(!price)
                throw inputException("Devi prima inserire il prezzo!");
            if(description == "")
                throw inputException("Devi prima inserire la descrizione!");
            if(brand == "")
                throw inputException("Devi prima inserire la marca!");
            if(model == "")
                throw inputException("Devi prima inserire il modello!");

            //isSecondHand false di default
            //quantity uguale a 1 di default

        }


        switch (type) {

        //Arco
        case 1: {

            int arcType = insert->getArcoType()->currentIndex();

            switch(arcType) {
            case 1: //Violino
		 toPush = new Violino(price, brand, model, description, isSecondHand, quantity, path);
                break;
            case 2: { //Viola
                if(instrumentTune == "Scegli il tipo di tonalità")
                       throw inputException("Devi prima inserire la tonalità!");
                toPush = new Viola(price, brand, model, description,Strumento::findTune(instrumentTune), isSecondHand, quantity, path);
            }
                break;
            default:
                  throw inputException("Devi prima scegliere il tipo di strumento ad arco che vuoi inserire!");

                break;
            }
        }

            break;
        case 2: { //Corda
            int stringType = insert->getCordaType()->currentIndex();
            int stringsNumber = insert->getStringsNumber()->text().toInt();


            switch(stringType) {


            case 1: { //Chitarra

                std::string guitarType = insert->getGuitarType()->currentText().toStdString();
                std::string guitarModel = insert->getModel()->text().toStdString();

                if(guitarType == "Scegli il tipo di chitarra")
                       throw inputException("Devi prima inserire il tipo di chitarra!");
                if(guitarModel == "")
                       throw inputException("Devi prima inserire il modello di chitarra!");
                if(!stringsNumber)
                       throw inputException("Devi prima inserire il numero di corde!");

                toPush = new Chitarra(Chitarra::findType(guitarType), price, brand, model, description, isSecondHand, stringsNumber, quantity, path);
            }
                break;
            case 2: { //Basso
                std::string bassType = insert->getBassType()->currentText().toStdString();
                bool isFretless = insert->getIsFretless()->isChecked();

                if(bassType == "Scegli il tipo di basso")
                       throw inputException("Devi prima inserire il tipo di basso!");
                if(!stringsNumber)
                       throw inputException("Devi prima inserire il numero di corde!");

                toPush = new Basso(Basso::findType(bassType), price, brand, model, description, isSecondHand, stringsNumber, isFretless, quantity, path);
            }
                break;
            case 3: { //Pianoforte
                std::string pianoShape = insert->getPianoShape()->currentText().toStdString();
                std::string keysMaterial = insert->getKeysMaterial()->currentText().toStdString();

                if(pianoShape == "Scegli il tipo di pianoforte")
                       throw inputException("Devi prima inserire il tipo di pianoforte!");
                if(keysMaterial == "Scegli il materiale dei tasti")
                       throw inputException("Devi prima inserire il materiale dei tasti!");

                toPush = new Pianoforte(Pianoforte::findShape(pianoShape), Pianoforte::findKeys(keysMaterial), price, brand, model, isSecondHand, description, quantity, path);
            }
                break;
            default:
                throw inputException("Devi prima scegliere il tipo di strumento ad corda che vuoi inserire!");

                break;
            }
        }
            break;

        case 3: {
        //Percussione
            int percussionType = insert->getPercussioneType()->currentIndex();
            switch(percussionType) {

            case 1: { //Pianoforte
                std::string pianoShape = insert->getPianoShape()->currentText().toStdString();
                std::string keysMaterial = insert->getKeysMaterial()->currentText().toStdString();

                if(pianoShape == "Scegli il tipo di pianoforte")
                       throw inputException("Devi prima inserire il tipo di pianoforte!");
                if(keysMaterial == "Scegli il materiale dei tasti")
                       throw inputException("Devi prima inserire il materiale dei tasti!");

                toPush = new Pianoforte(Pianoforte::findShape(pianoShape), Pianoforte::findKeys(keysMaterial), price, brand, model, isSecondHand, description, quantity, path);
            }
                break;
            case 2: { // Kit batteria
                std::string percussionMaterial = insert->getPercussioneMaterial()->currentText().toStdString();
                bool isMetalSnare = insert->getIsMetalSnare()->isChecked();

                if(percussionMaterial == "Scegli il tipo di materiale")
                       throw inputException("Devi prima inserire il tipo di materiale!");

                toPush = new KitBatteria(price, brand, model, KitBatteria::findMaterial(percussionMaterial), isMetalSnare, isSecondHand, description, quantity, path);

            }
                break;

            default:
                 throw inputException("Devi prima scegliere il tipo di strumento a percussione che vuoi inserire!");

                break;
            }
        }

            break;

        case 4: { //Fiato
        int fiatoType = insert->getFiatoType()->currentIndex();
        std::string windMaterial = insert->getFiatoMaterial()->currentText().toStdString();

        if(instrumentTune == "Scegli il tipo di tonalità")
               throw inputException("Devi prima inserire la tonalità!");
        if(windMaterial == "Scegli il tipo di materiale")
               throw inputException("Devi prima inserire il tipo di materiale!");

        switch(fiatoType) {

            case 1:  //Tromba
		 toPush = new Tromba(Strumento::findTune(instrumentTune), price, brand, model, Fiato::findMaterial(windMaterial), isSecondHand, description, quantity, path);

                break;
            case 2: //Sax
		 toPush = new Sax(Strumento::findTune(instrumentTune), price, brand, model, Fiato::findMaterial(windMaterial), isSecondHand, quantity, path);

                break;
            default:
                throw inputException("Devi prima scegliere il tipo di strumento ad fiato che vuoi inserire!");
                break;
            }

        }
            break;

        default:
              throw inputException("Devi prima scegliere il tipo di strumento che vuoi inserire!");
        }



        if(toPush!= nullptr){
            core->magazzino_push_end(toPush);
            QMessageBox::information(this,"Successo", "Strumento inserito correttamente");
            core->setDataSaved(false);
            slotUpdatePage();
        }

   } catch (inputException exc ) {
        QMessageBox::warning(this,"Spono",exc.getErrore());
    }
}

void Controller::slotAddToCart() {
    if(!Vmagazzino->getTable()->selectionModel()->hasSelection())
        QMessageBox::warning(this,"Attenzione!","Devi selezionare almeno un elemento!");
    else{
    QModelIndexList selectedIndexes = Vmagazzino->getTable()->selectionModel()->selectedRows();

    QMessageBox::StandardButton confirm
            = QMessageBox::question
            (this, "Conferma aggiunta",
            "Confermi di volere aggiungere al carrello il prodotto selezionato?", QMessageBox::Yes|QMessageBox::No);


if(confirm == QMessageBox::Yes)

    for(auto i = 0; i< selectedIndexes.size();++i) {

        if(!core->magazzinoAt(selectedIndexes[i].row())->getQuantity())
            QMessageBox::warning(this,"Attenzione!","Quantità esaurita, rifornire il magazzino!");

        else {
            bool ok;
            unsigned int quantity = QInputDialog::getInt(this, tr("Seleziona quantità"), tr("Quantità"), 1, 1, core->magazzinoAt(selectedIndexes[i].row())->getQuantity(), 1, &ok);
                    if(ok) {

                        bool aggiornato = false;
                        for(auto it = core->carrello_begin();it!=core->carrello_end(); ++it){
                            Strumento *instrument = *it;
                            int oldQuantity = instrument->getQuantity();
                            int newQuantity = oldQuantity + quantity;
                            if(*(*it) == *(core->magazzinoAt(selectedIndexes[i].row()))){ //Sto inserendo in carrello un oggetto che c'è gia -> incremento quantita
                                instrument->setQuantity(newQuantity);
                                aggiornato = true;
                            }
                        }
                        if(!aggiornato){ //Pusho un nuovo obj
                        core->carrello_push_end(core->magazzinoAt(selectedIndexes[i].row())->clone());
                        core->carrelloAt(core->getCarrelloSize()-1)->setQuantity(quantity);
                        }




                        /* Sottraggo la quantita appena inserita in carrello dal magazzino*/
                            /*if(quantity == core->magazzinoAt(selectedIndexes[i].row())->getQuantity())
                                Vmagazzino->getFilter()->removeRow(QPersistentModelIndex(selectedIndexes[i]).row());
                            else*/
                                core->magazzinoAt(selectedIndexes[i].row())->setQuantity(core->magazzinoAt(selectedIndexes[i].row())->getQuantity() - quantity);


                        }
                    }

                }

            else
    return;

core->setDataSaved(false);

    }

slotUpdatePage();

}

void Controller::slotDeleteMagazzinoItem()
{

    if(!Vmagazzino->getTable()->selectionModel()->hasSelection())
        QMessageBox::warning(this,"Attenzione!","Devi selezionare almeno un elemento!");
    else{
    QModelIndexList selectedIndexes = Vmagazzino->getTable()->selectionModel()->selectedRows();
    QMessageBox::StandardButton confirm
            = QMessageBox::question
            (this, "Conferma rimozione",
            "Confermi di voler rimuovere lo strumento selezionato?", QMessageBox::Yes|QMessageBox::No);

if(confirm == QMessageBox::Yes)
    for(auto i = 0; i< selectedIndexes.size();++i)
            Vmagazzino->getFilter()->removeRow(QPersistentModelIndex(selectedIndexes[i]).row());
else
    return;

core->setDataSaved(false);

    }
slotUpdatePage();
}

void Controller::slotDeleteCarrelloItem()
{

    if(!Vcarrello->getTable()->selectionModel()->hasSelection())
        QMessageBox::warning(this,"Attenzione!","Devi selezionare almeno un elemento!");
    else{
    QModelIndexList selectedIndexes = Vcarrello->getTable()->selectionModel()->selectedRows();
    QMessageBox::StandardButton confirm
            = QMessageBox::question
            (this, "Conferma rimozione",
            "Confermi di voler rimuovere lo strumento selezionato?", QMessageBox::Yes|QMessageBox::No);

if(confirm == QMessageBox::Yes)

    for(auto i = 0; i< selectedIndexes.size();++i) {

        bool found = false;
        for(auto it = core->magazzino_begin();it!=core->magazzino_end(); ++it){
            Strumento *instrument = *it;

            if(*(*it) == *(core->carrelloAt(selectedIndexes[i].row()))){ //Nel magazzino sono presenti ancora strumenti uguali a quello che si vuole rimuovere dal carrello -> incremento quantita
                instrument->setQuantity( core->carrelloAt(selectedIndexes[i].row())->getQuantity() + instrument->getQuantity());
                found = true;
            }
        }

        if(!found)
            core->magazzino_push_end(core->carrelloAt(selectedIndexes[i].row())->clone());


        //vengono rimossi gli elementi selezionati dal carrello
            Vcarrello->getFilter()->removeRow(QPersistentModelIndex(selectedIndexes[i]).row());
    }

else
    return;

core->setDataSaved(false);

    }
slotUpdatePage();
}


void Controller::slotResetMagazzino()
{
 if(core->getMagazzinoSize() == 0){
      QMessageBox::warning(this,"Errore","Nessun elemento presente nel magazzino!");
      return;
 }
QMessageBox::StandardButton confirm  = QMessageBox::question
(this, "Conferma rimozione",
"Sei sicuro di volere cancellare tutti gli articoli presenti in magazzino?", QMessageBox::Yes|QMessageBox::No);

if(confirm == QMessageBox::Yes){
    resetMagazzino();
    //Update pagina delegato a deleteTables
}
else
    return;

}//slotResetMagazzino

void Controller::slotResetCarrello()
{
 if(core->getCarrelloSize() == 0){
      QMessageBox::warning(this,"Errore","Nessun elemento presente nel carrello!");
      return;
 }
QMessageBox::StandardButton confirm  = QMessageBox::question
(this, "Conferma rimozione",
"Sei sicuro di volere cancellare tutti gli articoli presenti nel carrello?", QMessageBox::Yes|QMessageBox::No);

if(confirm == QMessageBox::Yes){
    resetCarrello();
    //Update pagina delegato a deleteTables
}
else
    return;

}//slotResetOrdini


void Controller::resetMagazzino(){

    while(core->getMagazzinoSize())
    Vmagazzino->getFilter()->removeRows(0,1);

    core->setDataSaved(false);

    slotUpdatePage();



}//resetMagazzino

void Controller::resetCarrello(){

    while(core->getCarrelloSize()) {

        bool found = false;
        for(auto it = core->magazzino_begin();it!=core->magazzino_end(); ++it){
            Strumento *instrument = *it;

            if(*(*it) == *(core->carrelloAt(0))){ //Nel magazzino sono presenti ancora strumenti uguali a quello che si vuole rimuovere dal carrello -> incremento quantita
                instrument->setQuantity( core->carrelloAt(0)->getQuantity() + instrument->getQuantity());
                found = true;
            }
        }

        if(!found)
            core->magazzino_push_end(core->carrelloAt(0)->clone());

        Vcarrello->getFilter()->removeRows(0,1);
    }


    core->setDataSaved(false);

    slotUpdatePage();


}//resetCarrello



void Controller::slotResetTables(){

    QAction* send = qobject_cast<QAction*>(sender());
    if(send->text() == "Nuovo"){
 if(core->getCarrelloSize() || core->getMagazzinoSize()){
    QMessageBox::StandardButton reply= QMessageBox::question
(this,"Attenzione!","Cosi' facendo sovrascriverai i dati presenti, vuoi continuare?",
QMessageBox::Yes|QMessageBox::No);
if(reply==QMessageBox::No)
      return;
resetMagazzino();
resetCarrello();
        }


    }//Se la chiamata arriva da File > Nuovo
    resetMagazzino();
    resetCarrello();
}//resetTables


void Controller::slotDataChanged(){
    //Viene chiamato solo in seguito al segnale dataChanged emesso da adapter, che indica che i dati sono stai modificati
    core->setDataSaved(false);
    slotUpdatePage();

}


void Controller::slotUpdatePage(){

    /* AGGIORNAMENTO TABELLE */
    Vmagazzino->getAdapter()->dataRefresh();
    Vcarrello->getAdapter()->dataRefresh();

    /* AGGIORNAMENTO LABEL CONTA RISULTATI */

    int magazzinoSize = core->getMagazzinoSize();
    int carrelloSize = core->getCarrelloSize();

    if(pagine->currentIndex() == 0) { //Magazzino

            if(!magazzinoSize){
                itemCounter->setText("<b>Nessun prodotto presente!</b>");
                Vmagazzino->getEditEnabled()->setText("");
                Vmagazzino->getResultsNumber()->setText("<b>Per iniziare, carica un salvataggio</b>");
                Vmagazzino->getResultsNumber()->setStyleSheet("color : orange");
            }

            else {
                itemCounter->setText("<u>" + QString::number(magazzinoSize) + " prodotti presenti </u>");
                Vmagazzino->getEditEnabled()->setText("<u> Modifica abilitata! </u>");
                Vmagazzino->getResultsNumber()->setText("<b>" + QString::number(core->getMagazzinoSize()) + " strumenti trovati</b>");
                Vmagazzino->getResultsNumber()->setStyleSheet("color : green");
            }
    }

    else if(pagine->currentIndex() == 1) {//Carrello
            if(!carrelloSize)
                itemCounter->setText("<b>Nessun prodotto presente!</b>");

             else
                itemCounter->setText("<u>" + QString::number(carrelloSize) + " prodotti presenti </u>");

            }

    /* AGGIORNAMENTO STATUS BAR */

    /* AGGIORNAMENTO STATUS BAR */
}

/*
void Controller::closeEvent(QCloseEvent *event) {

            if(!core->isDataSaved()){
            QMessageBox::StandardButton reply= QMessageBox::question(this,"Attenzione!","Sono presenti dei dati non ancora salvati, desideri salvarli?",QMessageBox::Yes|QMessageBox::No);
            if(reply==QMessageBox::No)
              this->close();
            else
                slotSave();
           }else
               this->close();
    }

    */

