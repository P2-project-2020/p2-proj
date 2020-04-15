#include "strumento.h"

const std::string Strumento::lutherie = "liuteria";

const QString Strumento::json_price = "prezzo";
const QString Strumento::json_desc = "descrizione";
const QString Strumento::json_used = "usato";
const QString Strumento::json_brand = "marca";

const std::vector<std::pair<Strumento::Tune, std::string>> Strumento::Tunes = {{Strumento::undefined, ""},
																			   {Strumento::soprano, "soprano"},
																			   {Strumento::contralto, "contralto"},
																			   {Strumento::tenor, "tenore"},
																			   {Strumento::baritone, "baritono"},
																			   {Strumento::bass, "basso"}};

Strumento::Strumento(double _price, const std::string& _brand, bool _used, const std::string& _desc):
	price(_price),description(_desc),used(_used),brand(_brand){}

Strumento::~Strumento() = default;

bool Strumento::isUsed() const { return used; }

void Strumento::setUsed(bool _used) { used = _used; }

std::string Strumento::getBrand() const { return brand; }

void Strumento::setBrand(const std::string& _brand){ brand = _brand; }

double Strumento::getPrice() const {
	return price;
}

void Strumento::setPrice(double _price) {
	price = _price;
}

std::string Strumento::getDescription() const {
	return description;
}

void Strumento::setDescription(const std::string& _desc) {
	description = _desc;
}

void Strumento::loadData(const QJsonObject& obj){
	const QJsonValue& valPrice = obj[json_price];
	const QJsonValue& valDesc = obj[json_desc];
	const QJsonValue& valUsed = obj[json_used];
	const QJsonValue& valBrand = obj[json_brand];

	if(!valPrice.isUndefined() && valPrice.isDouble())
		price = valPrice.toDouble();
	if(!valDesc.isUndefined() && valDesc.isString())
		description = valDesc.toString().toStdString();
	if(!valUsed.isUndefined() && valPrice.isBool())
		used = valUsed.toBool();
	if(!valBrand.isUndefined() && valPrice.isString())
		brand = valBrand.toString().toStdString();
}

void Strumento::saveData(QJsonObject& obj) const {
	obj[json_price] = price;
	obj[json_desc] = QString::fromStdString(description);
	obj[json_used] = used;
	obj[json_used] = QString::fromStdString(brand);
}

Strumento::Tune Strumento::findTune(const std::string& to_find){
	for(const auto& _tune : Tunes){
		if(_tune.second == to_find) return _tune.first;
	}
	return undefined;
}

std::string Strumento::tuneToString(const Strumento::Tune& to_find){
	for(const auto& _tune : Tunes){
		if(_tune.first == to_find) return _tune.second;
	}
	return "";
}
