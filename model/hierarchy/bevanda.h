#ifndef BEVANDA_H
#define BEVANDA_H
#include "prodotto.h"
#include <string>

class Bevanda: virtual public Prodotto{
	
	std::string brand;
	double volume;
	bool hot;
	bool frizzante;

	static double soglia_superalcolico; // buona pratica per le constanti per Ranzo
	
public:

	Bevanda(const std::string& _brand, double _price, const std::string& _nome_generico_);

	/* Ha anchesenso per i coctail dove la parte di alcol dipende da quanto alcolico c'è*/
	virtual double percentualeAlcol() const = 0;
	/* Questo lo possiamo implementare già qui in modo che guardi il metodo sopra e decida
	   rispetto la soglia */
	bool isSuperalcolico() const;
};

double Bevanda::soglia_superalcolico = 40;

#endif /* BEVANDA_H */
