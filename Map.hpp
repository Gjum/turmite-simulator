#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>

class Map {
    public:
        Map();
        Map(unsigned int newWidth, unsigned int newHeight);
        ~Map();

        unsigned int getWidth() const;
        unsigned int getHeight() const;
        unsigned char getCell(unsigned int x, unsigned int y) const;
        void setCell(unsigned int x, unsigned int y, unsigned char value);
        sf::Color getColorAt(unsigned int x, unsigned int y) const;
        void setRenderFunction(void (* newRenderFunction)(sf::Image *, const Map *));

        void draw(sf::RenderTarget &window) const;

    private:
        unsigned int width, height;
        unsigned char *cells;
        unsigned char untouchedCell;
        sf::Color *colorTable;
        bool twoColorTable;
        sf::Image *image;
        sf::Texture *texture;
        void (* renderFunction)(sf::Image *, const Map *);
};

void colorTableRenderer(sf::Image *image, const Map *map);
void subpixelRenderer(sf::Image *image, const Map *map);

#endif // MAP_HPP
