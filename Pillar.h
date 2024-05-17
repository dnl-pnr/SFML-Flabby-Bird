#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Score.h"
using namespace std;

class Pillar : virtual public sf::RectangleShape {
public:
    vector<sf::RectangleShape*> pillars;
    vector<sf::RectangleShape*> caps;
    sf::Texture texture;
    sf::Texture capTexture;

    Pillar(sf::Texture a, sf::Texture b);
    void createPillar();
    void reset();
    void updatePillars(sf::RenderWindow& window, Score& score);
};

