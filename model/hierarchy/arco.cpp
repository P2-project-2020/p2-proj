#include "arco.h"
const QString Arco::json_lutherie = "luteria"
	
Arco::Arco(bool _lutherie):lutherie(_lutherie){}

void Arco::saveData(QJsonObject& obj) const {
	Strumento::saveData(obj);

	obj[json_lutherie] = lutherie;
}

void Arco::loadData(const QJsonObject& obj){
	Strumento::loadData(obj);

	const QJsonValueRef val = obj[json_lutherie];
	if(!val.isUndefined() && val.isBool()){
		lutherie = obj[json_lutherie].toBool();
		setBrand(Strumento::lutherie);
	}
}
