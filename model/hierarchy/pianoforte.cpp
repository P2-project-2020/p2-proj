#include "pianoforte.h"

const unsigned int Pianoforte::numberOfKeys = 48;
const std::map<Pianoforte::Shape, std::string> Pianoforte::shapes = {{grand, "coda"},
																	 {upright, "muro"}};
const std::map<Pianoforte::Keys, std::string> Pianoforte::keys = {{wood, "legno"},
																  {plastic, "plastica"},
																  {ivory, "avorio"}};
const QString Pianoforte::json_shape = "forma";
const QString Pianoforte::json_keys = "tasti";

Pianoforte::Pianoforte(Pianoforte::Shape _shape, Pianoforte::Keys _keys, double _price, const std::string& _brand, bool _used, const std::string& _desc):
	Strumento(_price, _brand, _used, _desc),
	Corda(numberOfKeys*3),
	Percussione(true),
	pianoShape(_shape), pianoKeys(_keys){}

std::string Pianoforte::className() const {
	return "Pianoforte " + shapeToString(pianoShape);
}

std::string Pianoforte::getMaterial() const {
	return keysToString(pianoKeys);
}

std::string Pianoforte::shapeToString(const Pianoforte::Shape& _shape){
	return shapes.at(_shape);
}

Pianoforte::Shape Pianoforte::findShape(const std::string& _shape){
	for(const auto& s : shapes)
		if(_shape == s.second) return s.first;
	return upright;							// solo perchè è più probabile dato che sono i più economici in media
}

std::string Pianoforte::keysToString(const Pianoforte::Keys& _key){
	return keys.at(_key);
}

Pianoforte::Keys Pianoforte::findKeys(const std::string& _keys){
	for(const auto& key : keys)
		if(key.second == _keys) return key.first;
	return keys.begin()->first;
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

	obj[json_shape] = QString::fromStdString(shapeToString(pianoShape));
	obj[json_keys] = QString::fromStdString(keysToString(pianoKeys));
}
