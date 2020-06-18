#pragma once
#include "strumento.h"

class Fiato: virtual public Strumento{

protected:
     enum Mouthpiece {woodwind_mouthpiece, brass_mouthpiece};

public:
     static const std::vector<std::string> materials;
	
     Fiato(int = 0, Strumento::Tune = soprano, Mouthpiece = brass_mouthpiece);

     Strumento::Tune tune() const;
     void setTune(const Strumento::Tune&);
     
     std::string getMaterial() const;
     void setMaterial(int);

     void loadData(const QJsonObject&);
     void saveData(QJsonObject&) const;

     static int findMaterial(const std::string&);
     const std::vector<std::string>* getMaterialVector() const;

     bool operator==(const Fiato&) const;
     bool operator!=(const Fiato&) const;

private:
     Mouthpiece mouthpiece;
     int material;
     Tune instrumentTune;

     static const QString json_material;
     static const QString json_tune;
};
