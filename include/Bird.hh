#ifndef BIRD_HEADER
#define BIRD_HEADER

#define ROOF_LIMIT 700 - 136

#include <iostream>
#include <SFML/Graphics.hpp>

class Bird : public sf::Drawable
{
private:
    bool initiated, live;
    int status, timerState;
    std::vector<sf::Texture> states;
    sf::Sprite sprite;
    float movSpeed;

public:
    Bird(int, int);
    void Update();
    void Jump();
    void Death();
    bool isAlive();
    sf::Vector2f getPosition();
    void Initiated();
    void draw(sf::RenderTarget &, sf::RenderStates) const;
};

#endif // !BIRD_HEADER