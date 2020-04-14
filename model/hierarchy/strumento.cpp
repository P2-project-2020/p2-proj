#include "strumento.h"

const std::string lutherie = "liuteria";

const QString Strumento::json_price = "prezzo";
const QString Strumento::json_desc = "descrizione";
const QString Strumento::json_used = "usato";
const QString Strumento::json_brand = "marca";

const std::string Tunes[] = {"", "soprano", "contralto", "tenore", "baritono", "basso"}; // ho letto che dovrebbe funzionare con c++11, ma mi semba anche di ricordare sia una cosa di c++14 quindi devo testare

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
	const QJsonValueRef valPrice = obj[json_price];
	const QJsonValueRef valDesc = obj[json_desc];
	const QJsonValueRef valUsed = obj[json_used];
	const QJsonValueRef valBrand = obj[json_brand];

	if(!valPrice.isUndefined() && valPrice.isDouble())
		price = valPrice.toDouble;
	if(!valDesc.isUndefined() && valDesc.isString())
		description = valDesc.toString().toStdString();
	if(!valUsed.isUndefined() && valPrice.isBool())
		used = toBool();
	if(!valBrand.isUndefined() && valPrice.isString())
		brad = valBrand.toString().toStdString();
}

void Strumento:saveData(QJsonObject& obj) const {
	obj[json_price] = price;
	obj[josn_desc] = description;
	obj[josn_used] = used;
	obj[josn_brand] = brand;
}

Strumento::Tune Strumento::findTune(const std::string& to_find){
	
}
