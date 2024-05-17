#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
using namespace std;

class Score {
private:
    int score;
    sf::Font font;

public:
    Score(sf::Font a);

    void increaseScore();

    int getScore();

    void scoreDisplay(sf::RenderWindow& window);

    void scoreReset();
};

