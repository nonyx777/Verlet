#include "../../include/Demos/Verlet.hpp"

//defining constructor
Verlet::Verlet(){
    //..
}

//defining custom function
void Verlet::createBall(sf::Vector2f mouse_position){
    Ball ball = Ball(mouse_position - sf::Vector2f(1.f, 1.f));
    ball.setMass(1.f);
    ball.setElasticity(1.f);
    ball.particle_property.setFillColor(sf::Color::White);
    ball.particle_property.setRadius(10.f);
    ball.particle_property.setOrigin(sf::Vector2f(ball.particle_property.getRadius(), ball.particle_property.getRadius()));
    ball.particle_property.setPosition(mouse_position);

    this->balls.push_back(ball);

    //...
    if(this->balls.size() > 1)
        this->createLine();
}
void Verlet::shootProjectiles(sf::Vector2f mouse_position){
    Ball projectile = Ball(mouse_position - sf::Vector2f(1.f, 1.f));
    projectile.setMass(10.f);
    projectile.setElasticity(0.5f);
    projectile.particle_property.setFillColor(sf::Color(100, 50, 90, 255));
    projectile.particle_property.setRadius(10.f);
    projectile.particle_property.setOrigin(sf::Vector2f(projectile.particle_property.getRadius(), projectile.particle_property.getRadius()));
    projectile.particle_property.setPosition(mouse_position);

    this->projectiles.push_back(projectile);
}
void Verlet::createLine(){
    Line line;
    this->lines.push_back(line);
}
void Verlet::lineAlign(){
    for(int i = 0; i < this->lines.size(); i++){
        this->lines[i].setBase(this->balls[i].particle_property.getPosition());
        this->lines[i].setDirection(this->balls[i+1].particle_property.getPosition());
    }

    //connecting the first and last
    // if(this->balls.size() > 1){
    //     this->tail.setBase(this->balls[this->balls.size()-1].particle_property.getPosition());
    //     this->tail.setDirection(this->balls[0].particle_property.getPosition());
    // }
}
void Verlet::resolveCaller(){
    if(this->balls.size() < 2)
        return;

    //resolves all the balls except the first and the last
    for(int i = 0; i < this->balls.size()-1; i++){
        int j = i+1;
        this->distanceResolver(this->balls[i], this->balls[j]);
        this->balls[i].particle_property.move(this->ball1_position);
        this->balls[j].particle_property.move(this->ball2_position);
    }

    //first and last
    // this->distanceResolver(this->balls[0], this->balls[this->balls.size()-1]);
    // this->balls[0].particle_property.move(this->ball1_position);
    // this->balls[this->balls.size()-1].particle_property.move(this->ball2_position);

    //Box
    // if(this->balls.size() == 4){
    //     this->distanceResolverForFour(this->balls[1], this->balls[3]);
    //     this->balls[1].particle_property.move(this->ball1_position);
    //     this->balls[3].particle_property.move(this->ball2_position); 
    // }
}
void Verlet::distanceResolver(Ball ball1, Ball ball2){
    sf::Vector2f displacement = ball1.particle_property.getPosition() - ball2.particle_property.getPosition();
    float distance = Operation()._magnitude(displacement);
    float difference = this->length - distance;
    float percent = difference/distance/2.f;
    sf::Vector2f offset = displacement * percent;
    this->ball1_position = ball1.pinned == true ? sf::Vector2f(0.f, 0.f) : offset;
    this->ball2_position = ball2.pinned == true ? sf::Vector2f(0.f, 0.f) : -offset;
}
void Verlet::distanceResolverForFour(Ball ball1, Ball ball2){
    sf::Vector2f displacement = ball1.particle_property.getPosition() - ball2.particle_property.getPosition();
    float distance = Operation()._magnitude(displacement);
    float difference = this->length_for_four - distance;
    float percent = difference/distance/2.f;
    sf::Vector2f offset = displacement * percent;
    this->ball1_position = ball1.pinned == true ? sf::Vector2f(0.f, 0.f) : offset;
    this->ball2_position = ball2.pinned == true ? sf::Vector2f(0.f, 0.f) : -offset;
}
void Verlet::selection(sf::Vector2f mouse_position){
    for(Ball &ball : this->balls){
        if(Operation()._magnitude(Operation()._displacement(mouse_position, ball.particle_property.getPosition())) <= ball.particle_property.getRadius()){
            ball.selected = true;
        }
        else
            ball.selected = false;
    }
}
void Verlet::pinning(sf::Vector2f mouse_position){
    for(Ball &ball : this->balls){
        if(ball.selected)
            ball.pinned = !ball.pinned;
    }
}
void Verlet::controlBall(sf::Vector2f mouse_position){
    for(Ball &ball : this->balls){
        if(ball.selected == true && ball.pinned)
            ball.particle_property.setPosition(mouse_position);
    }
}
void Verlet::resolveCollision(){
    for(int i = 0; i < this->projectiles.size(); i++){
        for(int j = 0; j < this->projectiles.size() && i != j; j++){
            if(this->cod._ballCollide(this->projectiles[i], this->projectiles[j])){
                this->cod._ballBallPenetrationResolution(this->projectiles[i], this->projectiles[j]);
                this->projectiles[i].particle_property.move(this->cod.a_position);
                this->projectiles[j].particle_property.move(this->cod.b_position);
            }
        }
    }

    for(Ball &ball : this->balls){
            for(Ball &projectile : this->projectiles){
                if(this->cod._ballCollide(ball, projectile)){
                    this->cod._ballBallPenetrationResolution(ball, projectile);
                    ball.particle_property.move(this->cod.a_position);
                    projectile.particle_property.move(this->cod.b_position);
                }
            }
    }
}

//defining integrator and displayer
void Verlet::update(float dt){
    this->resolveCollision();
    this->lineAlign();
    this->resolveCaller();


    for(Ball &ball : this->balls)
        ball.update(dt);
    for(Ball &projectile : this->projectiles)
        projectile.update(dt);
}
void Verlet::render(sf::RenderTarget* target){
    for(Ball &ball : this->balls){
        if(ball.selected == true)
            ball.render(target);
    }
    for(Line &line : this->lines)
        line.render(target);
    for(Ball &projectile : this->projectiles)
        projectile.render(target);
    // this->tail.render(target);
}