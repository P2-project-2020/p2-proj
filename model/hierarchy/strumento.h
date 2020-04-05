#pragma once
#include <string>

class Strumento{
private:
	bool used;
	std::string brand;
protected:
	double price;
public:
	
	enum Tune {sporano, contralto, tenor, baritone, bass};
	
	Strumento(double, const std::string&, bool = false);
	virtual ~Strumento();
	
	bool isUsed() const { return used; }
	std::string getBrand() const { return brand; }

	virtual std::string description() const = 0;
	virtual std::string className() const = 0;
	virtual Strumento::Tune tune() const = 0;
};
