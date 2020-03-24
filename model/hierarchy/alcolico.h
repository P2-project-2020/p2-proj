#ifndef ALCOLICO_H
#define ALCOLICO_H
#include "bevanda.h"

class Alcolico: virtual public Bevanda{

	double grado;
	
public:

	Alcolico(double _grado);

	double percentualeAlcol() const;
	std::string getNome() const;
	double getPrezzo() const;
	std::string dettaglio() const;
};

#endif /* ALCOLICO_H */
