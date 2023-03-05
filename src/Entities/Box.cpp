#include <SFML/Graphics.hpp>
#include <chrono>
#include "../../include/Particle/Particle.hpp"

class Box : public Particle{
    public:
        sf::RectangleShape particle_property;
    public:
        Box(){
            //...
        }
        void update(float dt){
            //...
        }

        void render(sf::RenderTarget* target){
            target->draw(this->particle_property);
        }
};