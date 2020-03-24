#ifndef ALCOLICO_H
#define ALCOLICO_H
#include "bevanda.h"

class Alcolico: virtual public Bevanda{

	float grado;
	
public:

	Alcolico(std::string _nome, double _prezzo, float _grado);
	Alcolico(std::string _nome, std::string _brand, double _prezzo, float _grado);

	double percentualeAlcol() const;
	std::string getNome() const;
	double getPrezzo() const;
	std::string dettaglio() const;
};

#endif /* ALCOLICO_H */
