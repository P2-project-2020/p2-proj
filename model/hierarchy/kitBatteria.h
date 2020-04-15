#pragma once
#include "percussione.h"

class KitBatteria: public Percussione{
public:
	enum Material {woodKit, plexiglasKit};
	KitBatteria(double, const std::string&, KitBatteria::Material = woodKit, bool = false, bool = false, const std::string& = "");

	std::string className() const;
	Strumento::Tune tune() const { return undefined; }
	std::string getMaterial() const;

	void loadData(const QJsonObject&);
	void saveData(QJsonObject&) const;
private:
	Material material;
	bool metalSnare;

	std::vector<std::string> materials;
	KitBatteria::Material findMaterial(const std::string&);
	std::string materialToString(const KitBatteria::Material&);
	
	static const QString json_material;
	static const QString json_snare;
};
