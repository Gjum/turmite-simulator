#ifndef TURMITE_HPP
#define TURMITE_HPP

#include "Map.hpp"

class Turmite {
    public:
        Turmite(Map* newMap, void (* newTransitionFunction)(Turmite*));
        ~Turmite();

        bool step(); // true if leaving map

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
        Map* map;
        int posX, posY, rotation;
        unsigned int state, stepCounter;
        void (* transitionFunction)(Turmite*);
};

#endif // TURMITE_HPP

