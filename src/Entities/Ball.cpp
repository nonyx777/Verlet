#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../include/Particle/Particle.hpp"

class Ball : public Particle{
    private:
        float height = 360.f;
        float width = 640.f;

    public:
        sf::CircleShape particle_property;
        sf::Vector2f last_position = sf::Vector2f(-0.5f, -0.5f);

        //movement variables
    public:
        Ball(){
            this->acceleration = sf::Vector2f(0.f, 0.1f);
        }

        //collidion resolver
        void collisionResolve(){
            if(this->particle_property.getPosition().y > this->height){
                this->particle_property.setPosition(sf::Vector2f(this->particle_property.getPosition().x, this->height));
                this->last_position.y = this->particle_property.getPosition().y + this->velocity.y;
            }
            else if(this->particle_property.getPosition().y < 0.f){
                this->particle_property.setPosition(sf::Vector2f(this->particle_property.getPosition().x, 0.f));
                this->last_position.y = this->particle_property.getPosition().y + this->velocity.y;
            }
            if(this->particle_property.getPosition().x > this->width){
                this->particle_property.setPosition(sf::Vector2f(this->width, this->particle_property.getPosition().y));
                this->last_position.x = this->particle_property.getPosition().x + this->velocity.x;
            }
            else if(this->particle_property.getPosition().x < 0.f){
                this->particle_property.setPosition(sf::Vector2f(0.f, this->particle_property.getPosition().y));
                this->last_position.x = this->particle_property.getPosition().x + this->velocity.x;
            }
        }

        void update(float dt){
            this->collisionResolve();

            this->position = this->particle_property.getPosition();
            this->velocity = this->position - this->last_position;
            this->particle_property.move(this->velocity + this->acceleration);
            this->last_position = this->position;
        }
        void render(sf::RenderTarget* target){
            target->draw(this->particle_property);
        }
};