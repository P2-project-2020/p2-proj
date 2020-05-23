#pragma once
#include "percussione.h"

class KitBatteria: public Percussione{
public:
	enum Material {woodKit, plexiglassKit};
	KitBatteria(double = 0, const std::string& = "", KitBatteria::Material = woodKit, bool = false, bool = false, const std::string& = "");

	std::string className() const;
	Strumento::Tune tune() const { return undefined; }
	std::string getMaterial() const;

	void loadData(const QJsonObject&);
	void saveData(QJsonObject&) const;
private:
	Material material;
	bool metalSnare;

	static const std::map<KitBatteria::Material,std::string> materials;

	static KitBatteria::Material findMaterial(const std::string&);
	static std::string materialToString(const KitBatteria::Material&);
	
	static const QString json_material;
	static const QString json_snare;
};
