#include "fiato.h"

Fiato::Fiato(Material _material, Strumento::Tune _tune, Mouthpiece _mouthpiece, double _price, const std::string& _brand, bool _used):
	Strumento(_price, _brand, _used), material(_material), instrumentTune(_tune), mouthpiece(_mouthpiece){}

Strumento::Tune Fiato::tune() const {
	return instrumentTune;
}

