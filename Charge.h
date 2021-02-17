//
// Created by Christopher Horton on 11/1/18.
//
#include <SFML/Graphics.hpp>
#include <vector>

#ifndef ELECTRICALCHARGE_CHARGE_H
#define ELECTRICALCHARGE_CHARGE_H


class Charge {

public:

    char charge;
    int chargeMultiplier = 0;
    int radius = 2;
    float x = 0;
    float y = 0;
    int pointCount = 100;
    const sf::Color fillColor;
    float xVelocity = 0;
    float yVelocity = 0;
    double chargeSize = 0;
    std::vector<std::vector<double>> forces;
    std::vector<double> totalForce;

    void calculateTotalForce(std::vector<Charge *> charges, int currIndex);

    std::vector<double> averageForces();

    std::vector<double> calculateForce(Charge *c2);

    sf::CircleShape getCircle();

    Charge(char charge, int radius, int x, int y, const sf::Color &fillColor, int pointCount, int chargeMultiplier);

    Charge();

    ~Charge();

};


#endif //ELECTRICALCHARGE_CHARGE_H
