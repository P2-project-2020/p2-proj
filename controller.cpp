
#include "controller.h"
#include <QHBoxLayout>
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QGroupBox>

#include <QJsonDocument>
#include <QJsonObject>
#include <QAction>
#include <QPrinter>
#include <QPainter>

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
   // Vordini(new ordiniView(this,core)),
   // Vcarrello(new carrelloView(this,core)),
    mainLayout(new QBoxLayout(QBoxLayout::TopToBottom,this)),
    headerLayout(new QHBoxLayout),
    statusBar(new QHBoxLayout),
    itemCounter(new QLabel(this)),
    saveStatus(new QLabel(this))
{

    QGroupBox *logoBox = new QGroupBox();

    setStyleSheet("QTabWidget::pane {border: 0px;}");
    headerLayout->setSpacing(10);
    headerLayout->addWidget(menuBar);
    logoBox->setLayout(headerLayout);


    pagine->insertTab(0,Vmagazzino,"Magazzino");
    //pagine->insertTab(1,Vordini,"Ordini");
    //pagine->insertTab(1,Vcarrello,"Carrello");
    mainLayout->addWidget(pagine);

    statusBar->addWidget(itemCounter,Qt::AlignRight);
    statusBar->addWidget(saveStatus,Qt::AlignRight);
    mainLayout->addItem(statusBar);
    setLayout(mainLayout);

    this->layout()->setMenuBar(menuBar);

    core->magazzino_push_random();
    slotUpdatePage();


    connect(Vmagazzino->getAddView()->getAddItemButton(),SIGNAL(clicked()), this, SLOT(slotInserisci()));
    connect(Vmagazzino->getDeleteSelected(),SIGNAL(clicked()),this,SLOT(slotDeleteMagazzinoItem()));
    connect(Vmagazzino->getDeleteAll(),SIGNAL(clicked()),this,SLOT(slotResetMagazzino()));

    /*
    connect(Vmagazzino->getViewIns()->insertButton(),SIGNAL(clicked()),this, SLOT(slotInserisciPianta()));

    connect(pagine, SIGNAL(currentChanged(int)), this, SLOT(slotUpdatePage()));

    connect(Vpiante->getEliminaSel(),SIGNAL(clicked()),this,SLOT(slotDeletePianta()));

    connect(Vpiante->getEliminaT(),SIGNAL(clicked()),this,SLOT(slotResetPiante()));
    connect(menuBar->getSave(),SIGNAL(triggered()),this,SLOT(slotSave()));
    //Per sapere che i dati sono stati modificati in real time
    connect(Vshop->getAdapter(),SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(slotDataChanged()));
    connect(Vpiante->getAdapter(),SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(slotDataChanged()));

    */
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

    if(core->getMagazzinoSize() || core->getCarrelloSize() || core->getOrdiniSize()){
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
    try {

        int type= insert->getInstrumentType()->currentIndex();
        int arcType = insert->getArcoType()->currentIndex();
        int stringType = insert->getCordaType()->currentIndex();
        int percussionType = insert->getPercussioneType()->currentIndex();
        int fiatoType = insert->getFiatoType()->currentIndex();

        if(type == 0) throw inputException("Devi prima scegliere il tipo di strumento che vuoi inserire!");
        if(arcType == 0) throw inputException("Devi prima scegliere il tipo di strumento ad arco che vuoi inserire!");
        if(stringType == 0) throw inputException("Devi prima scegliere il tipo di strumento a corda che vuoi inserire!");
        if(percussionType == 0) throw inputException("Devi prima scegliere il tipo di strumento a percussione che vuoi inserire!");
        if(fiatoType == 0) throw inputException("Devi prima scegliere il tipo di strumento ad fiato che vuoi inserire!");

        double price = insert->getPrice()->text().toDouble();
        string description = insert->getDescription()->text().toStdString();
        string brand = insert->getBrand()->text().toStdString();
        string instrumentTune = insert->getInstrumentTune()->currentText().toStdString();
        bool isSecondHand = insert->getIsSecondHand()->isChecked();

        int stringsNumber = insert->getStringsNumber()->text().toInt();
        string guitarType = insert->getGuitarType()->currentText().toStdString();
        string guitarModel = insert->getModel()->text().toStdString();
        string bassType = insert->getBassType()->currentText().toStdString();
        bool isFretless = insert->getIsFretless()->isChecked();
        string pianoShape = insert->getPianoShape()->currentText().toStdString();
        string keysMaterial = insert->getKeysMaterial()->currentText().toStdString();
        string percussionMaterial = insert->getPercussioneMaterial()->currentText().toStdString();
        bool isMetalSnare = insert->getIsMetalSnare()->isChecked();
        string windMaterial = insert->getFiatoMaterial()->currentText().toStdString();

      Strumento* toPush = nullptr;

        switch (type) {
        //Arco
        case 1:

            switch(arcType) {
            case 1: //Violino
                toPush = new Violino(price, brand, description, isSecondHand);
            case 2: //Viola
                toPush = new Viola(price, brand, description, instrumentTune, isSecondHand);
            default:
                  throw inputException("Strumento non valido!");

                break;

            }

            break;

        case 2:
        //Corda
            switch(stringType) {
            case 1: //Chitarra
                toPush = new Chitarra(Chitarra::findType(guitarType), price, brand, guitarModel, description, isSecondHand, stringsNumber);
            case 2: //Basso
                toPush = new Basso(Basso::findType(bassType), price, brand, description, isSecondHand, stringsNumber, isFretless);
            case 3: //Pianoforte
                toPush = new Pianoforte(Pianoforte::findShape(pianoShape), Pianoforte::findKeys(keysMaterial), price, brand, isSecondHand, description);
            default:
                throw inputException("Strumento non valido!");

                break;
            }


            break;
        case 3:
        //Percussione
            switch(percussionType) {
            case 1: // Kit batteria
                toPush = new KitBatteria(price, brand, KitBatteria::findMaterial(percussionMaterial), isMetalSnare, isSecondHand, description);
            case 2: //Pianoforte
                toPush = new Pianoforte(Pianoforte::findShape(pianoShape), Pianoforte::findKeys(keysMaterial), price, brand, isSecondHand, description);
            default:
                throw inputException("Strumento non valido!");

                break;
            }


            break;

        case 4: //Fiato
            switch(fiatoType) {
            case 1: //Tromba
                toPush = new Tromba(Strumento::findTune(instrumentTune), price, brand, Fiato::findMaterial(windMaterial), isSecondHand, description );
            case 2: //Sax
                toPush = new Sax(Strumento::findTune(instrumentTune), price, brand, Fiato::findMaterial(windMaterial), isSecondHand);
            default:
                  throw inputException("Strumento non valido!");
                break;
            }


            break;
        default:
               throw inputException("Strumento non valido!");

        }


        if(toPush!= nullptr){
            core->push_end(toPush);
            QMessageBox::information(this,"Successo", "Strumento inserito correttamente");
            core->setDataSaved(false);
            slotUpdatePage();
        }

   } catch (inputException exc ) {
        QMessageBox::warning(this,"Spono",exc.getErrore());
    }
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
            "Confermi di volere rimuovere il prodotto selezionato?", QMessageBox::Yes|QMessageBox::No);

if(confirm == QMessageBox::Yes)
    for(auto i = 0; i< selectedIndexes.size();++i)
            Vmagazzino->getFilter()->removeRow(QPersistentModelIndex(selectedIndexes[i]).row());
else
    return;

core->setDataSaved(false);

    }
