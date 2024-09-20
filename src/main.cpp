#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <experimental/random>
#include <iostream>

#include "ResourcesUtil.hpp"

int main()
{
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(640, 360), "Dino escapes evolution");

    sf::Font pixelBloatedFont = ResourcesUtil::getFont(kPixelBloatedFont);
    sf::Font arialFont = ResourcesUtil::getFont(kArialFont);
    sf::Font mineFont = ResourcesUtil::getFont(kMineFont);

    sf::Sound welcomeSound = ResourcesUtil::getSound(kWelcomeSound);
    sf::Sound clickSound = ResourcesUtil::getSound(kClickSound);
    sf::Sound collisionSound = ResourcesUtil::getSound(kCollisionSound);
    sf::Sound gameOverSound = ResourcesUtil::getSound(kGameOverSound);

    sf::Text welcomeText("Welcome to", mineFont, 15);
    welcomeText.setPosition(sf::Vector2f(270.f, 0.f));
    welcomeText.setFillColor(sf::Color::White);

    sf::Text titleText("Dino Escapes Evolution", pixelBloatedFont, 30);
    titleText.setPosition(sf::Vector2f(50.f, 150.f));
    titleText.setFillColor(sf::Color::White);

    sf::Text markText("Vicente R. 2024", arialFont, 10);
    markText.setPosition(sf::Vector2f(5.f, 345.f));
    markText.setFillColor(sf::Color::White);

    sf::Text loadingText("Loading...", mineFont, 10);
    loadingText.setPosition(sf::Vector2f(288.f, 135.f));
    loadingText.setFillColor(sf::Color::White);

    sf::Text lifesText("Lifes: 5", pixelBloatedFont, 20);
    lifesText.setPosition(sf::Vector2f(10.f, 0.f));
    lifesText.setFillColor(sf::Color::Red);

    sf::Text landscapeText("Landscape: 1", pixelBloatedFont, 20);
    landscapeText.setPosition(sf::Vector2f(10.f, 20.f));
    landscapeText.setFillColor(sf::Color::Black);

    sf::Text gameOverText("Game Over", mineFont, 50);
    gameOverText.setPosition(sf::Vector2f(180.f, 130.f));
    gameOverText.setFillColor(sf::Color::White);

    sf::Sprite bgGameImage = ResourcesUtil::getSprite(kBgGameImage);
    sf::Sprite bgWelcomeImage = ResourcesUtil::getSprite(kBgWelcomeImage);
    sf::Sprite bgBlackImage = ResourcesUtil::getSprite(kBgBlackImage);
    sf::Sprite bgGameOverImage = ResourcesUtil::getSprite(kBgGameOverImage);
    sf::Sprite loadingBarImage = ResourcesUtil::getSprite(kLoadingBarImage);
    sf::Sprite dinoLoadingImage = ResourcesUtil::getSprite(kDinoLoadingImage);
    sf::Sprite flagImage = ResourcesUtil::getSprite(kFlagImage);
    sf::Sprite dinoImage = ResourcesUtil::getSprite(kDinoR0Image);
    sf::Sprite meteoroImage = ResourcesUtil::getSprite(kMeteoroImage);
    
    loadingBarImage.setPosition(sf::Vector2f(250.f, 150));
    dinoLoadingImage.setPosition(sf::Vector2f(238.f, 152.f));
    flagImage.setPosition(sf::Vector2f(365.f, 150.f));
    dinoImage.setPosition(sf::Vector2f(0.f, 250.f));
    dinoImage.setColor(sf::Color::Black);

    float x = static_cast<float>(std::experimental::randint(10, (int)(window.getSize().x - meteoroImage.getTexture()->getSize().x - 10)));
    meteoroImage.setPosition(x, -20.f);

    int cont{0}, aux{2}, menu{0}, life{4};

    welcomeSound.play();

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (menu == 0)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                clickSound.play();
                welcomeSound.stop();
                menu = 1;
            }

            window.clear();
            window.draw(bgWelcomeImage);
            window.draw(titleText);
            window.draw(markText);
            window.draw(welcomeText);
            window.display();
        }
        else if (menu == 1)
        {
            dinoLoadingImage.move(0.01f, 0.f);
            if (dinoLoadingImage.getGlobalBounds().intersects(flagImage.getGlobalBounds()))
            {
                menu = 2;
            }

            window.clear();
            window.draw(bgBlackImage);
            window.draw(loadingBarImage);
            window.draw(dinoLoadingImage);
            window.draw(flagImage);
            window.draw(loadingText);
            window.display();
        }
        else
        {
            meteoroImage.move(0.f, 0.1f);
            if (meteoroImage.getGlobalBounds().intersects(dinoImage.getGlobalBounds()))
            {
                collisionSound.play();
                x = static_cast<float>(std::experimental::randint(10, (int)(window.getSize().x - meteoroImage.getTexture()->getSize().x - 10)));
                meteoroImage.setPosition(x, -20.f);
                lifesText.setString("Lifes: " + std::to_string(life));
                if (life > -1)
                {
                    life--;
                }

                if (life == -1)
                {
                    gameOverSound.play();
                }
            }
            if (life == -1)
            {
                window.clear();
                window.draw(bgGameOverImage);
                window.draw(gameOverText);
                window.display();
            }
            else
            {
                if (meteoroImage.getPosition().y > window.getSize().y)
                {
                    x = static_cast<float>(std::experimental::randint(10, (int)(window.getSize().x - meteoroImage.getTexture()->getSize().x - 10)));
                    meteoroImage.setPosition(x, -20.f);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    dinoImage.move(0.3f, 0.f);
                    dinoImage.setTexture(ResourcesUtil::getTexture(kDinoR0Image));
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    dinoImage.move(-0.3f, 0.f);
                    dinoImage.setTexture(ResourcesUtil::getTexture(kDinoL0Image));
                }

                if (dinoImage.getPosition().x > window.getSize().x)
                {
                    if (cont == 0)
                    {
                        dinoImage.setPosition(0.f, 250.f);
                        cont++;
                    }
                    else
                    {
                        dinoImage.setPosition(0.f, 250.f);
                        cont = 0;
                    }

                    landscapeText.setString("Landscape: " + std::to_string(aux));
                    aux++;
                }

                window.clear();
                window.draw(bgGameImage);
                window.draw(landscapeText);
                window.draw(lifesText);
                window.draw(dinoImage);
                window.draw(meteoroImage);
                window.display();
            }
        }
    }

    return EXIT_SUCCESS;
}
