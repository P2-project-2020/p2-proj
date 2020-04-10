#pragma once
#include <string>

class Strumento{
public:
	enum Tune {undefined, soprano, contralto, tenor, baritone, bass};
	
	Strumento(double, const std::string&, bool = false, const std::string& = std::string(""));
	virtual ~Strumento();
	
	bool isUsed() const { return used; }
	std::string getBrand() const { return brand; }
	
	virtual std::string className() const = 0;
	virtual Strumento::Tune tune() const = 0;
	virtual std::string getMaterial() const = 0;

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
