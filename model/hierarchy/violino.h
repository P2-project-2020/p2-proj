#pragma once
#include "arco.h"

class Violino: public Arco{
     Strumento::Tune key;
public:
     Violino(double = 0, const std::string& = Strumento::lutherie, const std::string& = "",  const std::string& = "", bool = false, unsigned int = 1);
     Strumento* clone() const;
     std::string className() const;
     
     Strumento::Tune tune() const;
     void setTune(const Strumento::Tune&);
     
     std::string getMaterial() const { return "Legno"; }

     void loadData(const QJsonObject&);
     void saveData(QJsonObject&) const;

     bool operator==(const Violino&) const;
     bool operator!=(const Violino&) const;
};
