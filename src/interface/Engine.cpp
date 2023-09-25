#include "../../include/Engine/Engine.h"

//defining initializer functions
void Engine::initVariables(){
    this->window = nullptr;
}
void Engine::initWindow(){
    this->video_mode.width = 900;
    this->video_mode.height = 700;
    this->window = new sf::RenderWindow(this->video_mode, "Verlet", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

//defining constructor and destructor
Engine::Engine(){
    this->initVariables();
    this->initWindow();
}
Engine::~Engine(){
    delete this->window;
}

//defining accessors
const bool Engine::running() const{
    return this->window->isOpen();
}

//defining window functions
void Engine::pollEvent(){
    while(this->window->pollEvent(this->event)){
        switch(this->event.type){
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->event.key.code == sf::Keyboard::Q){
                    if(this->verlet.balls.size() < 1){
                        this->verlet.createBall(this->mouse_position_view);
                        this->verlet.balls[0].pinned = true;
                        this->verlet.balls[0].selected = true;
                    }
                    else
                        this->verlet.createBall(this->mouse_position_view);
                }
                if(this->event.key.code == sf::Keyboard::E)
                    this->verlet.controlBall(this->mouse_position_view);
                if(this->event.key.code == sf::Keyboard::W)
                    this->verlet.shootProjectiles(this->mouse_position_view);
                break;
            case sf::Event::MouseButtonPressed:
                if(this->event.mouseButton.button == sf::Mouse::Left)
                    this->verlet.selection(this->mouse_position_view);
                if(this->event.mouseButton.button == sf::Mouse::Right)
                    this->verlet.pinning(this->mouse_position_view);
                break;
        }
    }
}
void Engine::update(float dt){
    this->pollEvent();
    this->mouse_position = sf::Mouse::getPosition(*this->window);
    this->mouse_position_view = this->window->mapPixelToCoords(this->mouse_position);

    this->verlet.update(dt);
}
void Engine::render(){
    this->window->clear(sf::Color::Black);
    this->verlet.render(this->window);
    this->window->display();
}
