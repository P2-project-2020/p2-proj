#pragma once

#include <string>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>

class Strumento{
public:
	enum Tune {undefined, soprano, contralto, tenor, baritone, bass};
	static const std::string Tunes[];
	
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

	virtual void loadData(const QJsonObject&);
	virtual void saveData(QJsonObject&) const;
	
	virtual std::string className() const = 0;
	virtual Strumento::Tune tune() const = 0;
	virtual std::string getMaterial() const = 0;

protected:
	static Strumento::Tune findTune(const std::string&);
private:
	double price;
	std::string description;
	bool used;
	std::string brand;

	static const QString json_price;
	static const QString json_desc;
	static const QString json_used;
	static const QString json_brand;

	static const std::string lutherie; // serve come stringa reference in più punti del codice, ma non so se sia buona pratica
};
