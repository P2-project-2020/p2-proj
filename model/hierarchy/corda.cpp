#include "corda.h"
const QString Corda::json_strings = "corde";

Corda::Corda(unsigned int _strings): // derivazione virtuale && calsse astratta => non dovrà mai occuparsi di costruire Strumento
    strings(_strings){}

/*Corda::Corda(double _price, const std::string& _brand, const std::string& _desc, bool _used, unsigned int _stringsNumber):
    Strumento(_price, _brand, _used, _desc), strings(_stringsNumber){}*/

unsigned int Corda::getStringsNumber() const { return strings; }

void Corda::setStringsNumber(unsigned int n){ strings = n; }

void Corda::loadData(const QJsonObject& obj){
	Strumento::loadData(obj);
	
	QJsonValue val = obj[json_strings];
	if(!val.isUndefined() && val.isDouble() && val.toDouble() > 0)
		strings = val.toInt();
}


void Corda::saveData(QJsonObject& obj) const {
	Strumento::saveData(obj);

	obj[json_strings] = int(strings);
}