#pragma once
#include "strumento.h"

class Fiato: virtual public Strumento{
protected:
	enum Mouthpiece {woodwind_mouthpiece, brass_mouthpiece};
	// Vedere se serve davvero, non si usa da nessuna parte
public:
	enum Material {silver, brass, plastic};
	static const std::map<Fiato::Material,std::string> materials;
	
	void setMaterial(Fiato::Material);
	void setTune(Strumento::Tune);
	
	Fiato(Material = brass, Strumento::Tune = soprano, Mouthpiece = brass_mouthpiece);
	Strumento::Tune tune() const;
	std::string getMaterial() const;

	void loadData(const QJsonObject&);
	void saveData(QJsonObject&) const;

private:
	Mouthpiece mouthpiece;
	Material material;
	Tune instrumentTune;

	static const QString json_material;
	static const QString json_tune;

	static std::string materialToString(const Fiato::Material&);
	static Fiato::Material findMaterial(const std::string&);
};
