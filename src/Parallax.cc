#include "../include/Parallax.hh"

Parallax::Parallax()
{
    last = -1;
    initiated = false;
    score = 0;

    if (!obstacleTexture.loadFromFile("resources/sprites/pipe.png") ||
        !baseTexture.loadFromFile("resources/sprites/base.png"))
        exit(EXIT_FAILURE);

    srand(time(NULL));

    obstacles.push_back(Obstacle(obstacleTexture, 500, 100 + rand() % 250));
    obstacles.push_back(Obstacle(obstacleTexture, 850, 100 + rand() % 250));

    sf::Sprite newSprite;
    newSprite.setTexture(baseTexture);
    newSprite.setPosition(0, 700 - 112);
    newSprite.setScale(1.5f, 1.5f);

    bases.push_back(newSprite);
    newSprite.setPosition(336 * 1.5f, 700 - 112);
    bases.push_back(newSprite);
}

void Parallax::Update()
{
    for (int i = 0; i < bases.size(); i++)
        if (bases[i].getPosition().x < -(336 * 1.5f))
        {
            sf::Sprite newSprite = bases[bases.size() - 1];
            newSprite.setPosition(newSprite.getPosition().x + 336 * 1.5f, 700 - 112);

            bases.push_back(newSprite);
            bases.erase(bases.begin() + i);
            continue;
        }

    for (int i = 0; i < bases.size(); i++)
        bases[i].move(-2.5f, 0);

    if (!initiated)
        return;

    for (int i = 0; i < obstacles.size(); i++)
    {
        int lastObstacle = obstacles.size() - 1;

        if (obstacles[i].getPosition().x < 100 && i > last)
        {
            last = i;
            score++;
        }

        if (obstacles[i].getPosition().x <= -100)
            last--, obstacles.erase(obstacles.begin() + i),
                obstacles.push_back(Obstacle(obstacleTexture, obstacles[lastObstacle].getPosition().x + 350, 100 + rand() % 250));
    }

    for (int i = 0; i < obstacles.size(); i++)
        obstacles[i].Update();
}

bool Parallax::Collision(sf::IntRect rect)
{
    for (int i = 0; i < obstacles.size(); i++)
        if (obstacles[i].Collision(rect))
            return true;

    return false;
}

int Parallax::Score()
{
    return score;
}

void Parallax::Initiated()
{
    initiated = true;
}

void Parallax::draw(sf::RenderTarget &rt, sf::RenderStates rs) const
{
    for (int i = 0; i < obstacles.size(); i++)
        rt.draw(obstacles[i], rs);

    for (int i = 0; i < bases.size(); i++)
        rt.draw(bases[i], rs);
}