#include "Pillar.h"
#include "Score.h"
using namespace std;

void Pillar::createPillar() {
    pillars.insert(pillars.begin(), new sf::RectangleShape(sf::Vector2f(30.0f, 620.0f)));
    pillars.insert(pillars.begin(), new sf::RectangleShape(sf::Vector2f(30.0f, 620.0f)));
    (*pillars.at(0)).setTexture(&texture);
    (*pillars.at(1)).setTexture(&texture);
    (*pillars.at(0)).setOutlineColor(sf::Color::Black);
    (*pillars.at(1)).setOutlineColor(sf::Color::Black);
    (*pillars.at(0)).setOutlineThickness(1.5);
    (*pillars.at(1)).setOutlineThickness(1.5);
    caps.insert(caps.begin(), new sf::RectangleShape(sf::Vector2f(38.0f, 18.0f)));
    caps.insert(caps.begin(), new sf::RectangleShape(sf::Vector2f(38.0f, 18.0f)));
    (*caps.at(0)).setTexture(&capTexture);
    (*caps.at(1)).setTexture(&capTexture);
    (*caps.at(0)).setOutlineColor(sf::Color::Black);
    (*caps.at(1)).setOutlineColor(sf::Color::Black);
    (*caps.at(0)).setOutlineThickness(1.5);
    (*caps.at(1)).setOutlineThickness(1.5);
}

Pillar::Pillar(sf::Texture a, sf::Texture b) {
    //populates the vector with initial pillars
    double pos[7];
    int gap;
    texture = a;
    capTexture = b;
    for (int i = 0; i < 5; i += 2) {
        pos[i] = 500 + (100 * i);
        createPillar();
        gap = rand() % -400 + -580;
        (*pillars.at(0)).setPosition(pos[i], gap);
        (*pillars.at(1)).setPosition(pos[i], gap + 800);
        (*caps.at(0)).setPosition(pos[i] - 4, gap + 610);
        (*caps.at(1)).setPosition(pos[i] - 4, gap + 790);
    }
}

void Pillar::updatePillars(sf::RenderWindow& window, Score& score) {
    sf::Vector2f currentPos;
    int gap;
    //moves all pillars to the left once
    for (int i = 0; i < 6; ++i) {
        (*pillars.at(i)).move(-2.5, 0);
        (*caps.at(i)).move(-2.5, 0);
        window.draw(*pillars.at(i)); 
        window.draw(*caps.at(i));
    }
    //when pillar passes left side of screen, deletes it and makes a new one
    currentPos = (*pillars.back()).getPosition();
    if (currentPos.x < -99.0) {
        pillars.pop_back();
        pillars.pop_back();
        caps.pop_back();
        caps.pop_back();
        createPillar();
        gap = rand() % -400 + -580;
        (*pillars.at(0)).setPosition(500, gap);
        (*pillars.at(1)).setPosition(500, gap + 800);
        (*caps.at(0)).setPosition(500 - 4, gap + 610);
        (*caps.at(1)).setPosition(500 - 4, gap + 790);
    }
    //tracks score
    for (int i = 0; i < 6; i += 2) {
        currentPos = (*pillars.at(i)).getPosition();
        if (currentPos.x == 155.0) {
            score.increaseScore();
        }
    }
}

void Pillar::reset() {
    pillars.clear();
    //populates the vector with initial pillars
    double pos[7];
    int gap;
    for (int i = 0; i < 5; i += 2) {
        pos[i] = 500 + (100 * i);
        createPillar();
        gap = rand() % -400 + -580;
        (*pillars.at(0)).setPosition(pos[i], gap);
        (*pillars.at(1)).setPosition(pos[i], gap + 800);
        (*caps.at(0)).setPosition(pos[i] - 4, gap + 610);
        (*caps.at(1)).setPosition(pos[i] - 4, gap + 790);
    }
}