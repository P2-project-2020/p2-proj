#pragma once
#include <string>

class Strumento{
public:
	enum Tune {undefined = 0x0, soprano = 0x1, contralto = 0x2, tenor = 0x3, baritone = 0x4, bass = 0x5};

	Strumento(double, const std::string&, bool = false, const std::string& = std::string(""));
	virtual ~Strumento();
	
	bool isUsed() const { return used; }
	std::string getBrand() const { return brand; }
	
	virtual std::string className() const = 0;
	virtual Strumento::Tune tune() const = 0;

	double getPrice() const;
	void setPrice(double);

	std::string getDescription() const;
	void setDescription(const std::string&);

private:
	double price;
	std::string description;
	bool used;
	std::string brand;
};
