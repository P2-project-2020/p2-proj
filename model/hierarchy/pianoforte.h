#pragma once
#include "percussione.h"
#include "corda.h"

class Pianoforte: public Corda, public Percussione{
public:
     static const std::vector<std::string> shapes;
     static const std::vector<std::string> keys;

     static int findShape(const std::string&);
     static int findKeys(const std::string&);
	
     Pianoforte(int = 0, int = 2, double = 0, const std::string& = "",  const std::string& = "",  bool = false, const std::string& = "", unsigned int = 1);
     Strumento* clone() const;

     std::string className() const;
     Strumento::Tune tune() const { return undefined; }
     
     std::string getMaterial() const;
     void setMaterial(int);
     void setMaterial(const std::string&);
     const std::vector<std::string>* getMaterialVector() const;

     void loadData(const QJsonObject& obj);
     void saveData(QJsonObject& obj) const;

     bool operator==(const Pianoforte&) const;
     bool operator!=(const Pianoforte&) const;

private:
     int pianoShape;
     int pianoKeys;
	
     static const unsigned int numberOfKeys;
	
     static const QString json_shape;
     static const QString json_keys;
};
