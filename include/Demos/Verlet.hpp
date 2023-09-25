#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
// #include "../../src/logic/Operation.h"
// #include "../../src/Entities/Ball.cpp"
// #include "../../src/Entities/Line.cpp"
#include "../../src/logic/CollisionDetectionOperation.h"

class Verlet{
    private:
        //line(stick) container
        std::vector<Line> lines;
        //projectile container
        std::vector<Ball> projectiles;

        //ball movement related
        sf::Vector2f ball1_position;
        sf::Vector2f ball2_position;

        //attachment related variables
        float length = 20.f;
        float length_for_four = 40.f;
        Line tail;

        // instantiating objects
        CollisionDetectionOperation cod;
    public:
        //ball container
        std::vector<Ball> balls;
    public:
        Verlet();

        //custom function
        void createBall(sf::Vector2f mouse_position);
        void createLine();
        void lineAlign();
        void resolveCaller();
        void resolveCollision();
        void distanceResolver(Ball ball1, Ball ball2);
        void distanceResolverForFour(Ball ball1, Ball ball2);
        void selection(sf::Vector2f mouse_position);
        void pinning(sf::Vector2f mouse_position);
        void controlBall(sf::Vector2f mouse_position);
        void shootProjectiles(sf::Vector2f mouse_position);

        //integrator and displayer
        void update(float dt);
        void render(sf::RenderTarget* target);
};