#pragma once
#include "strumento.h"

class Corda: virtual public Strumento { 
     static const QString json_strings;
     unsigned int strings;		// Numero di corde dello strumento
public:
     Corda(unsigned int = 4);	/* Ci sono pochi strumenti a corda con
				 * meno di quattro corde, quasi
				 * nessuno, per ragioni storiche molti
				 * invece avevano 4 corde */

     unsigned int getStringsNumber() const;
     void setStringsNumber(unsigned int);

     void loadData(const QJsonObject& obj);
     void saveData(QJsonObject& obj) const;

     bool operator==(const Corda&) const;
     bool operator!=(const Corda&) const;
};
