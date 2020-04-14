#pragma once
#include "strumento.h"

class Fiato: virtual public Strumento{
protected:
	enum Mouthpiece {woodwind_mouthpiece, brass_mouthpiece};
	
public:
	enum Material {silver, brass, plastic};

	void setMaterial(Fiato::Material);
	void setTune(Strumento::Tune);
	
	Fiato(Material, Strumento::Tune, Mouthpiece);
	Strumento::Tune tune() const;
	std::string getMaterial() const;

	void loadData(const QJsonObject&);
	void saveData(QJosnObject&) const;
private:
	Mouthpiece mouthpiece;
	Material material;
	Tune instrumentTune;

	static const QString json_material;
	static const QString json_tune;

	static const std::string silver_material;
	static const std::string brass_material;
	static const std::string plastic_material;
};
