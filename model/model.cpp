#include "model.h"

#include <QMessageBox>


// #include <View/inputexception.h>

#include "model/hierarchy/basso.h"
#include "model/hierarchy/violino.h"
#include "model/hierarchy/viola.h"
#include "model/hierarchy/kitBatteria.h"
#include "model/hierarchy/pianoforte.h"
#include "model/hierarchy/sax.h"
#include "model/hierarchy/chitarra.h"
#include "model/hierarchy/tromba.h"



#include <QDebug>

Model::Model():
    magazzino(new Container<Strumento*>(2)),
    carrello(new Container<Strumento*>(2)),
    saved(true){}

Model::~Model(){
    for(unsigned int i=0; i<magazzino->getSize(); i++)
        delete magazzino->at(i);//Distruzione profonda
    delete magazzino;
    for(unsigned int i=0; i<carrello->getSize(); i++)
        delete carrello->at(i);//Distruzione profonda
    delete carrello;
}
void Model::serializeData(QJsonObject& json)
{
    QJsonArray jsonArray;
    QJsonObject jsonInstrument;
    for(auto it = magazzino_cbegin();it!=magazzino_cend(); ++it){

        Strumento *instrumentObject = *it;
        instrumentObject->saveData(jsonInstrument);
        jsonArray.append(jsonInstrument);
    }
    for(auto it = carrello_cbegin();it!=carrello_cend(); ++it){

        Strumento *instrumentObject = *it;
        instrumentObject->saveData(jsonInstrument);
        jsonArray.append(jsonInstrument);
    }
    json["Strumenti"] = jsonArray;
}

/*
bool Model::unserializeData(const QJsonObject& jsonObj)
{
    try{

    QJsonArray jsonArray;
    if(jsonObj.contains("Cannabis"))
        jsonArray = jsonObj["Cannabis"].toArray();
    else
       throw  inputException("Wrong header");

    for(int ind = 0; ind<jsonArray.size();++ind)
    {
        QJsonObject jsonCannabis = jsonArray[ind].toObject();
        string cat ="";
        if(jsonCannabis.contains("categoria"))
            cat = jsonCannabis["categoria"].toString().toStdString();
        else
            throw inputException("Il File JSON e' corrotto: Chiave categoria mancante");
        Cannabis* retrieve = nullptr;
        if(cat == "Fiore")
            retrieve = new Fiore;
        else if(cat == "Estratto")
                retrieve = new Estratto;
              else if(cat == "Commestibile")
                      retrieve = new Commestibile;
                    else if(cat == "Pianta")
                            retrieve = new Pianta;
                    else throw inputException("File JSON corrotto: Categoria non trovata");

        retrieve->loadData(jsonCannabis);
        push_end(retrieve);
    } //scorro gli elementi del Container
    }catch(inputException exc){qDebug()<<exc.getErrore();}

    return true;
}//loadData

*/
bool Model::isDataSaved() const{
    return saved;
}

void Model::setDataSaved(bool b){
    saved=b;
}

/* ITERATORI COSTANTI E NON */

Container<Strumento*>::iterator Model::magazzino_begin(){
    return  magazzino->begin();
}
Container<Strumento*>::iterator Model::magazzino_end(){
    return magazzino->end();
}

Container<Strumento*>::iterator Model::carrello_begin(){
    return carrello->begin();
}

Container<Strumento*>::iterator Model::carrello_end(){
    return carrello->end();
}

Container<Strumento*>::iterator Model::ordini_begin(){
    return ordini->begin();
}

Container<Strumento*>::iterator Model::ordini_end(){
    return ordini->end();
}


Container<Strumento*>::const_iterator Model::magazzino_cbegin() const
{
    return magazzino->cbegin();
}

Container<Strumento*>::const_iterator Model::magazzino_cend() const
{
    return magazzino->cend();
}

Container<Strumento*>::const_iterator Model::carrello_cbegin() const
{
    return carrello->cbegin();
}

Container<Strumento*>::const_iterator Model::carrello_cend() const
{
    return carrello->cend();
}

Container<Strumento*>::const_iterator Model::ordini_cbegin() const
{
    return ordini->cbegin();
}

Container<Strumento*>::const_iterator Model::ordini_cend() const
{
    return ordini->cend();
}

/* ITERATORI COSTANTI E NON */

void Model::magazzino_push_end(Strumento *instrument)
{
    magazzino->push_back(instrument);
}

void Model::magazzino_push_random()
{
    int num;

    for(int i=0;i<100; ++i){
        num = rand() % 8;
        switch(num){
            case(0):
                magazzino->push_back(new Violino());
                break;
            case(1):
                magazzino->push_back(new Viola());
                break;
            case(2):
                magazzino->push_back(new Sax());
                break;
            case(3):
                magazzino->push_back(new Tromba());
                break;
            case(4):
                magazzino->push_back(new Chitarra());
                break;
            case(5):
                magazzino->push_back(new Basso());
                break;
            case(6):
                magazzino->push_back(new Pianoforte());
                break;
            case(7):
                magazzino->push_back(new KitBatteria());
                break;

                        }


    }
}

void Model::carrello_push_end(Strumento *instrument)
{
    carrello->push_back(instrument);
}

void Model::ordini_push_end(Strumento *instrument)
{
    ordini->push_back(instrument);
}



Strumento *Model::magazzinoAt(unsigned int ind){
    return magazzino->at(ind);
}

Strumento *Model::carrelloAt(unsigned int ind){
    return carrello->at(ind);
}

Strumento *Model::ordiniAt(unsigned int ind){
    return ordini->at(ind);
}

unsigned int Model::getMagazzinoSize() const
{
    return magazzino->getSize();
}

unsigned int Model::getCarrelloSize() const
{
    return carrello->getSize();
}

unsigned int Model::getOrdiniSize() const
{
    return ordini->getSize();
}

void Model::eraseMagazzino(unsigned int index ){
    saved=false;
    magazzino->erase(index);
}

void Model::eraseCarrello(unsigned int index ){
    saved=false;
    carrello->erase(index);
}
void Model::eraseOrdini(unsigned int index ){
    saved=false;
    ordini->erase(index);
}

void Model::eraseMagazzino(unsigned int start, unsigned int end){
    saved=false;
    magazzino->erase(start,end);
}

void Model::eraseCarrello(unsigned int start, unsigned int end){
    saved=false;
    carrello->erase(start,end);
}

void Model::eraseOrdini(unsigned int start, unsigned int end){
    saved=false;
    ordini->erase(start,end);
}


void Model::resetMagazzino(){
    saved = false;
    eraseMagazzino(0,magazzino->getSize());
    delete magazzino;
}
void Model::resetCarrello(){
    saved = false;
    eraseCarrello(0,carrello->getSize());
    delete carrello;
}

void Model::resetOrdini(){
    saved = false;
    eraseOrdini(0,carrello->getSize());
    delete ordini;
}

