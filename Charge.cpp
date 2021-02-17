//
// Created by Christopher Horton on 11/1/18.
//

#include <math.h>
#include "Charge.h"
#include <iostream>
#include "Simulation.h"
#include <vector>

Charge::~Charge() {

    // What if we made the charges a linked list??????
    // That would take away the complexity of charges vector?

}

sf::CircleShape Charge::getCircle() {

    sf::CircleShape circle(radius);
    circle.setRadius(radius);
    circle.setPointCount(100);
    circle.setFillColor(fillColor);
    circle.setPosition(x, y);

    return circle;
}

Charge::Charge(char charge, int radius, int x, int y, const sf::Color &fillColor, int pointCount, int chargeMultiplier)
        : charge(charge),
          radius(radius),
          x(x),
          y(y),
          fillColor(fillColor),
          pointCount(pointCount), chargeMultiplier(chargeMultiplier) {
    if (charge == '-') {
        this->chargeSize = -500;
    } else {
        this->chargeSize = 500;
    }
}


std::vector<double> Charge::calculateForce(Charge *c2) {
    double chargeProducts = (this->chargeSize * c2->chargeSize) / (4 * M_PI);

    double xDistance = (this->x - c2->x);
    double yDistance = (this->y - c2->y);

    double xResult = (xDistance)/abs(xDistance*xDistance*xDistance);
    double yResult = (yDistance)/abs(yDistance*yDistance*yDistance);

    // this returns the directional unit vector multiplied by charge products scalar to give force vector on charge
    std::vector<double> result = {chargeProducts * xResult, chargeProducts * yResult};
    return result;
}

void Charge::calculateTotalForce(std::vector<Charge *> charges, int currIndex) {
    for (int i = 0; i < charges.size(); ++i) {

        if (charges.size() == 1) {
            continue;
        }
        if (i == currIndex)
            // skip calculating the current charge
            continue;

        this->forces.push_back(calculateForce(charges[i]));
        // Now average these forces out
    }

    if (charges.size() > 1) {
        this->totalForce = averageForces();

        this->xVelocity = totalForce[0];
        this->yVelocity = totalForce[1];
    }
    this->forces = {};

}

std::vector<double> Charge::averageForces() {

    double xComponentAccumulator=0;
    double yComponentAccumulator=0;

    for (int i = 0; i < this->forces.size(); ++i) {
            xComponentAccumulator += this->forces[i][0];
            yComponentAccumulator += this->forces[i][1];
    }
    double xAverage = xComponentAccumulator/forces.size();
    double yAverage = yComponentAccumulator/forces.size();
    return {xAverage, yAverage};
}






























