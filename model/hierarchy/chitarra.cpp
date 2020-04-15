#include "chitarra.h"

const unsigned int Chitarra::defaultStrings = 6;
const std::vector<std::pair<Chitarra::guitarType, std::string>> Chitarra::guitarTypes = {{Chitarra::electric, "elettrica"},
																			   {Chitarra::acoustic, "acustica"},
																			   {Chitarra::classic, "classica"}};
const QString Chitarra::json_type = "tipo";
const QString Chitarra::json_model = "modello";

Chitarra::Chitarra(Chitarra::guitarType _type, double _price, const std::string& _brand, const std::string& _model, const std::string& _desc, bool _used, unsigned int _stringsNumber):
	Strumento(_price,_brand,_used,_desc), Corda(_stringsNumber), type(_type), model(_model){}

std::string Chitarra::typeToString(const guitarType& _type){
	for(const auto& gType : guitarTypes)
		if(gType.first == _type) return gType.second;
	return "";
}

Chitarra::guitarType Chitarra::findType(const std::string& str){
	for(const auto& gType : guitarTypes){
		if(str == gType.second) return gType.first;
	}
	return electric;
}

Strumento::Tune Chitarra::tune() const { return undefined; }

std::string Chitarra::className() const {
	return std::string("chitarra ") + typeToString(type) + " " + model;
}

void Chitarra::loadData(const QJsonObject& obj){
	Corda::loadData(obj);

	const QJsonValue& valType = obj[json_type];
	const QJsonValue& valModel = obj[json_model];

	if(!valType.isUndefined() && valType.isString())
		type = Chitarra::findType(valType.toString().toStdString());

	if(!valModel.isUndefined() && valModel.isString())
		model = valModel.toString().toStdString();
}

void Chitarra::saveData(QJsonObject& obj) const {
	Corda::saveData(obj);

	obj[json_type] = QString::fromStdString(typeToString(type));
	obj[json_model] = QString::fromStdString(model);
}
