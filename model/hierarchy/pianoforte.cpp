#include "pianoforte.h"

const unsigned int Pianoforte::numberOfKeys = 48;
const std::vector<std::string> Pianoforte::shapes = {"coda", "muro"};
const std::vector<std::string> Pianoforte::keys = {"legno", "plastica", "avorio"};
const QString Pianoforte::json_shape = "forma";
const QString Pianoforte::json_keys = "tasti";

Pianoforte::Pianoforte(int _shape, int _keys, double _price, const std::string& _brand, const std::string& _model, bool _used, const std::string& _desc, unsigned int _quantity):
     Strumento(_price, _brand, _used, _desc, _quantity, _model),
     Corda(numberOfKeys*3),
     Percussione(true),
     pianoShape(_shape >= 0 && _shape < (int)shapes.size() ? _shape : 0),
     pianoKeys(_keys >= 0 && _keys < (int)keys.size() ? _keys : 0){}

Strumento* Pianoforte::clone() const {
     return new Pianoforte(*this);
}

std::string Pianoforte::className() const {
     return "Pianoforte " + shapes.at(pianoShape);
}

std::string Pianoforte::getMaterial() const {
     return keys.at(pianoKeys);
}

void Pianoforte::setMaterial(int new_material){
     if(new_material >= 0 && new_material < (int)keys.size()){
	  pianoKeys = new_material;
     }
}

int Pianoforte::findShape(const std::string& _shape){
     for(unsigned int i=0; i < shapes.size(); ++i)
	  if(_shape == shapes.at(i)) return i;
     return 0;
}

int Pianoforte::findKeys(const std::string& _key){
     for(unsigned int i=0; i < keys.size(); ++i)
	  if(_key == keys.at(i)) return i;
     return 0;
}


void Pianoforte::loadData(const QJsonObject& obj){
     Corda::loadData(obj);
     Percussione::loadData(obj);

     const QJsonValue& valShape = obj[json_shape];
     const QJsonValue& valKeys = obj[json_keys];

     if(!valShape.isUndefined() && valShape.isString())
	  pianoShape = findShape(valShape.toString().toStdString());
     if(!valKeys.isUndefined() && valKeys.isString())
	  pianoKeys = findKeys(valKeys.toString().toStdString());
}

void Pianoforte::saveData(QJsonObject& obj) const {
     Corda::saveData(obj);
     Percussione::saveData(obj);

     obj[json_shape] = QString::fromStdString(shapes.at(pianoShape));
     obj[json_keys] = QString::fromStdString(keys.at(pianoKeys));
}

bool Pianoforte::operator==(const Pianoforte& other) const {
     return
	  Corda::operator==(other) &&
	  Percussione::operator==(other) &&
	  pianoShape == other.pianoShape &&
	  pianoKeys == other.pianoKeys;
}

bool Pianoforte::operator!=(const Pianoforte& other) const {
     return !(*this == other);
}
