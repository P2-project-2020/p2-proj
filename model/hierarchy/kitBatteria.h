#pragma once
#include "percussione.h"

class KitBatteria: public Percussione{
public:
     static const std::vector<std::string> materials;
	
     KitBatteria(double = 0, const std::string& = "", int = 0, bool = false, bool = false, const std::string& = "", unsigned int = 1);

     std::string className() const;
     Strumento::Tune tune() const { return undefined; }
     std::string getMaterial() const;
     void setMaterial(int);

     void loadData(const QJsonObject&);
     void saveData(QJsonObject&) const;

     static int findMaterial(const std::string&);
     
private:
     int material;
     bool metalSnare;
	
     static const QString json_material;
     static const QString json_snare;
};
