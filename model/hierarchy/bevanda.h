#ifndef BEVANDA_H
#define BEVANDA_H
#include <string>

class Bevanda{
	
	double price;
	std::string generic_name;
	std::string brand;
	
public:

	Bevanda(const std::string& _name, double _price);
	virtual ~Bevanda() = default;

	virtual double final_price() const = 0;
	
};

#endif /* BEVANDA_H */
