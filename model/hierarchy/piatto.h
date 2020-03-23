#ifndef PIATTO_H
#define PIATTO_H
#include <iostream>


class Piatto
{
    std::string name;
    double kcal;
    double price;


public:
    Piatto(std::string = "", double = 0, double = 0);
};

#endif // PIATTO_H
