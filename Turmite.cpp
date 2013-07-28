#include "Turmite.hpp"

Turmite::Turmite() {
    init(0);
}
Turmite::Turmite(Map *newMap, void (* newTransitionFunction)(Turmite *)) {
    init(newMap);
    setTransitionFunction(newTransitionFunction);
}
Turmite::Turmite(Map *newMap, std::string newTransitionRule) {
    init(newMap);
    setTransitionRule(newTransitionRule);
}
Turmite::~Turmite() {
    if (transitionTable != 0) delete [] transitionTable;
}

// returns true on success
bool Turmite::setTransitionRule(std::string newTransitionRule) {
    useTransitionRule = false;
    transitionFunction = 0;

    if (newTransitionRule.length() <= 0) return false;

    unsigned int numberOfCommas = 0;
    unsigned int numberOfOpeningBraces = 0;

    for (auto character : newTransitionRule) {
        if (character == ',') numberOfCommas++;
        else if (character == '{') numberOfOpeningBraces++;
    }

    unsigned int numberOfTriples = (numberOfCommas + 1) / 3;
    numberOfStates = numberOfOpeningBraces - 1 - numberOfTriples;
    numberOfColors = numberOfTriples / numberOfStates;

    if (transitionTable != 0) delete [] transitionTable;
    transitionTable = new TransitionTriple[numberOfTriples];

    if (transitionTable == 0) return false;

    unsigned int begin = 0;
    unsigned int end = 0;
    std::string subStr = "";

    for (unsigned char readState = 0; readState < numberOfStates; readState++) {
        for (unsigned int readColor = 0; readColor < numberOfColors; readColor++) {
            TransitionTriple &triple = transitionTable[readState * numberOfColors + readColor];

            for (unsigned int triplePart = 0; triplePart < 3; triplePart++) {
                begin = newTransitionRule.find_first_of("0123456789NSEW", end);
                end = newTransitionRule.find_first_not_of("0123456789NSEW", begin);

                if (begin == std::string::npos) return false;
                if (end == std::string::npos) return false;

                subStr = newTransitionRule.substr(begin, end - begin);

                if (subStr.length() <= 0) return false;

                if (triplePart == 0) triple.color = atoi(subStr.c_str());
                else if (triplePart == 1) triple.direction = subStr[0]; // TODO longer direction for splitting turmites
                else if (triplePart == 2) triple.state = atoi(subStr.c_str());
                else return false;
            }
        }
    }

    useTransitionRule = true;

    return true;
}
void Turmite::setTransitionFunction(void (* newTransitionFunction)(Turmite *)) {
    transitionFunction = newTransitionFunction;
}

// true if leaving map
bool Turmite::step() {
    if (map == 0) return false;
    stepCounter++;

    if (useTransitionRule) transitionRule();
    else transitionFunction(this);

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
    rotation = (rotation + 3) % 4; // +3 equals -1
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

void Turmite::init(Map *newMap) {
    map = newMap;
    posX = map->getWidth() / 2;
    posY = map->getHeight() / 2;
    rotation = 0;
    state = 0;
    stepCounter = 0;

    transitionFunction = 0;

    transitionTable = 0;
    numberOfColors = 0;
    numberOfStates = 0;
    useTransitionRule = false;
}
void Turmite::transitionRule() {
    TransitionTriple triple = transitionTable[state * numberOfColors + getCell()];

    setCell(triple.color);
    state = triple.state;

    if (triple.direction == '2') turnRight();
    else if (triple.direction == '8') turnLeft();
}
