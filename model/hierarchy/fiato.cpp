#include "fiato.h"
const QString Fiato::json_material = "materiale";
const QString Fiato::json_tune = "intonazione";

const std::map<Fiato::Material, std::string> Fiato::materials = {{Fiato::brass, "bronzo"},
																 {Fiato::silver,"argento"},
																 {Fiato::plastic, "plastica"}};

Fiato::Fiato(Material _material, Strumento::Tune _tune, Mouthpiece _mouthpiece):
	mouthpiece(_mouthpiece), material(_material), instrumentTune(_tune) {}

void Fiato::setMaterial(Fiato::Material _material){	material = _material; }

void Fiato::setTune(Strumento::Tune _tune){	instrumentTune = _tune; }

Strumento::Tune Fiato::tune() const { return instrumentTune; }

std::string Fiato::getMaterial() const {
	return Fiato::materialToString(material);
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

	obj[json_material] = QString::fromStdString(Fiato::materialToString(material));
	obj[json_tune] = QString::fromStdString(Strumento::tuneToString(instrumentTune));
}

std::string Fiato::materialToString(const Fiato::Material& _material){
	return materials[_material];
}

Fiato::Material Fiato::findMaterial(const std::string& str){
	for(const auto& mat : materials){
		if(mat.second == str) return mat.first;
	}
	return materials.begin()->first;
}
