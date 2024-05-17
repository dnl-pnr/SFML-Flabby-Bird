#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Bird.h"
#include "Score.h"
#include <iostream>
#include <time.h>
#include <Windows.h>
#include "Pillar.h"

using namespace std;

bool checkCollisions(Bird Bird, vector<sf::RectangleShape*> pillars, vector<sf::RectangleShape*> edges) {
    sf::FloatRect pillarHitBoxes;
    sf::FloatRect borders;
    sf::FloatRect birdHitBox = Bird.shape.getGlobalBounds();
    bool hit;

    for (int i = 0; i < 2; ++i) { //checks if bird hits ceiling or floor
        borders = (edges.at(i))->getGlobalBounds();
        hit = birdHitBox.intersects(borders);
        if (hit == true) {
            break;
        }
    }
    if (hit != true) { //checks if bird hits any pillars
        for (int i = 0; i < 6; ++i) {
            pillarHitBoxes = (pillars.at(i))->getGlobalBounds();
            hit = birdHitBox.intersects(pillarHitBoxes);
            if (hit == true) {
                break;
            }
        }
    }
    return hit;
}

void endGame() {
    sf::RenderWindow window(sf::VideoMode(500, 620), "You Lost");
    sf::Texture t3;
    t3.loadFromFile("C:/Users/Lab6131/source/repos/FlappyBirdSFML/LoseScreen.png");
    sf::Sprite LoseScreen(t3);
    LoseScreen.setOrigin(0, 0);
    LoseScreen.setPosition(0, 0);
    LoseScreen.setScale(4.15, 4);
    window.draw(LoseScreen);
    window.display();
    Sleep(1000);
}

int main()
{
    srand((int)time(nullptr));

    //SFML stuff
    sf::RenderWindow window(sf::VideoMode(500, 620), "SFML Flappy Bird");
    sf::Texture b1;
    b1.loadFromFile("C:/Users/Lab6131/source/repos/FlappyBirdSFML/flappy1.png");
    sf::Sprite Background(b1);
    Background.setOrigin(0, 0);
    Background.setScale(1, 1.37);
    Background.setPosition(0, 0);
    vector<sf::Texture> birdFrames;
    sf::Texture s1;
    sf::Texture s2;
    sf::Texture s3;
    s1.loadFromFile("C:/Users/Lab6131/source/repos/WorkingFlappyBirdSFML/bird1.2.png");
    s2.loadFromFile("C:/Users/Lab6131/source/repos/WorkingFlappyBirdSFML/bird2.3.png");
    s3.loadFromFile("C:/Users/Lab6131/source/repos/WorkingFlappyBirdSFML/bird3.1.png");
    birdFrames.push_back(s1);
    birdFrames.push_back(s2);
    birdFrames.push_back(s3);
    Bird Bird(birdFrames);
    Bird.shape.setOrigin(0, 0);
    Bird.shape.setPosition(150, 200);
    sf::Font font;
    font.loadFromFile("FlappyBirdRegular-9Pq0.ttf");
    Score score(font);
    sf::Texture p1;
    sf::Texture p2;
    p1.loadFromFile("C:/Users/Lab6131/source/repos/WorkingFlappyBirdSFML/pipe1.png");
    p2.loadFromFile("C:/Users/Lab6131/source/repos/WorkingFlappyBirdSFML/pipe2.png");


    //create ceiling and floor
    vector<sf::RectangleShape*> edges;
    edges.push_back(new sf::RectangleShape(sf::Vector2f(500.0f, 10.0f)));
    edges.push_back(new sf::RectangleShape(sf::Vector2f(500.0f, 10.0f)));
    (*edges.at(0)).setPosition(0, 0);
    (*edges.at(1)).setPosition(0, 620);

    //various varibles used
    int gap = 0;
    Pillar pillars(p1, p2);
    bool play = false;
   
    while (window.isOpen()) {  
        window.draw(Background);
        window.draw(Bird.shape);
        window.display();

        //check when to start game
        sf::Event event2;
        while (window.pollEvent(event2))
        {
            if (event2.type == sf::Event::Closed)
                window.close();
            else if (event2.type == sf::Event::MouseButtonPressed)
            {
                if (event2.mouseButton.button == sf::Mouse::Left)
                {
                    play = true;
                }
            }

        }

        if (play == true) {           
            //game running
            while (play == true) {
                sf::Event event;

                //game inputs
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            Bird.birdJump(window);
                        }
                    }
                    else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Space) {
                            Bird.birdJump(window);
                        }
                    }
                }
                window.clear();
                window.draw(Background);
                pillars.updatePillars(window, score);
                Bird.birdUpdate(window);
                score.scoreDisplay(window);
                if (checkCollisions(Bird, pillars.pillars, edges) == true) {
                    pillars.pillars.clear();
                    play = false;
                    endGame();
                    score.scoreReset();
                    Bird.birdReset();
                    pillars.reset();
                }
                window.display();
                Sleep(10);
            }
        }
    }
}