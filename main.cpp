#include <SFML\Graphics.hpp>
#include <graphics.h>
#include "Animation.h"
//#include "soil.cpp"
#include <iostream>
#include <stdlib.h>

sf::RenderWindow window(sf::VideoMode(500,500), "GAME SFML", sf::Style::Default);

class Soil {
    private:
    int x;
    int y;

    sf::Sprite sprite;
    sf::Texture texture;

    public:

    void movement() {
        x-=2;
        sprite.setPosition(x,y);
    }

    void setposisi(int _x, int _y) {
        x = _x;
        y = _y;

       // if(texture.loadFromFile("soil.jpg") != true)return;
        texture.loadFromFile("soil.jpg");
        sprite.setTexture(texture);
        sprite.setScale(0.2, 0.04);
        sprite.setPosition(x,y);
    }


    sf::Sprite get() {
        return sprite;
    }
};

class Player {
    int x;
    int y;



};

int main()
{
    sf::RectangleShape score (sf::Vector2f (1.5f,0.5f));
    score.setFillColor(sf::Color::White);
    score.setPosition(40.0f,0.0f);

    sf::RectangleShape background(sf::Vector2f (500.0f,500.0f));
    background.setPosition(0.0f,0.0f);
    sf::Texture backgroundImage;
    backgroundImage.loadFromFile("background.jpg");
    background.setTexture(&backgroundImage);

    sf::RectangleShape player(sf::Vector2f(100.0f,100.0f));
    player.setPosition(0.0f,0.0f);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("tux_from_linux.png");
    player.setTexture(&playerTexture);

    Animation animation(&playerTexture, sf::Vector2u(3,9), 1.0f);

    sf::RectangleShape player2(sf::Vector2f(30.0f,30.0f));
    player2.setPosition(40.0f,55.0f);
    player2.setTexture(&playerTexture);

    Animation animation2(&playerTexture, sf::Vector2u(3,9), 1.0f);

    float deltaTime = 0.0f;
    sf::Clock clock;

    Soil soil[20];
    for(int i = 0; i < 20; i++) {
        int x = 0;
        int y = 0;
        x = rand()%1000;
        while(y<100)
            y = rand()%1000;
        soil[i].setposisi(x,y);
        //std::cout<<x<<" "<<y<<std::endl;
    }


    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if(evnt.type==sf::Event::Closed)
            {

                window.close();
                break;

            }
        }

    window.draw(score);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            player.move(-2.0f,0.0f);
            player2.move(-2,0.0f);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.move(2,0.0f);
            player2.move(2,0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            float vy = 10.0;
            float g = 1;
            while(vy>=-5){
                player.move(1,-vy);
                player2.move(1,-vy);
                vy-=g;
                window.clear();
                window.draw(background);
                //window.draw(score);

                for(int i = 0; i<20; i++){
                    soil[i].movement();
                    window.draw(soil[i].get());
                }
                window.draw(player);
                window.display();
                delay(100);
                }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            player.move(0.0f,2);
            player2.move(0.0f,2);
        }


        animation.Update(7, deltaTime);
        player.setTextureRect(animation.uvRect);
        animation2.Update(7, deltaTime);
        player2.setTextureRect(animation.uvRect);
        window.clear();
        window.draw(background);
        //window.draw(score);


        bool collision = false;
        for(int i = 0; i<20; i++) {
            sf::Sprite _soil = soil[i].get();
            if(player2.getGlobalBounds().intersects(_soil.getGlobalBounds()))
                collision = true;
            soil[i].movement();
            window.draw(soil[i].get());
        }
        if(!collision){
            player.move(0,5);
            player2.move(0,5);
        }

        window.draw(player);
        window.display();
        delay(10);
    }
    return 0;
}
