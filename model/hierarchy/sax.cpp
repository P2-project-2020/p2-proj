#include "sax.h"

Sax::Sax(Strumento::Tune _tune, double _price, const std::string& _brand, Fiato::Material _material, bool _used):
	Strumento(_price, _brand, _used), Fiato(_material, _tune, Fiato::woodwind_mouthpiece){}

std::string Sax::className() const{
	return "Sax " + Strumento::tuneToString(tune());
}

void Sax::loadData(const QJsonObject& obj){
	Fiato::loadData(obj);
}

void Sax::saveData(QJsonObject& obj) const {
	Fiato::saveData(obj);
}