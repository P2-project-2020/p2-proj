#ifndef BEVANDA_H
#define BEVANDA_H
#include <string>

class Bevanda{
	
	double prezzo;
	std::string nome_generico;

public:

	Bevanda(const std::string& nome, double prezzo);
	virtual ~Bevanda() = default;

	virtual double prezzo_finale() const = 0;
	
};

#endif /* BEVANDA_H */
