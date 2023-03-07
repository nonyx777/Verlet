#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../include/Particle/Particle.hpp"

class Ball : public Particle{
    private:
        //window border parameters
        float height = 360.f;
        float width = 640.f;

    public:
        sf::CircleShape particle_property;
        sf::Vector2f last_position;
        //node properties
        bool pinned;
        bool selected;

        //movement variables
    public:
        Ball(){
        }
        Ball(sf::Vector2f initial_last_position){
            this->last_position = initial_last_position;
            this->acceleration = sf::Vector2f(0.f, .5f);
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

        void integrate(float dt){
            if(this->pinned == true)
                return;
            
            this->position = this->particle_property.getPosition();
            this->velocity = this->position - this->last_position;
            this->particle_property.move(this->velocity + this->acceleration);
            this->last_position = this->position;
        }

        void update(float dt){
            //color change based on selection state
            if(this->selected == true)
                this->particle_property.setFillColor(sf::Color::Red);
            else
                this->particle_property.setFillColor(sf::Color::White);
            


            this->collisionResolve();
            this->integrate(dt);
        }
        void render(sf::RenderTarget* target){
            target->draw(this->particle_property);
        }
};