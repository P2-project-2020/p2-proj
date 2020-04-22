#include "basso.h"

const unsigned int Basso::defaultStrings = 4;
const std::vector<std::pair<Basso::bassType,std::string>> Basso::bassTypes = {{electric,"elettrico"}, {acoustic,"acustico"}};
const QString Basso::json_type = "tipo";
const QString Basso::json_fretless = "fretless";

Basso::Basso(bassType _type, double _price, const std::string& _brand, const std::string& _desc, bool _used, unsigned int _stringNumber, bool _fretLess):
	Strumento(_price, _brand, _used, _desc), Corda(_stringNumber), type(_type), fretLess(_fretLess){}

std::string Basso::className() const {
	return "Basso " + typeToString(type) + (fretLess ? " fretless" : "");
}

Basso::bassType Basso::getType() const {
    return type;
}

void Basso::loadData(const QJsonObject& obj) {
	Corda::loadData(obj);
	
	const QJsonValue& valType = obj[json_type];
	const QJsonValue& valFretless = obj[json_fretless];

	if(!valType.isUndefined() && valType.isString())
		type = findType(valType.toString().toStdString());
	if(!valFretless.isUndefined() && valFretless.isBool())
		fretLess = valFretless.toBool();
}

void Basso::saveData(QJsonObject& obj) const {
	Corda::saveData(obj);
}

Basso::bassType Basso::findType(const std::string& str){ // le stringhe dovrebbero forse essere preprocessate in modo da fare tutto lowercase se non vogliamo che sia case-sensitive
	for(const auto& coppia : bassTypes)
		if(str == coppia.second) return coppia.first;
	return electric;
}

std::string Basso::typeToString(const bassType& _type){
	return bassTypes[_type].second;
}
