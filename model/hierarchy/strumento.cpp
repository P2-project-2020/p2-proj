#include "strumento.h"

const std::string Strumento::lutherie = "liuteria";
const QString Strumento::json_type = "strumento";
const QString Strumento::json_tune = "intonazione"; // Questa non viene gestita direttamente da Strumento dato che molti figli non la usano
const QString Strumento::json_price = "prezzo";
const QString Strumento::json_desc = "descrizione";
const QString Strumento::json_used = "usato";
const QString Strumento::json_brand = "marca";

const std::map<Strumento::Tune, std::string> Strumento::Tunes = {{Strumento::undefined, ""},
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
	obj[json_type] = QString::fromStdString(className()).split(" ").at(0); // ogni classe come prima cosa ritorna il nome specifico dello strumento, poi dettagli
	obj[json_price] = price;
	obj[json_desc] = QString::fromStdString(description);
	obj[json_used] = used;
	obj[json_used] = QString::fromStdString(brand);
}

Strumento::Tune Strumento::findTune(const std::string& to_find){
	for(const auto& it : Tunes)
		if(it.second == to_find) return it.first;
	return undefined;
}

// dato che richiede uno Strumrnto::Tune non serve fare find() sulla mappa, cose diverse da un Tune non dovrebbero funzionare
std::string Strumento::tuneToString(const Strumento::Tune& to_find){
	return Tunes.at(to_find);
}
