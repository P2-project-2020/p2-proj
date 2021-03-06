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

     static const std::string lutherie; // serve come stringa reference in più punti del codice
     static const QString json_type; // QString sulla quale fare switch nella gestione del documento

     Strumento(double = 0, const std::string& = "", bool = false, const std::string& = "", unsigned int = 1, const std::string& = "", const std::string& = "");
     virtual ~Strumento();
     virtual Strumento* clone() const = 0;

     bool isUsed() const;
     void setUsed(bool = true);

     std::string getBrand() const;
     void setBrand(const std::string&);

     std::string getModel() const;
     void setModel(const std::string&);
     
     double getPrice() const;
     void setPrice(double);

     std::string getDescription() const;
     void setDescription(const std::string&);

     unsigned int getQuantity() const;
     void setQuantity(unsigned int);

     bool setImgPath(const std::string&);
     std::string getImgPath() const;

     virtual void loadData(const QJsonObject&);
     virtual void saveData(QJsonObject&) const;

     virtual std::string className() const = 0;

     virtual Strumento::Tune tune() const = 0;
     virtual void setTune(const Strumento::Tune&);
     
     virtual std::string getMaterial() const = 0;
     virtual void setMaterial(int);
     virtual void setMaterial(const std::string&);
     virtual const std::vector<std::string>* getMaterialVector() const;

     static Strumento::Tune findTune(const std::string&);

     bool operator==(const Strumento&) const;
     bool operator!=(const Strumento&) const;

protected:
     static const QString json_tune;	   // non tutti la usano ma ha senso per fare una cosa consistente nel json
private:
     double price;
     std::string description;
     bool used;
     std::string brand;
     std::string model;
     std::string imgPath;
     unsigned int quantity;
     
     static const QString json_price;
     static const QString json_desc;
     static const QString json_used;
     static const QString json_brand;
     static const QString json_model;
     static const QString json_quantity;
     static const QString json_img_path;
};
