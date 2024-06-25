#include "../include/UISound.hh"

UISound::UISound()
{
    initiated = false;
    gameOver = false;

    if (!font.loadFromFile("resources/font/font.ttf") ||
        !gameOverTexture.loadFromFile("resources/sprites/gameover.png") ||
        !initTexture.loadFromFile("resources/sprites/message.png") ||
        !pointB.loadFromFile("resources/sounds/point.ogg") ||
        !wingB.loadFromFile("resources/sounds/wing.ogg") ||
        !hitB.loadFromFile("resources/sounds/hit.ogg") ||
        !music.openFromFile("resources/sounds/music.ogg"))
        exit(EXIT_FAILURE);

    music.openFromFile("resources/sounds/music.ogg");
    music.setLoop(true);
    music.play();

    point.setBuffer(pointB);
    wing.setBuffer(wingB);
    hit.setBuffer(hitB);

    currentScore = 0;
    currentScoreT.setFont(font);
    currentScoreT.setCharacterSize(40);
    currentScoreT.setString(std::to_string(currentScore));
    currentScoreT.setOrigin(currentScoreT.getGlobalBounds().width / 2, currentScoreT.getGlobalBounds().height / 2);
    currentScoreT.setPosition(210, 50);

    std::ifstream in("score");
    in >> maxScore;

    maxScoreT.setFont(font);
    maxScoreT.setCharacterSize(20);
    maxScoreT.setString(std::to_string(maxScore));
    maxScoreT.setOrigin(maxScoreT.getGlobalBounds().width / 2, maxScoreT.getGlobalBounds().height / 2);
    maxScoreT.setPosition(210, 100);

    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setOrigin(gameOverTexture.getSize().x / 2, gameOverTexture.getSize().y / 2);
    gameOverSprite.setScale(2, 2);
    gameOverSprite.setPosition(210, 350);

    initSprite.setTexture(initTexture);
    initSprite.setOrigin(initTexture.getSize().x / 2, initTexture.getSize().y / 2);
    initSprite.setScale(1.5f, 1.5f);
    initSprite.setPosition(210, 280);
}

void UISound::setScore(int val)
{
    if (currentScore != val)
        point.play();

    currentScore = val;
    currentScoreT.setString(std::to_string(currentScore));
    currentScoreT.setOrigin(currentScoreT.getGlobalBounds().width / 2, currentScoreT.getGlobalBounds().height / 2);
}

void UISound::Initiated(bool state)
{
    initiated = state;
    currentScore = 0;
    gameOver = false;

    std::ifstream in("score");
    in >> maxScore;

    maxScoreT.setString(std::to_string(maxScore));
    maxScoreT.setOrigin(maxScoreT.getGlobalBounds().width / 2, maxScoreT.getGlobalBounds().height / 2);

    currentScoreT.setString(std::to_string(currentScore));
    currentScoreT.setOrigin(currentScoreT.getGlobalBounds().width / 2, currentScoreT.getGlobalBounds().height / 2);
}

void UISound::Wing()
{
    wing.play();
}

void UISound::GameOver()
{
    if (!gameOver)
        hit.play();

    if (currentScore > maxScore)
    {
        maxScore = currentScore;
        std::ofstream out("score");
        out << currentScore;
    }

    gameOver = true;
}

void UISound::draw(sf::RenderTarget &rt, sf::RenderStates rs) const
{
    if (!initiated)
        rt.draw(initSprite, rs);
    else
    {
        rt.draw(currentScoreT, rs);
        rt.draw(maxScoreT, rs);

        if (gameOver)
            rt.draw(gameOverSprite, rs);
    }
}