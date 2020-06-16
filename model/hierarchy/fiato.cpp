#include "fiato.h"
const QString Fiato::json_material = "materiale";
const QString Fiato::json_tune = "intonazione";

const std::vector<std::string> Fiato::materials = { "bronzo", "argento", "plastica" };

Fiato::Fiato(int _material, Strumento::Tune _tune, Mouthpiece _mouthpiece):
	mouthpiece(_mouthpiece),
	material(_material >= 0 && _material < materials.size() ? _material : 0),
	instrumentTune(_tune) {}

Strumento::Tune Fiato::tune() const { return instrumentTune; }

void Fiato::setTune(const Strumento::Tune& new_tune){
     // if(new_tune) { // Se vogliamo che non si possa settare undefined però idk
     instrumentTune = new_tune;
     // }
}

std::string Fiato::getMaterial() const {
	return Fiato::materials.at(material);
}

void Fiato::setMaterial(int new_material) {
     if(new_material >=0 && new_material < materials.size()){
	  material = new_material;
     }
}

void Fiato::loadData(const QJsonObject& obj){
	Strumento::loadData(obj);

	const QJsonValue& valMaterial = obj[json_material];
	const QJsonValue& valTune = obj[json_tune];

	if(!valMaterial.isUndefined() && valMaterial.isString())
		material = Fiato::findMaterial(valMaterial.toString().toStdString());

	if(!valTune.isUndefined() && valTune.isString())
		setTune(Strumento::findTune(valTune.toString().toStdString()));
}

void Fiato::saveData(QJsonObject& obj) const {
	Strumento::saveData(obj);

	obj[json_material] = QString::fromStdString(Fiato::materials.at(material));
	obj[json_tune] = QString::fromStdString(Strumento::Tunes.at(instrumentTune));
}

int Fiato::findMaterial(const std::string& str){
     for(int i = 0; i < materials.size(); ++i){
	  if(str == materials.at(i))
	       return i;
     }
     return -1;
}

bool Fiato::operator==(const Fiato& other) const {
     return
	  Strumento::operator==(other) &&
	  mouthpiece == other.mouthpiece &&
	  material == other.material &&
	  instrumentTune == other.instrumentTune;
}
