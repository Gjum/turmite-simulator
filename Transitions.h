#include <Turmite.h>

///// Ant transition functions /////

void Ant_RL(Turmite *turmite) {
    if (turmite->getCell() == 0) turmite->turnRight();
    else turmite->turnLeft();
    turmite->increaseCell(2);
}

void Ant_RRLL(Turmite *turmite) {
    if (turmite->getCell() <= 1) turmite->turnLeft();
    else turmite->turnRight();
    turmite->increaseCell(4);
}

void Ant_RRLRR(Turmite *turmite) {
    if (turmite->getCell() == 2) turmite->turnLeft();
    else turmite->turnRight();
    turmite->increaseCell(5);
}

///// Turmite transition functions /////

// simulating competing species
void Turmite_Biotope(Turmite *turmite) {
    if (turmite->getState() == 0) {
        if (turmite->getCell() == 0) {
            turmite->setCell(1);
            turmite->turnRight();
            turmite->setState(0);
        }
        else {
            turmite->setCell(1);
            turmite->turnLeft();
            turmite->setState(1);
        }
    }
    else {
        if (turmite->getCell() == 0) {
            turmite->setCell(0);
            turmite->turnRight();
            turmite->setState(0);
        }
        else {
            turmite->setCell(0);
            turmite->setState(0);
        }
    }
}

// alternating between creating and destroying every 10k steps
void Turmite_Pulsing(Turmite *turmite) {
    if (turmite->getStepsPassed() % 20000 < 10000) {
        if (turmite->getCell() == 0) {
            if (turmite->getState() == 0) {
                turmite->setCell(1);
                turmite->setState(1);
            }
            else {
                turmite->setState(0);
                turmite->setCell(1);
                turmite->turnLeft();
            }
        }
        else {
            if (turmite->getState() == 0) {
            }
            else {
                turmite->setState(0);
                turmite->setCell(0);
                turmite->turnLeft();
            }
        }
    }
    else {
        if (turmite->getCell() == 0) {
            if (turmite->getState() == 0) {
                turmite->setState(1);
            }
            else {
            }
        }
        else {
            if (turmite->getState() == 0) {
            }
            else {
                turmite->setState(0);
                turmite->setCell(0);
                turmite->turnLeft();
            }
        }
    }
}

// building a fibonacci spiral
// {{{1, 8, 1}, {1, 8, 1}}, {{1, 2, 1}, {0, 1, 0}}}
void Turmite_Fibonacci(Turmite *turmite) {
    if (turmite->getState() == 0) {
        if (turmite->getCell() == 0) {
            turmite->setCell(1);
            turmite->turnLeft();
            turmite->setState(1);
        }
        else {
            turmite->setCell(1);
            turmite->turnLeft();
            turmite->setState(1);
        }
    }
    else {
        if (turmite->getCell() == 0) {
            turmite->setCell(1);
            turmite->turnRight();
            turmite->setState(1);
        }
        else {
            turmite->setCell(0);
            turmite->setState(0);
        }
    }
}

// buiding a distinctive growing square pattern
// {{{1, 8, 0}, {1, 2, 1}}, {{0, 2, 0}, {0, 8, 1}}}
void Turmite_Qrcode(Turmite *turmite) {
    if (turmite->getState() == 0) {
        if (turmite->getCell() == 0) {
            turmite->setCell(1);
            turmite->turnLeft();
            turmite->setState(0);
        }
        else {
            turmite->setCell(1);
            turmite->turnRight();
            turmite->setState(1);
        }
    }
    else {
        if (turmite->getCell() == 0) {
            turmite->setCell(0);
            turmite->turnRight();
            turmite->setState(0);
        }
        else {
            turmite->setCell(0);
            turmite->turnLeft();
            turmite->setState(1);
        }
    }
}

// buiding a chaotic distinctive pattern
// {{{1, 2, 1}, {1, 8, 1}}, {{1, 2, 1}, {0, 2, 0}}}
void Turmite_Foo(Turmite *turmite) {
    if (turmite->getState() == 0) {
        if (turmite->getCell() == 0) {
            turmite->setCell(1);
            turmite->turnRight();
            turmite->setState(1);
        }
        else {
            turmite->setCell(1);
            turmite->turnLeft();
            turmite->setState(1);
        }
    }
    else {
        if (turmite->getCell() == 0) {
            turmite->setCell(1);
            turmite->turnRight();
            turmite->setState(1);
        }
        else {
            turmite->setCell(0);
            turmite->turnRight();
            turmite->setState(0);
        }
    }
}

/*/// old code /////

//// Biotope Turmite --------------------
//    if (getCell() == 1) {
//        if (state == 0) {
//            turnRight();
//            setCell(2);
//            state = 0;
//        }
//        else {
//            turnRight();
//            setCell(1);
//            state = 0;
//        }
//    }
//    else {
//        if (state == 0) {
//            turnLeft();
//            setCell(2);
//            state = 1;
//        }
//        else {
//            setCell(1);
//            state = 0;
//        }
//    }
//
//// ------------------------------------

//// pulsing Turmite --------------------
//    if (getStepsPassed() % 20000 < 10000) {
//        if (getCell() == 1) {
//            if (state == 0) {
//                setCell(2);
//                state = 1;
//            }
//            else {
//                state = 0;
//                setCell(2);
//                turnLeft();
//            }
//        }
//        else {
//            if (state == 0) {
//            }
//            else {
//                state = 0;
//                setCell(1);
//                turnLeft();
//            }
//        }
//    }
//    else {
//        if (getCell() == 1) {
//            if (state == 0) {
//                state = 1;
//            }
//            else {
//            }
//        }
//        else {
//            if (state == 0) {
//            }
//            else {
//                state = 0;
//                setCell(1);
//                turnLeft();
//            }
//        }
//    }
//// ------------------------------------

//// RL Ant -----------------------------
//    if (getCell() == 1) turnRight();
//    else turnLeft();
//    increaseCell(2);
//// ------------------------------------

//// RRLRR Ant --------------------------
//    if (getCell() == 3) turnLeft();
//    else turnRight();
//    increaseCell(5);
//// ------------------------------------

//// RRLL Ant ---------------------------
//    if (getCell() == 1 || getCell() == 2) turnLeft();
//    else turnRight();
//    increaseCell(4);
//// ------------------------------------

*/
