#include "bevanda.h"

Bevanda::Bevanda():
	Prodotto(), volume(0), hot(false), frizzante(false)
{}

bool Bevanda::isSuperalcolico() const {
	return percentualeAlcol() >= sogliaSuperalcolico;
}
