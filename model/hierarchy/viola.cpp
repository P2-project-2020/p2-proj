#include "viola.h"
const std::string Viola::lutherie_string = "Liuteria";
const QString Viola::json_tune = "intonazione";

Viola::Viola(double _price, const std::string& _brand, const std::string& _desc, Strumento::Tune _key, bool _used):
	Strumento(_price ,_brand, _used, _desc), Arco(_brand == lutherie_string), key(_key){}

std::string Viola::className() const {
	return "Viola";
}

Strumento::Tune Viola::tune() const {
	return key;
}

void Viola::loadData(const OJsonObject& obj){
	Arco::loadData(obj);

	const QJsonValueRef valTune = obj[json_tune];
	if(!valTune.isUndefined() && valTune.isString())
		key = Strumento::findTune(valTune.toString.toStdString());
}

void Viola::saveData(QJsonObject& obj) const {
	Arco::saveData(obj);

	obj[json_tune] = Strumento::tuneToString(key);
}
