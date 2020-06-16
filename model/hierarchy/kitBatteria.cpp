#include "kitBatteria.h"
const std::vector<std::string> KitBatteria::materials = {"legno", "plexiglas"};
const QString KitBatteria::json_material = "materiale";
const QString KitBatteria::json_snare = "rullante in metallo";

KitBatteria::KitBatteria(double _price, const std::string& _brand, int _material, bool _metalSnare, bool _used, const std::string& _desc, unsigned int _quantity):
     Strumento(_price, _brand, _used, _desc, _quantity),
     Percussione(false),
     material(_material),
     metalSnare(_metalSnare){}

Strumento* KitBatteria::clone() const {
     return new KitBatteria(*this);
}
std::string KitBatteria::className() const {
     return std::string("Batteria");
}

std::string KitBatteria::getMaterial() const {
     return materials[material];
}

void KitBatteria::setMaterial(int new_material){
     if(new_material >= 0 && new_material < materials.size())
	  material = new_material;
}

int KitBatteria::findMaterial(const std::string& str){
     for(int i=0; i < materials.size(); ++i){
	  if(str == materials.at(i)) return i;
     }
     return -1;
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

     obj[json_material] = QString::fromStdString(KitBatteria::materials.at(material));
     obj[json_snare] = metalSnare;
}

bool KitBatteria::operator==(const KitBatteria& other) const {
     return
	  Percussione::operator==(other) &&
	  material == other.material &&
	  metalSnare == other.metalSnare;
}

bool KitBatteria::operator!=(const KitBatteria& other) const {
     return !(*this == other);
}
