#include "pianoforte.h"
const unsigned int Pianoforte::numberOfKeys = 48;
const std::vector<std::string> Pianoforte::shapes = {"coda", "muro"};
const std::vector<std::string> Pianoforte::keys = {"legno", "plastica", "avorio"};
const QString Pianoforte::json_shape = "forma";
const QString Pianoforte::json_shape = "tasti";

Pianoforte::Pianoforte(Pianoforte::Shape _shape, Pianoforte::Keys _keys, double _price, const std::string& _brand, bool _used, const std::string& _desc):
	Strumento(_price, _brand, _used, _desc),
	Corda(numberOfKeys*3),
	Percussione(true),
	pianoShape(_shape), pianoKeys(_keys){}

std::string Pianoforte::className() const {
	return "Pianoforte " + shapeToString(pianoShape);
}

std::string Pianoforte::getMaterial() const {
	keysToString(pianoKeys);
}

std::string Pianoforte::shapeToString(const Pianoforte::Shape& _shape){
	return shapes[_shape];
}

Pianoforte::Shape Pianoforte::findShape(onst std::string& _shape){
	for(Pianoforte::Shape i = grand; i < shapes.size(); ++i)
		if(_shape == shapes[i]) return i;
	return grand;
}

std::string Pianoforte::keysToString(const Pianoforte::Keys& _keys){
	return keyss[_keys];
}

Pianoforte::Keys Pianoforte::findKeys(onst std::string& _keys){
	for(Pianoforte::Keys i = wood; i < keyss.size(); ++i)
		if(_keys == keys[i]) return i;
	return wood;
}


void Pianoforte::loadData(const QJsonObject& obj){
	Corda::loadData(obj);
	Percussione::loadData(obj);

	const QJsonValueRef valShape = obj[json_shape];
	const QJsonValueRef valKeys = obj[json_keys];

	if(!valShape.isUndefined() && valShape.isString())
		pianoShape = findShape(valShape.toString().toStdString());
	if(!valKeys.isUndefined() && valKeys.isString())
		pianoKeys = findKeys(valKeys.toString().toStdString());
}

void Pianoforte::saveData(QJsonObject& obj) const {
	Corda::saveData(obj);
	Percussione::saveData(obj);

	obj[json_shape] = shapeToString(pianoShape);
	obj[json_keys] = keysToString(pianoKeys);
}
