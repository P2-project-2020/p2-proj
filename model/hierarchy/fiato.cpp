#include "fiato.h"

Fiato::Fiato(Material _material, Strumento::Tune _tune, Mouthpiece _mouthpiece):
	material(_material), instrumentTune(_tune), mouthpiece(_mouthpiece){}

Strumento::Tune Fiato::tune() const {
	return instrumentTune;
}

