#pragma once
#include "strumento.h"

class Corda: virtual public Strumento { // derivazione virtuale && calsse astratta => non dovrà mai occuparsi di costruire Strumento
	static const QString json_strings;
	unsigned int strings;		// Numero di corde dello strumento
public:
    Corda(unsigned int);
    //Corda(double, const std::string&, const std::string&, bool, unsigned int);
	unsigned int getStringsNumber() const;
	void setStringsNumber(unsigned int);

	void loadData(const QJsonObject& obj);
	void saveData(QJsonObject& obj) const;
};
