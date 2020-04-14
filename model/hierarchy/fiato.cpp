#include "fiato.h"

Fiato::Fiato(Material _material, Strumento::Tune _tune, Mouthpiece _mouthpiece):
	material(_material), instrumentTune(_tune), mouthpiece(_mouthpiece){}

void Fiato::setMaterial(Fiato::Material _material){	material = _material; }
void Fiato::setTune(Strumento::Tune _tune){	instrumentTune = _tune; }

Strumento::Tune Fiato::tune() const { return instrumentTune; }

std::string Fiato::getMaterial() const {
	std::string to_return;
	switch (material){
	case brass:
		to_return = "Legno"; break;
	case plastic:
		to_return = "Plastica"; break;
	case silver:
		to_return = "Argento"; break;	
	}
	return to_return;
}
