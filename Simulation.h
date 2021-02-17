//
// Created by Christopher Horton on 11/1/18.
//

#include "Charge.h"
#include <SFML/Window.hpp>
#include <vector>

#ifndef ELECTRICALCHARGE_SIMULATION_H
#define ELECTRICALCHARGE_SIMULATION_H

class Simulation {
    int screenX = 0;
    int screenY = 0;
    bool paused = false;

public:

    ~Simulation();

    std::vector<Charge *> charges;

    sf::RenderWindow window;

    Simulation(int screenX, int screenY);

    void pause();

    void resume();

};


#endif //ELECTRICALCHARGE_SIMULATION_H
