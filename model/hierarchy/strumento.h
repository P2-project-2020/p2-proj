#pragma once
#include <string>

class Strumento{
private:
	bool used;
	std::string brand;
protected:
	double price;
public:
	Strumento(double, const std::string&, bool = false);
	virtual ~Strumento();
	
	virtual bool isUsed() const { return used; }
	virtual std::string description() const = 0;
	virtual std::string className() const = 0;
	std::string getBrand() const { return brand; }
};
