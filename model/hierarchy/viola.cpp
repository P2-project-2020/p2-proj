#include "viola.h"

Viola::Viola(double _price, const std::string& _brand, const std::string& _desc, Strumento::Tune _key, bool _used):
	Strumento(_price ,_brand, _used, _desc), Arco(_brand == Strumento::lutherie), key(_key){}

std::string Viola::className() const {
	return "Viola";
}

Strumento::Tune Viola::tune() const {
	return key;
}

void Viola::loadData(const QJsonObject& obj){
	Arco::loadData(obj);

	const QJsonValue& valTune = obj[Strumento::json_tune];
	if(!valTune.isUndefined() && valTune.isString())
		key = Strumento::findTune(valTune.toString().toStdString());
}

void Viola::saveData(QJsonObject& obj) const {
	Arco::saveData(obj);
	
	obj[Strumento::json_tune] = QString::fromStdString(Strumento::Tunes.at(key));
}
