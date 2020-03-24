#ifndef DRINK_H
#define DRINK_H
#include "analcolico.h"
#include "alcolico.h"

class Drink: public Alcolico, public Analcolico {
public:
	Drink(std::string _name, double _prezzo);

	double percentualeAlcol() const;
	std::string getNome() const;
	std::string dettaglio() const;
	double getPrezzo() const;
	
}; 

#endif /* DRINK_H */
