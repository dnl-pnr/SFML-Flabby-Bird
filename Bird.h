#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
using namespace std;

class Bird : virtual public sf::Sprite {
public:
	sf::Sprite shape;
	double ySpeed = 0;
	double rotationChange = 0;
	double angle = -20;
	int rotateTimer = 0;
	int currentFrame = 0;
	vector<sf::Texture> frames;
	int frameCount = 0;
	int frameSpeed = 3;

	Bird(vector<sf::Texture> a);
	void birdJump(sf::RenderWindow& window);
	void birdUpdate(sf::RenderWindow& window);
	void birdAnimate();
	void birdReset();
};