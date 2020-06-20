#include "basso.h"

const unsigned int Basso::defaultStrings = 4;
const std::map<Basso::bassType,std::string> Basso::bassTypes = {{electric,"Elettrico"},
                                {acoustic,"Acustico"}};
const QString Basso::json_type = "tipo";
const QString Basso::json_fretless = "fretless";

Basso::Basso(bassType _type, double _price, const std::string& _brand, const std::string& _model, const std::string& _desc, bool _used, unsigned int _stringNumber, bool _fretLess, unsigned int _quantity, const std::string& _path):
     Strumento(_price, _brand, _used, _desc, _quantity, _model, _path),
     Corda(_stringNumber),
     type(_type),
     fretLess(_fretLess){}

Strumento* Basso::clone() const {
     return new Basso(*this);
}

std::string Basso::className() const {
     return "Basso " + bassTypes.at(type) + (fretLess ? " fretless" : "");
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

     obj[json_type] = QString::fromStdString(bassTypes.at(type));
     obj[json_fretless] = fretLess ? "true" : "false";
}

bool Basso::operator==(const Basso& other) const {
     return
	  Corda::operator==(other) &&
	  type == other.type &&
	  fretLess == other.fretLess;
}

bool Basso::operator!=(const Basso& other) const {
     return !(*this == other);
}

Basso::bassType Basso::findType(const std::string& str){
     for(const auto& coppia : bassTypes)
	  if(str == coppia.second) return coppia.first;
     return electric;
}
