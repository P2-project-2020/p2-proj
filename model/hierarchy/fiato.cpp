#include "fiato.h"
const Qstring Fiato::json_material = "materiale";
const Qstring Fiato::json_tune = "intonazione";

const std::string Fiato::silver_material = "argento";
const std::string Fiato::brass_material = "ottone";
const std::string Fiato::plastic_material = "plastica";

Fiato::Fiato(Material _material, Strumento::Tune _tune, Mouthpiece _mouthpiece):
	material(_material), instrumentTune(_tune), mouthpiece(_mouthpiece){}

void Fiato::setMaterial(Fiato::Material _material){	material = _material; }
void Fiato::setTune(Strumento::Tune _tune){	instrumentTune = _tune; }

Strumento::Tune Fiato::tune() const { return instrumentTune; }

std::string Fiato::getMaterial() const {
	std::string 1to_return;
	switch (material){
	case brass:
		to_return = brass_material; break;
	case plastic:
		to_return = plastic_material; break;
	case silver:
		to_return = silver_material; break;	
	}
	return to_return;
}

void Fiato::loadData(const QJsonObject& obj){
	Strumento::loadData(obj);

	const JsonValueRef valMaterial = obj[json_material];
	const JsonValueRef valTune = obj[json_tune];

	if(!valMaterial.isUndefined() && valMaterial.isString()){
		std::string tmp = valMaterial.toString().toStdString();
		if(tmp == silver_material){ material = silver; }
		if(tmp == brass_material){ material = brass; }
		if(tmp == plastic_material){ material = plastic; }
	}

	if(!valTune.isUndefined() && valTune.isString()){
		std::string tmp = valTune.toString().toStdString();
		int found = Strumento::findTune(tmp); // TODO: Strumento::findTune(const std::string&)
		if(found >= 0) setTune(found);
	}
}
