#include "sax.h"

Sax::Sax(Strumento::Tune _tune, double _price, const std::string& _brand, Fiato::Material _material, bool _used):
	Strumento(_price, _brand, _used), Fiato(_material, _tune, Fiato::woodwind_mouthpiece){}

std::string Sax::className() const{
	std::string specifier;
	if(tune())
		// undefined not handled by switch, non serve includerlo dato che l'if impone una
		// precondizine sullo switch di != da undefined
		switch (tune()){
		case soprano:
			specifier = "soprano"; break;
		case contralto:
			specifier = "contralto"; break;
		case tenor:
			specifier = "tenore"; break;
		case baritone:
			specifier = "baritone"; break;
		case bass:
			specifier = "baritone"; break;
		}
	return "Sax " + specifier;
}
