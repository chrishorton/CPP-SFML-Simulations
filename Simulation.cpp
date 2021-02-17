//
// Created by Christopher Horton on 11/1/18.
//

#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include <iostream>

Simulation::Simulation(int screenX, int screenY) : screenX(screenX), screenY(screenY) {

    window.create(sf::VideoMode(screenX, screenY), "Charged Particles Simulation");
    window.setFramerateLimit(30);

    while (window.isOpen()) {

        // Simulation loop
        window.clear();

        for (int i = 0; i < this->charges.size(); ++i) {

            sf::CircleShape currCircle = charges[i]->getCircle();
            Charge *currCharge = charges[i];


            currCharge->calculateTotalForce(charges, i);

            if (currCharge->x + currCharge->radius > this->screenX || currCharge->x < 0) {
                currCharge->xVelocity = -currCharge->xVelocity;
            }
            if (currCharge->y + currCharge->radius > this->screenY || currCharge->y < 0) {
                currCharge->yVelocity = -currCharge->yVelocity;
            }

            currCharge->x += currCharge->xVelocity;
            currCharge->y += currCharge->yVelocity;

            currCircle.move(currCharge->xVelocity, currCharge->yVelocity);

            window.draw(currCircle);

        }

        window.display();

        sf::Event event;

        while (window.pollEvent(event)) {

            switch (event.type) {
                case event.MouseButtonReleased:

                    if (event.mouseButton.button == sf::Mouse::Left) {

                        Charge *charge = new Charge('+', 20, event.mouseButton.x, event.mouseButton.y,
                                                    sf::Color(100, 250, 50), 100, 1);
                        this->charges.push_back(charge);

                    } else if (event.mouseButton.button == sf::Mouse::Right) {

                        Charge *charge = new Charge('-', 20, event.mouseButton.x, event.mouseButton.y,
                                                    sf::Color(200, 200, 100), 100, -1);
                        this->charges.push_back(charge);

                    }
                    break;

                case sf::Event::Closed:

                    window.close();
                    break;

                case sf::Event::KeyPressed:

                    window.clear();
                case sf::Event::LostFocus:

                    this->pause();
                    break;

                case sf::Event::GainedFocus:

                    this->resume();
                    break;

                    case sf::Event::Resized:
                        this->screenX = event.size.width;
                        this->screenY = event.size.height;
                        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                        window.setView(sf::View(visibleArea));
                        break;
            }
        }
    }
}

void Simulation::pause() {
    this->paused = true;
}

void Simulation::resume() {
    this->paused = false;
}

Simulation::~Simulation() {

    for (int i = 0; i < charges.size(); ++i) {
        delete charges[i];
    }

}

