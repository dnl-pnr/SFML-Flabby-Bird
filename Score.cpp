#include "Score.h"

Score::Score(sf::Font a) {
    score = 0;
    font = a;
}
void Score::increaseScore() {
    ++score;
}

int Score::getScore() {
    return score;
}

void Score::scoreDisplay(sf::RenderWindow& window) {
    sf::Text value;
    value.setFont(font);
    value.setString(to_string(score));
    value.setCharacterSize(150);
    value.setPosition(250, -40);
    value.setFillColor(sf::Color::White);
    value.setOutlineColor(sf::Color::Black);
    value.setOutlineThickness(4);
    window.draw(value);
}

void Score::scoreReset() {
    score = 0;
}