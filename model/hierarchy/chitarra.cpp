#include "chitarra.h"

const unsigned int Chitarra::defaultStrings = 6;
const std::vector<std::string> guitarTypes = {"elettrica", "acustica", "classica"};
const QString Chitarra::json_type = "tipo";
const QString Chitarra::json_model = "modello";

Chitarra::Chitarra(Chitarra::guitarType _type, double _price, const std::string& _brand, const std::string& _model, const std::string& _desc, bool _used, unsigned int _stringsNumber):
	Strumento(_price,_brand,_used,_desc), Corda(_stringsNumber), type(_type), model(_model){}

std::string Chitarra::typeToString(const guitarType& _type){
	return guitarTypes[_type];
}

guitarType findType(const std::string& str){
	guitarType to_return = elettrica;
	for(unsigned int i=0; i<guitarTypes.size(); ++i)
		if(guitarTypes[i] == str)
			to_return = i;
	return to_return;
}

Strumento::Tune Chitarra::tune() const { return undefined; }

std::string Chitarra::className() const {
	return std::string("chitarra ") + typeToString(type) + " " + model;
}

void Chitarra::loadData(const QJsonObject& obj){
	Corda::loadData(obj);

	const QJsonValueRef valType = obj[json_type];
	const QJsonValueRef valModel = obj[json_model];

	if(!valType.isUndefined() && valType.isString())
		type = Chitarra::findType(valType.tpString.toStdString());

	if(!valModel.isUndefined() && valModel.isString())
		model = valModel.toString().toStdString();
}

void Chitarra::saveData(QJsonObject& obj) const {
	Corda::saveData(obj);

	obj[json_type] = typeToString(type);
	obj[json_model] = model;
}
