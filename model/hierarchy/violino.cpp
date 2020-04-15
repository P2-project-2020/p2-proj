#include "violino.h"
const std::string Violino::lutherie_string = "Liuteria";

Violino::Violino(double _price, const std::string& _brand, const std::string& _desc, bool _used):
	Strumento(_price ,_brand, _used, _desc), Arco(_brand == lutherie_string){}

std::string Violino::className() const {
	return "Violino";
}

Strumento::Tune Violino::tune() const {
	return undefined;
}

void Violino::loadData(const QJsonObject& obj){
	Arco::loadData(obj);
}

void Violino::saveData(QJsonObject& obj) const {
	Arco::saveData(obj);
}
