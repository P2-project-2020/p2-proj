#pragma once
#include "arco.h"

class Viola: public Arco{
	
     Strumento::Tune key;
	
public:
	
     Viola(double = 0, const std::string& = Strumento::lutherie, const std::string& = "", const std::string& = "", Strumento::Tune = contralto ,bool = false, unsigned int = 1, const std::string& = "");
     Strumento* clone() const;
     std::string className() const;

     Strumento::Tune tune() const;
     void setTune(const Strumento::Tune&);
     
     std::string getMaterial() const { return "Legno"; }

     void loadData(const QJsonObject&);
     void saveData(QJsonObject&) const;

     bool operator==(const Viola&) const;
     bool operator!=(const Viola&) const;
     
};
