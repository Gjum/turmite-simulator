#include <iostream>

#include <SFML/Window.hpp>

#include <Transitions.hpp>
#include <Turmite.hpp>
#include <Map.hpp>

// TODO custom color table
// TODO rendering and turmites in separate threads

int main(int argc, char *argv[]) {
    std::cout << "Turmite simulator by Gjum\n";
    std::cout << "http://github.com/Gjum/turmite-simulator\n";
    std::cout << "\n";

    unsigned int width = 320;
    unsigned int height = 180;
    unsigned int numberOfTurmites = 1;
    unsigned int stepsBetweenRenders = 1;

    bool pauseAtBorder = true;

    void (* transitionFunction)(Turmite *) = Turmite_Biotope;

    if (argc > 1) {
        std::string turmiteName(argv[1]);

        if (turmiteName.compare(0, 6, "Ant_RL") == 0)
            transitionFunction = Ant_RL;
        else if (turmiteName.compare(0, 8, "Ant_RRLL") == 0)
            transitionFunction = Ant_RRLL;
        else if (turmiteName.compare(0, 9, "Ant_RRLRR") == 0)
            transitionFunction = Ant_RRLRR;

        else if (turmiteName.compare(0, 15, "Turmite_Biotope") == 0)
            transitionFunction = Turmite_Biotope;
        else if (turmiteName.compare(0, 15, "Turmite_Pulsing") == 0)
            transitionFunction = Turmite_Pulsing;
        else if (turmiteName.compare(0, 17, "Turmite_Fibonacci") == 0)
            transitionFunction = Turmite_Fibonacci;
        else if (turmiteName.compare(0, 14, "Turmite_Qrcode") == 0)
            transitionFunction = Turmite_Qrcode;
        else if (turmiteName.compare(0, 11, "Turmite_Foo") == 0)
            transitionFunction = Turmite_Foo;
    }
    if (argc > 2) {
        numberOfTurmites = atoi(argv[2]);
    }
    if (argc > 3) {
        stepsBetweenRenders = atoi(argv[3]);
    }

    sf::RenderWindow window(sf::VideoMode(width, height), "Turmite");
    // adjust window if too small
    if (width < 100 && height < 100)
        window.setSize(sf::Vector2u(100, 100));

    Map *map = new Map(width, height);
    map->setRenderFunction(colorTableRenderer);

    Turmite *turmites[numberOfTurmites];
    for (int i = 0; i < numberOfTurmites; i++) {
        turmites[i] = new Turmite(map, transitionFunction);
    }

    std::cout << "Starting with mapsize " << width << "x" << height << "\n";
    if (numberOfTurmites != 1) std::cout << numberOfTurmites << " Turmites\n";
    else std::cout << "1 Turmite\n";
    std::cout << "Render every ";
    if (stepsBetweenRenders != 1) std::cout << stepsBetweenRenders << " steps\n";
    else std::cout << "step\n";
    std::cout << "To pause or resume, click on the window.\n";
    std::cout << "\n";

    bool paused = false;
    while (window.isOpen()) {
        sf::Event Event;
        while (window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                window.close();
            if (Event.type == sf::Event::Resized)
                window.setView(sf::View(sf::Vector2f(width / 2.0, height / 2.0),
                                        sf::Vector2f(width, height)));
            if (Event.type == sf::Event::MouseButtonPressed) {
                paused = !paused;
                if (paused) std::cout << "paused at " << turmites[0]->getStepsPassed() << " steps     \n";
            }
        }

        for (int i = stepsBetweenRenders; i > 0 && !paused; i--) {
            bool hitBorder = false;
            for (int i = 0; i < numberOfTurmites; i++) {
                if (turmites[i]->step()) hitBorder = true;
            }
            // pause when hitting map's border
            if (hitBorder && pauseAtBorder) {
                paused = true;
                std::cout << "crossing border at " << turmites[0]->getStepsPassed() << " steps\n";
                std::cout << "To continue in a torus, click on the window.\n";
                pauseAtBorder = false;
            }
            else std::cout << "running for " << turmites[0]->getStepsPassed() << " steps\r";
        }

        window.clear();

        map->draw(window);

        window.display();
    }

    std::cout << "Program terminated after " << turmites[0]->getStepsPassed() << " steps\n";

    for (int i = 0; i < numberOfTurmites; i++) delete turmites[i];
    delete map;

    return EXIT_SUCCESS;
}
