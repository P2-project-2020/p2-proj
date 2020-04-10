#include "fiato.h"

Fiato::Fiato(Material _material, Strumento::Tune _tune, Mouthpiece _mouthpiece):
	material(_material), instrumentTune(_tune), mouthpiece(_mouthpiece){}

Strumento::Tune Fiato::tune() const {
	return instrumentTune;
}

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
