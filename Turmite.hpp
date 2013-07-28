#ifndef TURMITE_HPP
#define TURMITE_HPP

#include <string>
#include <Map.hpp>

struct TransitionTriple {
    unsigned char color;
    char direction; // TODO longer direction for splitting turmites
    unsigned char state;
};

class Turmite {
    public:
        Turmite();
        Turmite(Map *newMap, std::string transitionRule);
        Turmite(Map *newMap, void (* newTransitionFunction)(Turmite *));
        ~Turmite();

        bool step(); // true if leaving map

        bool setTransitionRule(std::string transitionRule);
        void setTransitionFunction(void (* newTransitionFunction)(Turmite *));
        void setPosition(unsigned int x, unsigned int y);
        void setRotation(unsigned int newRotation);
        unsigned int getStepsPassed() const;

        unsigned int getState() const;
        void setState(unsigned int newState);
        unsigned char getCell() const;
        void setCell(unsigned char value);
        void increaseCell(unsigned char max);

        void turnLeft();
        void turnRight();
        bool move(); // true if leaving map

    private:
        Map *map;
        int posX, posY;
        unsigned int rotation, state, stepCounter;

        void (* transitionFunction)(Turmite *);

        TransitionTriple *transitionTable;
        unsigned char numberOfColors;
        unsigned int numberOfStates;
        bool useTransitionRule;

        void init(Map *newMap);
        void transitionRule();
};

#endif // TURMITE_HPP
