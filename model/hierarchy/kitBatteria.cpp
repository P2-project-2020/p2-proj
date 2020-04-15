#include "kitBatteria.h"
const std::vector<std::pair<KitBatteria::Material,std::string>> KitBatteria::materials = {{KitBatteria::woodKit, "legno"},
																			 {KitBatteria::plexiglassKit, "plexiglas"}};
const QString KitBatteria::json_material = "materiale";
const QString KitBatteria::json_snare = "rullante in metallo";

KitBatteria::KitBatteria(double _price, const std::string& _brand, KitBatteria::Material _material, bool _metalSnare, bool _used, const std::string& _desc):
	Strumento(_price, _brand, _used, _desc), Percussione(false), material(_material), metalSnare(_metalSnare){}

std::string KitBatteria::className() const {
	return std::string("Batteria ") + (metalSnare ? "con rullante in metallo" : "");
}

std::string KitBatteria::getMaterial() const {
	return (material == woodKit ? "Legno" : "Plexiglas");
}

KitBatteria::Material KitBatteria::findMaterial(const std::string& str){
	for(const auto& mat : materials){
		if(mat.second == str)
			return mat.first;
	}
	return woodKit;
}

std::string KitBatteria::materialToString(const KitBatteria::Material& _material){
	for(const auto mat : materials)
		if(mat.first == _material) return mat.second;
	return "";
}

void KitBatteria::loadData(const QJsonObject& obj){
	Percussione::loadData(obj);

	const QJsonValue& valMaterial = obj[json_material];
	const QJsonValue& valSnare = obj[json_snare];

	if(!valMaterial.isUndefined() && valMaterial.isString())
		material = KitBatteria::findMaterial(valMaterial.toString().toStdString());
	if(!valSnare.isUndefined() && valSnare.isBool())
		metalSnare = valSnare.toBool();
}

void KitBatteria::saveData(QJsonObject& obj) const {
	Percussione::saveData(obj);

	obj[json_material] = QString::fromStdString(materialToString(material));
	obj[json_snare] = metalSnare;
}
