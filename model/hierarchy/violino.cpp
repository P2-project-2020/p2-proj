#include "violino.h"

Violino::Violino(double _price, const std::string& _brand, const std::string& _model, const std::string& _desc, bool _used, unsigned int _quantity, const std::string& _path):
     Strumento(_price ,_brand, _used, _desc, _quantity, _model, _path),
     Arco(_brand == Strumento::lutherie),
     key(Strumento::contralto){}

Strumento* Violino::clone() const {
     return new Violino(*this);
}

std::string Violino::className() const {
     return "Violino";
}

Strumento::Tune Violino::tune() const {
     return key;
}

void Violino::setTune(const Strumento::Tune& new_tune){
     // if(new_tune)
     key = new_tune;
}

void Violino::loadData(const QJsonObject& obj){
     Arco::loadData(obj);
}

void Violino::saveData(QJsonObject& obj) const {
     Arco::saveData(obj);
}

bool Violino::operator==(const Violino& other) const {
     return
	  Arco::operator==(other) &&
	  key == other.key;
}

bool Violino::operator!=(const Violino& other) const {
     return !(*this == other);
}
