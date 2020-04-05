#pragma once
#include <string>

class Strumento{
public:
	enum Tune {undefined = 0x0, sporano = 0x1, contralto = 0x2, tenor = 0x3, baritone = 0x4, bass = 0x5};

	Strumento(double, const std::string&, bool = false, Strumento::Tune = undefined);
	virtual ~Strumento();
	
	bool isUsed() const { return used; }
	std::string getBrand() const { return brand; }

	virtual std::string userDescription() const = 0;
	virtual std::string className() const = 0;
	virtual Strumento::Tune tune() const = 0;

protected:
	double price;
	
private:
	bool used;
	std::string brand;
	Tune instrumentTune;
};
