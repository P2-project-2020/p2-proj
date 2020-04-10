#include "kitBatteria.h"

KitBatteria::KitBatteria(double _price, const std::string& _brand, KitBatteria::Material _material, bool _metalSnare, bool _used, const std::string& _desc):
	Strumento(_price, _brand, _used, _desc), Percussione(false), material(_material), metalSnare(_metalSnare){}

std::string KitBatteria::className() const {
	return std::string("Batteria ") + (metalSnare ? " con rullante in metallo" : "");
}

std::string KitBatteria::getMaterial() const {
	return (material == woodKit ? "Legno" : "Plexiglas");
}
