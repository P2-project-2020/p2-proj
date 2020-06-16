#pragma once
#include "arco.h"

class Viola: public Arco{
	
     Strumento::Tune key;
	
public:
	
     Viola(double = 0, const std::string& = Strumento::lutherie, const std::string& = "", Strumento::Tune = contralto ,bool = false);
     Strumento* clone() const;
     std::string className() const;

     Strumento::Tune tune() const;
     void setTune(const Strumento::Tune&);
     
     std::string getMaterial() const { return "Legno"; }

     void loadData(const QJsonObject&);
     void saveData(QJsonObject&) const;
};
