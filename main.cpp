#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <experimental/random>
#include <iostream>

int main()
{
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(640,360), "Dino escapes evolution"); 

    sf::Texture pause, cenario, carrego, carrego1;
    pause.loadFromFile("./imagens/menu.jpg");
    cenario.loadFromFile("./imagens/cenario1.png");
    carrego.loadFromFile("./imagens/carrego.png");
    carrego1.loadFromFile("./imagens/carrego1.png");

    sf::Texture aba, dinoc, bande, texture, cometa, caixa;
    aba.loadFromFile("./imagens/aba.png");
    dinoc.loadFromFile("./imagens/dinoC.png");
    bande.loadFromFile("./imagens/chegada.png");
    texture.loadFromFile("./imagens/dino.png");
    cometa.loadFromFile("./imagens/meteoro.png");

    sf::Font font, font2, font3;
    if (!font.loadFromFile("./fonte/PixelBloated.ttf") 
        || !font2.loadFromFile("./fonte/arial.ttf")
        || !font3.loadFromFile("./fonte/mine.ttf"))
    {
        std::cerr << "Falha ao ler a fonte\n";
        return EXIT_FAILURE;
    }

    sf::SoundBuffer music, comeco, colisao, over;
    comeco.loadFromFile("./sons/inicio.wav");
    music.loadFromFile("./sons/jurassic.wav");
    colisao.loadFromFile("./sons/colisao.wav");
    over.loadFromFile("./sons/GameOver.wav");

    sf::Sound musicF(music), toque(comeco), bateu(colisao), acabou(over);

    sf::Text welcome("Welcome to", font3, 15);
    welcome.setPosition(sf::Vector2f(270.f,0.f));
    welcome.setFillColor(sf::Color::White);

    sf::Text titulo("Dino Escapes Evolution", font, 30);
    titulo.setPosition(sf::Vector2f(50.f,150.f));
    titulo.setFillColor(sf::Color::White);

    sf::Text marca("Vicente R. 2024", font2, 10);
    marca.setPosition(sf::Vector2f(5.f,345.f));
    marca.setFillColor(sf::Color::White);

    sf::Text caregando("Loading...", font3, 10);
    caregando.setPosition(sf::Vector2f(288.f,135.f));
    caregando.setFillColor(sf::Color::White);

    sf::Text vida("Lifes: 5", font, 20);
    vida.setPosition(sf::Vector2f(10.f,0.f));
    vida.setFillColor(sf::Color::Red);

    sf::Text paisagem("Landscape: 1", font, 20);
    paisagem.setPosition(sf::Vector2f(10.f,20.f));
    paisagem.setFillColor(sf::Color::Black);

    sf::Text gameover("Game Over", font3, 50);
    gameover.setPosition(sf::Vector2f(180.f,130.f));
    gameover.setFillColor(sf::Color::White);

    sf::Sprite fundo(cenario), inicio(pause), fundo1(carrego), fundo2(carrego1);

    sf::Sprite espere(aba), movi(dinoc), ban(bande), sprite(texture), meteoro(cometa);
    espere.setPosition(sf::Vector2f(250.f,150));
    movi.setPosition(sf::Vector2f(238.f,152.f));
    ban.setPosition(sf::Vector2f(365.f,150.f));
    sprite.setPosition(sf::Vector2f(0.f,250.f));
    sprite.setColor(sf::Color::Black);

    
    float x = static_cast<float>(std::experimental::randint(10, (int)(window.getSize().x - cometa.getSize().x -10)));
    meteoro.setPosition(x,-20.f);

    int cont {0}, aux {2}, menu {0}, life {4};

    musicF.play();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
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
                toque.play();
                musicF.stop();
                menu = 1;
            }
        
        }
        
        if (menu == 1)
        {
            movi.move(0.03f,0.f);
            if (movi.getGlobalBounds().intersects(ban.getGlobalBounds()))
            {
                menu = 2;
            }
            
            window.clear();
            window.draw(fundo1);
            window.draw(espere);
            window.draw(movi);
            window.draw(ban);
            window.draw(caregando);
            window.display();
        }
        else if (menu >= 2)
        {
            meteoro.move(0.f,0.5f);
            if (meteoro.getGlobalBounds().intersects(sprite.getGlobalBounds()))
            {
                bateu.play();
                x = static_cast<float>(std::experimental::randint(10, (int)(window.getSize().x - cometa.getSize().x - 10)));
                meteoro.setPosition(x,-20.f);
                vida.setString("Lifes: " + std::to_string(life));
                if (life > -1)
                {
                    life--;
                }
                
                if (life == -1)
                {
                    acabou.play();
                }
            }
            if (life == -1)
            {
                window.clear();
                window.draw(fundo2);
                window.draw(gameover);
                window.display();
            }
            else
            {
                if (meteoro.getPosition().y > window.getSize().y)
                {
                    x = static_cast<float>(std::experimental::randint(10, (int)(window.getSize().x - cometa.getSize().x - 10)));
                    meteoro.setPosition(x,-20.f);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    sprite.move(0.3f,0.f);
                    texture.loadFromFile("./imagens/dino.png");
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    sprite.move(-0.3f,0.f);
                    texture.loadFromFile("./imagens/dino1.png");
                }

                if (sprite.getPosition().x > window.getSize().x) 
                {
                    if (cont == 0)
                    {
                        sprite.setPosition(0.f,250.f);
                        cenario.loadFromFile("./imagens/cenario2.png");
                        cont++;
                    }
                    else
                    {
                        sprite.setPosition(0.f,250.f);
                        cenario.loadFromFile("./imagens/cenario1.png");
                        cont = 0;
                    }  

                    paisagem.setString("Landscape: " + std::to_string(aux));
                    aux++;

                }

                window.clear();
                window.draw(fundo);
                window.draw(paisagem);
                window.draw(vida);
                window.draw(sprite);
                window.draw(meteoro);
                window.display();
            }
        }else{
            window.clear();
            window.draw(inicio);
            window.draw(titulo);
            window.draw(marca);
            window.draw(welcome);
            window.display();
        }        
        
    }
    
    return EXIT_SUCCESS;
}  
