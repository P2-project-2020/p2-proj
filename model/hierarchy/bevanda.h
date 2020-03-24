#ifndef BEVANDA_H
#define BEVANDA_H
#include "prodotto.h"
#include <string>

class Bevanda: public Prodotto{
	
	std::string brand;
	double volume;
	bool hot;
	bool frizzante;

	static double sogliaSuperalcolico; // buona pratica per le constanti per Ranzo
	
public:
	
	// Il distruttore è già virtuale per Prodotto
	Bevanda(); // Per ora tengo quello vuoto, sennò diventa bloat subito

	/* Ha anche senso per i coctail dove la parte di alcol dipende da quanto alcolico c'è*/
	virtual double percentualeAlcol() const = 0;
	/* Questo lo possiamo implementare già qui in modo che guardi il metodo sopra e decida
	   rispetto la soglia */
	bool isSuperalcolico() const;
};

double Bevanda::sogliaSuperalcolico = 40;

#endif /* BEVANDA_H */
