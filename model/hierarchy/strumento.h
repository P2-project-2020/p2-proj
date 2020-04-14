#pragma once

#include <string>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>

class Strumento{
public:
	enum Tune {undefined, soprano, contralto, tenor, baritone, bass};
	
	Strumento(double, const std::string&, bool = false, const std::string& = std::string(""));
	virtual ~Strumento();
	
	bool isUsed() const;
	void setUsed(bool = true);

	std::string getBrand() const;
	void setBrand(const std::string&);
	
	double getPrice() const;
	void setPrice(double);

	std::string getDescription() const;
	void setDescription(const std::string&);

	virtual std::string className() const = 0;
	virtual Strumento::Tune tune() const = 0;
	virtual std::string getMaterial() const = 0;
	virtual void loadData(const QJsonObject&) = 0;
	virtual void saveData(QJsonObject&) const = 0;

private:
	double price;
	std::string description;
	bool used;
	std::string brand;
};
