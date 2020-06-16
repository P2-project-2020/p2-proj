#include "violino.h"

Violino::Violino(double _price, const std::string& _brand, const std::string& _desc, bool _used):
     Strumento(_price ,_brand, _used, _desc), Arco(_brand == Strumento::lutherie){}

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
