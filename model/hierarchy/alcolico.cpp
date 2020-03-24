#include "alcolico.h"

Alcolico::Alcolico(double _grado):
	Bevanda(),
	grado(_grado){}

double Alcolico::percentualeAlcol() const {
	return grado;
}

std::string Alcolico::getNome() const {
	return (brand.length() ? brand : nome); 		// Hai ragione, sono privati...
}

double Alcolico::getPrezzo() const {				
	return prezzo;									// pure questo
}
std::string Alcolico::dettaglio() const {
	return getNome() + "\n" + getDescrizione() +"\n" + getPrezzo();
    /* molto provvisiorio, ma magari potrebbe essere un'idea, fare tutto con metodi get?
	   se poi ci servono anche i set però tantovale avere i campi protetti */
}
