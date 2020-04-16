
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

    slotUpdatePage();

/*
    connect(Vshop->getViewIns()->insertButton(),SIGNAL(clicked()), this, SLOT(slotInserisci()));
    connect(Vpiante->getViewIns()->insertButton(),SIGNAL(clicked()),this, SLOT(slotInserisciPianta()));
    connect(pagine, SIGNAL(currentChanged(int)), this, SLOT(slotUpdatePage()));
    connect(Vshop->getEliminaSel(),SIGNAL(clicked()),this,SLOT(slotDeleteProdotto()));
    connect(Vpiante->getEliminaSel(),SIGNAL(clicked()),this,SLOT(slotDeletePianta()));
    connect(Vshop->getEliminaT(),SIGNAL(clicked()),this,SLOT(slotResetProdotti()));
    connect(Vpiante->getEliminaT(),SIGNAL(clicked()),this,SLOT(slotResetPiante()));
    connect(menuBar->getSave(),SIGNAL(triggered()),this,SLOT(slotSave()));
    //Per sapere che i dati sono stati modificati in real time
    connect(Vshop->getAdapter(),SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(slotDataChanged()));
    connect(Vpiante->getAdapter(),SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(slotDataChanged()));

    */
}

QString Controller::getCurrentFile() const{ return currentFile;}

/*
void Controller::slotSave(){
   if(core->isDataSaved()){
        QMessageBox::information(this,"Informazione","No Worries! I dati correnti sono gia' salvati");
        return;
    }
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
                    QDir::homePath(),
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
        if(overr)//Salvataggio sullo stesso file
            QMessageBox::information(this,"Successo!","File JSON sovrascritto correttamente");
        else
            QMessageBox::information(this,"Successo!","File JSON salvato correttamente");
     }else//Errore nella lettura del file di salvataggio
         QMessageBox::critical(this,"Errore!","Errore nel salvataggio del file scelto");

}

}//slotSave
*/

/*
void Controller::slotLoad(){

    if(core->getPianteSize() || core->getProdottiSize()){
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
                    QDir::homePath(),
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
*/

/*
void Controller::slotInserisci(){

    viewInserisci *Inserisci = Vshop->getViewIns();
    try {

        int type= Inserisci->baseFieldTipo()->currentIndex();

        if(type == 0) throw inputException("Devi prima scegliere il tipo di prodotto che vuoi inserire!");

        double thc = Inserisci->fieldTHC()->text().toDouble();
        double cbd = Inserisci->fieldCBD()->text().toDouble();
        int indica = Inserisci->fieldIndica()->text().toInt();
        int sativa = Inserisci->fieldSativa()->text().toInt();
        string strain = Inserisci->fieldStrain()->text().toStdString();

        double prezzo = Inserisci->fieldPrezzoBase()->text().toDouble();
        bool hq = Inserisci->fieldHQ()->isChecked();
        double peso = Inserisci->fieldPeso()->text().toDouble();

        string estratto = Inserisci->fieldTipoEstratto()->currentText().toStdString();
        string commestibile = Inserisci->fieldTipoCommestibile()->currentText().toStdString();
        bool indoor = Inserisci->fieldIndoor()->isChecked();

        Cannabis* toPush=nullptr;




        switch (type) {
        case 1://Fiore
               toPush = new Fiore(thc,cbd,indica,sativa,strain,peso,prezzo,hq,indoor);
            break;
        case 2://Estratto
                toPush = new Estratto(thc,cbd,indica,sativa,strain,peso,prezzo,hq,
                                       Estratto::toEnum(estratto));
            break;
        case 3://Commestibile
                toPush = new Commestibile(thc,cbd,indica,sativa,strain,peso,prezzo,hq,
                                          Commestibile::toEnum(commestibile));
            break;
      default:
            throw inputException("Prodotto non valido!");

        }


        if(toPush!= nullptr){
            core->push_end(toPush);
            QMessageBox::information(this,"Successo", "Prodotto inserito correttamente");
            core->setDataSaved(false);
            slotUpdatePage();
        }

   } catch (inputException exc ) {
        QMessageBox::warning(this,"Spono",exc.getErrore());
    }
}

*/




/*

void Controller::slotDeleteProdotto()
{

    if(!Vshop->getTable()->selectionModel()->hasSelection())
        QMessageBox::warning(this,"Attenzione!","Devi selezionare almeno un elemento!");
    else{
    QModelIndexList selectedIndexes = Vshop->getTable()->selectionModel()->selectedRows();
    QMessageBox::StandardButton confirm
            = QMessageBox::question
            (this, "Conferma rimozione",
            "Confermi di volere rimuovere il prodotto selezionato?", QMessageBox::Yes|QMessageBox::No);

if(confirm == QMessageBox::Yes)
    for(auto i = 0; i< selectedIndexes.size();++i)
            Vshop->getFilter()->removeRow(QPersistentModelIndex(selectedIndexes[i]).row());
else
    return;

core->setDataSaved(false);

    }
slotUpdatePage();
}

*/


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
/*
    while(core->getProdottiSize())
    Vshop->getFilter()->removeRows(0,1);

    core->setDataSaved(false);

    slotUpdatePage();

    */

}//resetMagazzino

void Controller::resetCarrello(){
/*
    while(core->getProdottiSize())
    Vshop->getFilter()->removeRows(0,1);

    core->setDataSaved(false);

    slotUpdatePage();

    */

}//resetCarrello


/*
void Controller::slotResetTables(){

    QAction* send = qobject_cast<QAction*>(sender());
    if(send->text() == "Nuovo"){
 if(core->getPianteSize() || core->getProdottiSize()){
    QMessageBox::StandardButton reply= QMessageBox::question
(this,"Attenzione!","Cosi' facendo sovrascriverai i dati presenti, vuoi continuare?",
QMessageBox::Yes|QMessageBox::No);
if(reply==QMessageBox::No)
      return;
resetProdotti();
resetPiante();
        }
 resetProdotti();
 resetPiante();


    }//Se la chiamata arriva da File > Nuovo
    resetProdotti();
    resetPiante();
}//resetTables
*/

void Controller::slotDataChanged(){
    //Viene chiamato solo in seguito al segnale dataChanged emesso da adapter, che indica che i dati sono stai modificati
    core->setDataSaved(false);
    slotUpdatePage();

}


void Controller::slotUpdatePage(){

    /* AGGIORNAMENTO TABELLE */



    /* AGGIORNAMENTO LABEL CONTA RISULTATI */


    /* AGGIORNAMENTO LABEL CONTA RISULTATI */

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

