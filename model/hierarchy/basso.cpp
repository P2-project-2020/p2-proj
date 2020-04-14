#include "basso.h"
const unsigned int Basso::defaultStrings = 4;

Basso::Basso(bassType _type, double _price, const std::string& _brand, const std::string& _desc, bool _used, unsigned int _stringNumber, bool _fretLess):
	Strumento(_price, _brand, _used, _desc), Corda(_stringNumber), type(_type), fretLess(_fretLess){}

std::string Basso::className() const {
	std::string specifier;
	if(type == electric) specifier = "elettrico";
	else specifier = "acustico";
	if(fretLess) specifier += " fretless";
	return "basso " + specifier;
}

void Basso::loadData(const QJsonObject& obj) {
	// strumento
	setPrice(obj["prezzo"].toDouble());
	setBrand(obj["brand"].toString().toStdString());
	setUsed(obj["usato"].toBool());
	setDescription(obj["descrizione"].toString().toStdString());
	// corda
	int nCorde = obj["corde"].toInt();
	if(nCorde > 0) setStringsNumber(nCorde);
	
	//Basso
	switch(obj["tipo"].toString().toStdString()){
	case "elettrico":
		type = electric; break;
	case "acustico"
		type = acoustic; break;
	}
	fretLess = obj["fretless"].toBool();
}
void Basso::saveData(QJsonObject&) const {
	// strumento
	// dovrei dare una interfaccia consistente ai nomi nel json, partendo da strumento
	// corda
	// basso
}
