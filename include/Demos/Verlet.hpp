#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../src/logic/Operation.h"
#include "../../src/Entities/Ball.cpp"
#include "../../src/Entities/Line.cpp"

class Verlet{
    private:
        //ball container
        std::vector<Ball> balls;
        //line(stick) container
        std::vector<Line> lines;

        //ball movement related
        sf::Vector2f ball1_position;
        sf::Vector2f ball2_position;

        //attachment related variables
        float length = 20.f;
        float length_for_four = 40.f;
        Line tail;

    public:
        Verlet();

        //custom function
        void createBall(sf::Vector2f mouse_position);
        void createLine();
        void lineAlign();
        void resolveCaller();
        void distanceResolver(Ball ball1, Ball ball2);
        void distanceResolverForFour(Ball ball1, Ball ball2);
        void selection(sf::Vector2f mouse_position);
        void pinning(sf::Vector2f mouse_position);
        void controlBall(sf::Vector2f mouse_position);

        //integrator and displayer
        void update(float dt);
        void render(sf::RenderTarget* target);
};