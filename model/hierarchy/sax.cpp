#include "sax.h"

Sax::Sax(Strumento::Tune _tune, double _price, const std::string& _brand, const std::string& _model, int _material, bool _used, unsigned int _quantity, const std::string& _desc, const std::string& _path):
     Strumento(_price, _brand, _used, _desc, _quantity, _model, _path),
     Fiato(_material, _tune, Fiato::woodwind_mouthpiece){}

Strumento* Sax::clone() const {
     return new Sax(*this);
}

std::string Sax::className() const{
     return "Sax";
}

void Sax::loadData(const QJsonObject& obj){
     Fiato::loadData(obj);
}

void Sax::saveData(QJsonObject& obj) const {
     Fiato::saveData(obj);
}

bool Sax::operator==(const Sax& other) const {
     return
	  Fiato::operator==(other);
}

bool Sax::operator!=(const Sax& other) const {
     return !(*this == other);
}
