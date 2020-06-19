#include "strumento.h"

const std::string Strumento::lutherie = "liuteria";
const QString Strumento::json_type = "strumento";
const QString Strumento::json_tune = "intonazione"; // Questa non viene gestita direttamente da Strumento dato che molti figli non la usano
const QString Strumento::json_price = "prezzo";
const QString Strumento::json_desc = "descrizione";
const QString Strumento::json_used = "usato";
const QString Strumento::json_brand = "marca";
const QString Strumento::json_model = "modello";

const std::map<Strumento::Tune, std::string> Strumento::Tunes = {{Strumento::undefined, ""},
								 {Strumento::soprano, "soprano"},
								 {Strumento::contralto, "contralto"},
								 {Strumento::tenor, "tenore"},
								 {Strumento::baritone, "baritono"},
								 {Strumento::bass, "basso"}};

Strumento::Strumento(double _price, const std::string& _brand, bool _used, const std::string& _desc, unsigned int _quantity, const std::string& _model):
     price(_price),
     description(_desc),
     used(_used),
     brand(_brand),
     model(_model),
     quantity(_quantity){}

Strumento::~Strumento() = default;

bool Strumento::isUsed() const { return used; }

void Strumento::setUsed(bool _used) { used = _used; }

std::string Strumento::getBrand() const { return brand; }

void Strumento::setBrand(const std::string& _brand){ brand = _brand; }

std::string Strumento::getModel() const { return model; }

void Strumento::setModel(const std::string& _model){ model = _model; }


double Strumento::getPrice() const {
     return price;
}

void Strumento::setPrice(double _price) {
     if(_price >= 0)
	  price = _price;
}

std::string Strumento::getDescription() const {
     return description;
}

void Strumento::setDescription(const std::string& _desc) {
     description = _desc;
}

unsigned int Strumento::getQuantity() const { return quantity; }

void Strumento::setQuantity(unsigned int newQty){
     quantity = newQty;
}

void Strumento::loadData(const QJsonObject& obj){
     const QJsonValue& valPrice = obj[json_price];
     const QJsonValue& valDesc = obj[json_desc];
     const QJsonValue& valUsed = obj[json_used];
     const QJsonValue& valBrand = obj[json_brand];
     const QJsonValue& valModel = obj[json_model];

     if(!valPrice.isUndefined() && valPrice.isDouble())
	  price = valPrice.toDouble();
     if(!valDesc.isUndefined() && valDesc.isString())
	  description = valDesc.toString().toStdString();
     if(!valUsed.isUndefined() && valPrice.isBool())
	  used = valUsed.toBool();
     if(!valBrand.isUndefined() && valPrice.isString())
	  brand = valBrand.toString().toStdString();
     if(!valModel.isUndefined() && valModel.isString())
	  model = valModel.toString().toStdString();

}

void Strumento::saveData(QJsonObject& obj) const {
     obj[json_type] = QString::fromStdString(className()).split(" ").at(0);
     obj[json_price] = price;
     obj[json_desc] = QString::fromStdString(description);
     obj[json_used] = used;
     obj[json_brand] = QString::fromStdString(brand);
     obj[json_model] = QString::fromStdString(model);
}

Strumento::Tune Strumento::findTune(const std::string& to_find){
     for(const auto& it : Tunes)
	  if(it.second == to_find) return it.first;
     return undefined;
}

void Strumento::setTune(const Strumento::Tune& new_tune){
     return;
     /* La maggior parte delle volte gli strumenti non hanno intonazione, e comunque
	lascio decidere alla classe finale cosa fare */
}

void Strumento::setMaterial(int){
     return; // stesso discorso per i materiali
}

void Strumento::setMaterial(const std::string& new_material){
     return; // stesso discorso per i materiali
}

const std::vector<std::string>* Strumento::getMaterialVector() const {
     return nullptr;
     /* Così di default ritorna nullptr, a meno che una sottoclasse
      * non lo overridi ritornando il proprio vettore di materiali */
}

bool Strumento::operator==(const Strumento& other) const {
     return
	  price == other.price &&
	  used == other.used &&
	  brand == other.brand &&
	  model == other.model;
     /* Credo non abbia senso mettere l'uguaglianza anche sulla
      * quantità e la descrizione, visto che sono estremamente
      * variabili (tra l'altro se facciamo un oggetto unico che deve
      * essere aggiunto a una collezione non è molto funzionale)
      */
}

bool Strumento::operator!=(const Strumento& other) const {
     return !(*this == other);
}