slotUpdatePage();
}




void Controller::slotResetOrdini()
{
 if(core->getOrdiniSize() == 0){
      QMessageBox::warning(this,"Errore","Nessun ordine presente!");
      return;
 }
QMessageBox::StandardButton confirm  =QMessageBox::question
(this, "Conferma rimozione",
"Sei sicuro di volere cancellare tutti gli ordini presenti?", QMessageBox::Yes|QMessageBox::No);

if(confirm == QMessageBox::Yes){
    resetOrdini();
    //Update pagina delegato a deleteTables
}
else
    return;

}//slotResetOrdini

void Controller::slotResetMagazzino()
{
 if(core->getMagazzinoSize() == 0){
      QMessageBox::warning(this,"Errore","Nessun elemento presente nel magazzino!");
      return;
 }
QMessageBox::StandardButton confirm  =QMessageBox::question
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
QMessageBox::StandardButton confirm  =QMessageBox::question
(this, "Conferma rimozione",
"Sei sicuro di volere cancellare tutti gli articoli presenti nel carrello?", QMessageBox::Yes|QMessageBox::No);

if(confirm == QMessageBox::Yes){
    resetCarrello();
    //Update pagina delegato a deleteTables
}
else
    return;

}//slotResetOrdini

void Controller::resetOrdini(){
/*
    while(core->getProdottiSize())
    Vshop->getFilter()->removeRows(0,1);

    core->setDataSaved(false);

    slotUpdatePage();

    */

}//resetOrdini

void Controller::resetMagazzino(){

    while(core->getMagazzinoSize())
    Vmagazzino->getFilter()->removeRows(0,1);

    core->setDataSaved(false);

    slotUpdatePage();



}//resetMagazzino

void Controller::resetCarrello(){
/*
    while(core->getProdottiSize())
    Vshop->getFilter()->removeRows(0,1);

    core->setDataSaved(false);

    slotUpdatePage();

    */

}//resetCarrello



void Controller::slotResetTables(){

    QAction* send = qobject_cast<QAction*>(sender());
    if(send->text() == "Nuovo"){
 if(core->getCarrelloSize() || core->getMagazzinoSize() || core->getOrdiniSize()){
    QMessageBox::StandardButton reply= QMessageBox::question
(this,"Attenzione!","Cosi' facendo sovrascriverai i dati presenti, vuoi continuare?",
QMessageBox::Yes|QMessageBox::No);
if(reply==QMessageBox::No)
      return;
resetMagazzino();
resetCarrello();
resetOrdini();
        }


    }//Se la chiamata arriva da File > Nuovo
    resetMagazzino();
    resetCarrello();
    resetOrdini();
}//resetTables


void Controller::slotDataChanged(){
    //Viene chiamato solo in seguito al segnale dataChanged emesso da adapter, che indica che i dati sono stai modificati
    core->setDataSaved(false);
    slotUpdatePage();

}


void Controller::slotUpdatePage(){

    /* AGGIORNAMENTO TABELLE */
    Vmagazzino->getAdapter()->dataRefresh();



    /* AGGIORNAMENTO LABEL CONTA RISULTATI */


    /* AGGIORNAMENTO LABEL CONTA RISULTATI */

    int magazzinoSize = core->getMagazzinoSize();

    if(pagine->currentIndex() == 0)
            if(!magazzinoSize){
                itemCounter->setText("<b>Nessun prodotto presente!</b>");
                Vmagazzino->getEditEnabled()->setText("");
            }else{
                itemCounter->setText("<u>" + QString::number(magazzinoSize) + " prodotti presenti </u>");
                Vmagazzino->getEditEnabled()->setText("<u> Modifica abilitata! </u>");
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

