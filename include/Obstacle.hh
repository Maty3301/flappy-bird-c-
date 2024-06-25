#ifndef OBSTACLE_HEADER
#define OBSTACLE_HEADER

#include <iostream>
#include <SFML/Graphics.hpp>

class Obstacle : public sf::Drawable
{
private:
    sf::Sprite upperSprite, lowerSprite;

public:
    Obstacle(sf::Texture &, int, int);
    void Update();
    bool Collision(sf::IntRect);
    sf::Vector2f getPosition();
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
};

#endif // !OBSTACLE_HEADER