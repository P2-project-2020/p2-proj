#pragma once
#include <string>

class Tunes{
	class Tune{
		std::string name;
	public:
		Tune(const std::string&);
		std::string toString();
	};
public:
	Tunes();
};
