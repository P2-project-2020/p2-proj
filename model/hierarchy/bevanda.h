#ifndef BEVANDA_H
#define BEVANDA_H
#include "bar.h"
#include <string>

class Bevanda {
protected:
	double prezzo;
	std::string nome_generico;
public:
	Bevanda(const std::string& nome, double prezzo);
	virtual ~Bevanda() = default;
	
};

#endif /* BEVANDA_H */
