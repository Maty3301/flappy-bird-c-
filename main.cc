#include <iostream>
#include <SFML/Graphics.hpp>
#include "include/Bird.hh"
#include "include/Parallax.hh"
#include "include/UISound.hh"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 700
#define FRAME_LIMIT 60

int main(void)
{
    sf::Texture backTexture;
    sf::Sprite backSprite;

    if (!backTexture.loadFromFile("resources/sprites/background.png"))
        exit(EXIT_FAILURE);

    backSprite.setTexture(backTexture);
    backSprite.setPosition(0, -15);
    backSprite.setScale(1.5f, 1.5f);

    bool initialited, pressed;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird");
    window.setFramerateLimit(FRAME_LIMIT);
    pressed = false;
    UISound uis;

    while (window.isOpen())
    {
        Bird *bird = new Bird(210, 350);
        Parallax *parallax = new Parallax();
        initialited = false;
        uis.Initiated(false);

        while (true)
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    exit(EXIT_SUCCESS);
                }
            }

            bird->Update();

            if (bird->isAlive())
            {
                parallax->Update();

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed)
                {
                    bird->Jump();
                    pressed = true;
                    uis.Wing();

                    if (!initialited)
                    {
                        initialited = true;
                        bird->Initiated();
                        parallax->Initiated();
                        uis.Initiated(true);
                    }
                }
            }
            else
                uis.GameOver();

            if (!bird->isAlive() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed)
            {
                pressed = true;
                break;
            }

            sf::IntRect rect(bird->getPosition().x - 23, bird->getPosition().y - 21, 44, 40);
            if (bird->getPosition().y < 0 || bird->getPosition().y > ROOF_LIMIT || parallax->Collision(rect))
                bird->Death();

            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                pressed = false;

            uis.setScore(parallax->Score());

            window.clear();
            window.draw(backSprite);
            window.draw(*parallax);
            window.draw(*bird);
            window.draw(uis);
            window.display();
        }

        delete bird;
        delete parallax;
    }

    exit(EXIT_SUCCESS);
}
