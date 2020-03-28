#ifndef DRINK_H
#define DRINK_H
#include "analcolico.h"
#include "alcolico.h"

class Drink: public Alcolico, public Analcolico {
	double percentualeParteAlcolica, percentualeParteAnalcolica;
public:
	
	Drink(const std::string& _nome, double _prezzo, double _grado = 0, double _zucchero = 0);
	double percentualeAlcol() const;
	std::string getNome() const;
	std::string dettaglio() const;
	double getPrezzo() const;
	
}; 

#endif /* DRINK_H */
