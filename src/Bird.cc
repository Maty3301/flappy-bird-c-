#include "../include/Bird.hh"

#define DEFAULT_TIMER_STATE 10
#define MOV_SPEED 12
#define ROT_SPEED 4
#define JUMP_FORCE -8
#define JUMP_FORCE_ROT -15
#define DEATH_FALL_SPEED 10

Bird::Bird(int x, int y)
{
    initiated = false;
    live = true;
    status = 0;
    timerState = DEFAULT_TIMER_STATE;
    states.resize(3);

    if (!states[0].loadFromFile("resources/sprites/birdupflap.png") ||
        !states[1].loadFromFile("resources/sprites/birdmidflap.png") ||
        !states[2].loadFromFile("resources/sprites/birddownflap.png"))
        exit(EXIT_FAILURE);

    sprite.setTexture(states[status]);
    sprite.setOrigin(states[status].getSize().x / 2, states[status].getSize().y / 2);
    sprite.setPosition(x, y);
    sprite.setScale(2, 2);
    movSpeed = 0;
}

void Bird::Update()
{
    if (!live)
    {
        if (sprite.getPosition().y < ROOF_LIMIT)
        {
            sprite.move(0, MOV_SPEED);
            sprite.setRotation(sprite.getRotation() + DEATH_FALL_SPEED);
        }
        return;
    }

    timerState--;

    if (timerState == 0)
    {
        status++;
        status %= (int)states.size();
        sprite.setTexture(states[status]);
        sprite.setOrigin(states[status].getSize().x / 2, states[status].getSize().y / 2);
        timerState = DEFAULT_TIMER_STATE;
    }

    if (!initiated)
        return;

    sprite.move(0, movSpeed);
    movSpeed += .5f;

    if (movSpeed > 8 && movSpeed < 15)
        sprite.setRotation(sprite.getRotation() + ROT_SPEED);
}

void Bird::Jump()
{
    movSpeed = JUMP_FORCE;
    sprite.setRotation(JUMP_FORCE_ROT);
}

sf::Vector2f Bird::getPosition()
{
    return sprite.getPosition();
}

bool Bird::isAlive()
{
    return live;
}

void Bird::Death()
{
    live = false;
}

void Bird::Initiated()
{
    initiated = true;
}

void Bird::draw(sf::RenderTarget &rt, sf::RenderStates rs) const
{
    rt.draw(sprite, rs);
}