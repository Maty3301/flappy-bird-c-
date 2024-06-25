#ifndef PARALLAX_HEADER
#define PARALLAX_HEADER

#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Obstacle.hh"

class Parallax : public sf::Drawable
{
private:
    int score, last;
    bool initiated;
    sf::Texture obstacleTexture, baseTexture;
    std::vector<sf::Sprite> bases;
    std::vector<Obstacle> obstacles;

public:
    Parallax();
    void Update();
    bool Collision(sf::IntRect);
    void Initiated();
    int Score();
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
};

#endif // !PARALLAX_HEADER