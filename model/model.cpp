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

	// salva magazzino
	for(auto it = magazzino_cbegin();it!=magazzino_cend(); ++it){
		QJsonObject jsonInstrument;
		Strumento *instrumentObject = *it;
		instrumentObject->saveData(jsonInstrument);
		jsonArray.append(jsonInstrument);
	}
	json["Magazzino"] = jsonArray;

	while(jsonArray.count())
		jsonArray.pop_back();
	
	//salva carrello
	for(auto it = carrello_cbegin();it!=carrello_cend(); ++it){
		QJsonObject jsonInstrument;
		Strumento *instrumentObject = *it;
		instrumentObject->saveData(jsonInstrument);
		jsonArray.append(jsonInstrument);
	}
	json["Carrello"] = jsonArray;
	
	while(jsonArray.count())
		jsonArray.pop_back();
}


bool Model::unserializeData(const QJsonObject& jsonObj)
{
	QJsonArray jsonMagazzino = jsonObj["Magazzino"].toArray();
	QJsonArray jsonCarrello = jsonObj["Carrello"].toArray();

	//Carica magazzino
	for(auto it = jsonMagazzino.begin(); it != jsonMagazzino.end(); ++it){
		QJsonObject obj = it->toObject();
		std::string type;

		if(obj.contains(Strumento::json_type))
			type = obj[Strumento::json_type].toString().toStdString();
		else type = "";

		Strumento* retrive = nullptr;

		if(type == "Viola")
			retrive	 = new Viola();
		else if(type == "Violino")
			retrive	 = new Violino();
		else if(type == "Chitarra")
			retrive	 = new Chitarra();
		else if(type == "Basso")
			retrive	 = new Basso();
		else if(type == "Pianoforte")
			retrive	 = new Pianoforte();
		else if(type == "KitBatteria")
			retrive	 = new KitBatteria();
		else if(type == "Sax")
			retrive	 = new Sax();
		else if(type == "Tromba")
			retrive	 = new Tromba();

		if(retrive){
			retrive->loadData(obj);
			magazzino->push_back(retrive);
		}
	}

//Carica carrello
	for(auto it = jsonCarrello.begin(); it != jsonCarrello.end(); ++it){
		QJsonObject obj = it->toObject();
		std::string type;
		
		if(obj.contains(Strumento::json_type))
			type = obj[Strumento::json_type].toString().toStdString();
		else type = "";
		
		Strumento* retrive = nullptr;

		if(type == "Viola")
			retrive	 = new Viola();
		else if(type == "Violino")
			retrive	 = new Violino();
		else if(type == "Chitarra")
			retrive	 = new Chitarra();
		else if(type == "Basso")
			retrive	 = new Basso();
		else if(type == "Pianoforte")
			retrive	 = new Pianoforte();
		else if(type == "KitBatteria")
			retrive	 = new KitBatteria();
		else if(type == "Sax")
			retrive	 = new Sax();
		else if(type == "Tromba")
			retrive	 = new Tromba();

		if(retrive){
			retrive->loadData(obj);
			carrello->push_back(retrive);
		}
	}

	return true;
}

bool Model::isDataSaved() const{
	return saved;
}

void Model::setDataSaved(bool b){
	saved=b;
}

/* ITERATORI COSTANTI E NON */

Container<Strumento*>::iterator Model::magazzino_begin(){
	return	magazzino->begin();
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

Strumento *Model::magazzinoAt(unsigned int ind){
	return magazzino->at(ind);
}

Strumento *Model::carrelloAt(unsigned int ind){
	return carrello->at(ind);
}

unsigned int Model::getMagazzinoSize() const
{
	return magazzino->getSize();
}

unsigned int Model::getCarrelloSize() const
{
	return carrello->getSize();
}

void Model::eraseMagazzino(unsigned int index ){
	saved=false;
	magazzino->erase(index);
}

void Model::eraseCarrello(unsigned int index ){
	saved=false;
	carrello->erase(index);
}

void Model::eraseMagazzino(unsigned int start, unsigned int end){
	saved=false;
	magazzino->erase(start,end);
}

void Model::eraseCarrello(unsigned int start, unsigned int end){
	saved=false;
	carrello->erase(start,end);
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
