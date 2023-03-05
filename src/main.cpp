#include "../include/Engine/Engine.h"

float dt;

int main()
{
    //instantiating object
    Engine engine;
    sf::Clock clock;

    //engine loop
    while(engine.running()){

        dt = clock.restart().asSeconds();

        //update frame by frame
        engine.update(dt);
        //render frame
        engine.render();
    }

    return 0;
}