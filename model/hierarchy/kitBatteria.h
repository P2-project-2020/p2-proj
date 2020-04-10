#pragma once
#include "percussione.h"

class KitBatteria: public Percussione{
public:
	enum Material {woodKit, plexiglasKit};
	KitBatteria(double, const std::string&, KitBatteria::Material = woodKit, bool = false, bool = false, const std::string& = "");

	std::string className() const;
	Strumento::Tune tune() const { return undefined; }
	std::string getMaterial() const;
private:
	Material material;
	bool metalSnare;
};
