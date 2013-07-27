#include "Turmite.h"

Turmite::Turmite(Map* newMap, void (* newTransitionFunction)(Turmite*)) {
    map = newMap;
    transitionFunction = newTransitionFunction;

    posX = map->getWidth() / 2;
    posY = map->getHeight() / 2;
    rotation = 0;

    state = 0;
    stepCounter = 0;
}
Turmite::~Turmite() {
}

// true if leaving map
bool Turmite::step() {
    stepCounter++;

    if (transitionFunction != 0) transitionFunction(this);

    return move();
}

void Turmite::setPosition(unsigned int x, unsigned int y) {
    posX = x;
    posY = y;
}
void Turmite::setRotation(unsigned int newRotation) {
    rotation = newRotation;
}
unsigned int Turmite::getStepsPassed() const {
    return stepCounter;
}

unsigned int Turmite::getState() const {
    return state;
}
void Turmite::setState(unsigned int newState) {
    state = newState;
}

unsigned char Turmite::getCell() const {
    return map->getCell(posX, posY);
}
void Turmite::setCell(unsigned char value) {
    map->setCell(posX, posY, value);
}
void Turmite::increaseCell(unsigned char max) {
    setCell((getCell() + 1) % max);
}

void Turmite::turnLeft() {
    rotation = (rotation + 3) % 4;
}
void Turmite::turnRight() {
    rotation = (rotation + 1) % 4;
}

// true if leaving map
bool Turmite::move() {
// direction
//   0
// 3   1
//   2
    if (rotation == 0) posY--;
    else if (rotation == 1) posX++;
    else if (rotation == 2) posY++;
    else if (rotation == 3) posX--;

    // Torus
    if (posX < 0 || posY < 0 || posX >= map->getWidth() || posY >= map->getHeight()) {
        posX = (posX + map->getWidth()) % map->getWidth();
        posY = (posY + map->getHeight()) % map->getHeight();

        return true;
    }

    return false;
}
