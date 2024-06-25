#include "../include/Obstacle.hh"

Obstacle::Obstacle(sf::Texture &texture, int x, int y)
{
    upperSprite.setTexture(texture);
    lowerSprite.setTexture(texture);

    upperSprite.setOrigin(texture.getSize().x, 0);
    upperSprite.setRotation(180);

    upperSprite.setPosition(x, y);
    lowerSprite.setPosition(x, y + 150);

    upperSprite.setScale(1.5f, 1.5f);
    lowerSprite.setScale(1.5f, 1.5f);
}

void Obstacle::Update()
{
    upperSprite.move(-2.5f, 0);
    lowerSprite.move(-2.5f, 0);
}

bool Obstacle::Collision(sf::IntRect rect)
{
    sf::IntRect upperRect(upperSprite.getPosition().x + 4, upperSprite.getPosition().y - 480, 70, 480),
        lowerRect(lowerSprite.getPosition().x + 4, lowerSprite.getPosition().y, 70, 480);

    if (upperRect.intersects(rect) || lowerRect.intersects(rect))
        return true;

    return false;
}

sf::Vector2f Obstacle::getPosition()
{
    return upperSprite.getPosition();
}

void Obstacle::draw(sf::RenderTarget &rt, sf::RenderStates rs) const
{
    rt.draw(upperSprite, rs);
    rt.draw(lowerSprite, rs);
}