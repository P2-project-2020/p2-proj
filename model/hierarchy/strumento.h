#pragma once

#include <string>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QStringList>
#include <vector>
#include <map>

class Strumento{
public:
     enum Tune {undefined, soprano, contralto, tenor, baritone, bass};
     static const std::map<Strumento::Tune, std::string> Tunes;
	
     static std::string tuneToString(const Strumento::Tune&);

     static const std::string lutherie; // serve come stringa reference in più punti del codice
     static const QString json_type; // QString sulla quale fare switch nella gestione del documento

     Strumento(double = 0, const std::string& = "", bool = false, const std::string& = "");
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
     virtual void setTune(const Strumento::Tune&);
     
     virtual std::string getMaterial() const = 0;

protected:
     static Strumento::Tune findTune(const std::string&);
     static const QString json_tune;	   // non tutti la usano ma ha senso fare una cosa consistente nel json

private:
     double price;
     std::string description;
     bool used;
     std::string brand;

     static const QString json_price;
     static const QString json_desc;
     static const QString json_used;
     static const QString json_brand;
};
