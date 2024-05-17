#include "Bird.h"
#include <vector>

Bird::Bird(vector<sf::Texture> a) {
    shape = *(new sf::Sprite);
    frames = a;
    shape.setTexture(frames.at(currentFrame));
    shape.setScale(.1, .1);
    shape.setOrigin(150, 200);
}

void Bird::birdJump(sf::RenderWindow& window) {
    shape.move(0, 10);
    shape.setPosition(150, shape.getPosition().y ); //snap to proper x
    ySpeed = -16;
    angle = -20;
    shape.setRotation(angle);
    rotationChange = 0;
    rotateTimer = 0;
    window.draw(shape);
}

void Bird::birdUpdate(sf::RenderWindow& window) {
    shape.move(0, ySpeed);
    ++frameCount;
    ++rotateTimer;

    if (frameCount == frameSpeed) { //changes framerate of bird
        birdAnimate();
        frameCount = 0;
    }
    
    //does the falling animation
    if (rotateTimer > 15) { //after certain "floating time," starts to fall
        rotationChange = 8;
        shape.setTexture(frames.at(1)); //sets to "diving" texture
    }
    if (angle > 90) { //when facing down, stop rotating
        rotationChange = 0;
    }
    shape.setRotation(angle + rotationChange);
    shape.move(.4 * rotationChange, 0); //moves object to counter rotation x movement
    angle += rotationChange; //new angle
    
    //fall speed
    if (ySpeed < 15) {
        ySpeed += 2;
    }
    window.draw(shape);
}

void Bird::birdAnimate() {
    if (currentFrame < 2) {
        ++currentFrame;
    }
    else {
        currentFrame = 0;
    }
    shape.setTexture(frames.at(currentFrame));
}

void Bird::birdReset() {
    ySpeed = 0;
    rotationChange = 0;
    angle = 0;
    rotateTimer = 0;
    currentFrame = 0;
    frameCount = 0;
    shape.setPosition(150, 200);
    shape.setRotation(angle);
}