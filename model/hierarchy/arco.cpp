#include "arco.h"
const QString Arco::json_lutherie = "luteria";
	
Arco::Arco(bool _lutherie):lutherie(_lutherie){}

/*Arco::Arco(double _price, const std::string& _brand, const std::string& _desc, bool _used, bool _lutherie):
    Strumento(_price ,_brand, _used, _desc), lutherie(_lutherie){}*/

void Arco::saveData(QJsonObject& obj) const {
	Strumento::saveData(obj);

	obj[json_lutherie] = lutherie;
}

void Arco::loadData(const QJsonObject& obj){
	Strumento::loadData(obj);

	const QJsonValue& val = obj[json_lutherie];
	if(!val.isUndefined() && val.isBool()){
		lutherie = obj[json_lutherie].toBool();
		setBrand(Strumento::lutherie);
	}
}
