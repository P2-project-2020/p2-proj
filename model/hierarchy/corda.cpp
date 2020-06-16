#include "corda.h"
const QString Corda::json_strings = "corde";

Corda::Corda(unsigned int _strings): // derivazione virtuale && calsse astratta => non dovrà mai occuparsi di costruire Strumento
    strings(_strings){}

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

bool Corda::operator==(const Corda& other) const {
     return
	  Strumento::operator==(other) &&
	  strings == other.strings;
}
