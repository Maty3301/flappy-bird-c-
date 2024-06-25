#ifndef UISOUND_HEADER
#define UISOUND_HEADER

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

class UISound : public sf::Drawable
{
private:
    sf::SoundBuffer pointB, wingB, hitB;
    sf::Sound point, wing, hit;
    sf::Music music;
    sf::Font font;
    sf::Text maxScoreT, currentScoreT;
    int currentScore, maxScore;
    bool initiated, gameOver;
    sf::Texture gameOverTexture, initTexture;
    sf::Sprite gameOverSprite, initSprite;

public:
    UISound();
    void setScore(int);
    void Initiated(bool);
    void GameOver();
    void Wing();
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
};

#endif // !UISOUND_HEADER