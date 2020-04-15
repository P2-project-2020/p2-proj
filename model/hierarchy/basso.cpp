#include "basso.h"

const unsigned int Basso::defaultStrings = 4;
const std::vector<std::string> Basso::bassTypes = {"elettrico", "acustico"};
const QString Basso::json_type = "tipo";
const QString Basso::json_model = "modello";

Basso::Basso(bassType _type, double _price, const std::string& _brand, const std::string& _desc, bool _used, unsigned int _stringNumber, bool _fretLess):
	Strumento(_price, _brand, _used, _desc), Corda(_stringNumber), type(_type), fretLess(_fretLess){}

std::string Basso::className() const {
	return "basso " + typeToString(type) + (fretless ? " fretless" : "");
}

void Basso::loadData(const QJsonObject& obj) {
	Corda::loadData(obj);
	
	const QJsonValueRef valType = obj[json_type];
	const QJsonValueRef valModel = obj[json_model];

	if(!valType.isUndefined() && valType.isString())
		type = findType(valType.toString().toStdString());
	if(!valModel.isUndefined() && valModel.isString())
		model = valModel.toString().toStdString();
}

void Basso::saveData(QJsonObject&) const {
	Corda::saveData(obj);
}

bassType Basso::findType(const std::string& str){ // le stringhe dovrebbero forse essere preprocessate in modo da fare tutto lowercase se non vogliamo che sia case-sensitive
	bassType to_return = electric;
	for(unsigned int i = 0; i < bassTypes.size(); ++i)
		if(bassTypes[i] == str) to_return = i;
	return to_return;
}

std::string Basso::typeToString(const bassType& _type){
	return bassTypes[_type];
}
