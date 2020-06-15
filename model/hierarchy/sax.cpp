#include "sax.h"

Sax::Sax(Strumento::Tune _tune, double _price, const std::string& _brand, int _material, bool _used, unsigned int _quantity, const std::string& _desc):
     Strumento(_price, _brand, _used, _desc, _quantity),
     Fiato(_material, _tune, Fiato::woodwind_mouthpiece){}

std::string Sax::className() const{
     return "Sax";
}

void Sax::loadData(const QJsonObject& obj){
	Fiato::loadData(obj);
}

void Sax::saveData(QJsonObject& obj) const {
	Fiato::saveData(obj);
}
