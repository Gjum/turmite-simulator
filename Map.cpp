#include "Map.h"

Map::Map() {
    Map(10, 10);
}
Map::Map(unsigned int newWidth, unsigned int newHeight) {
    width = newWidth;
    height = newHeight;

    cells = new unsigned char[width * height];
    untouchedCell = 10; // !!! ATTENTION: this will set the size of the color table !!!
    for (unsigned int i = 0; i < width * height; i++) {
        cells[i] = untouchedCell;
    }

    colorTable = new sf::Color[untouchedCell + 1];
    colorTable[untouchedCell] = sf::Color(230, 230, 230);
    colorTable[0] = sf::Color(255, 255, 255);
    colorTable[1] = sf::Color(0, 0, 0);
    twoColorTable = true;

    texture = new sf::Texture;
    image = new sf::Image();
    image->create(width, height, sf::Color(255, 128, 128));

    renderFunction = colorTableRenderer;
}
Map::~Map() {
    delete image;
    delete texture;
    delete [] colorTable;
    delete [] cells;
}

unsigned int Map::getWidth() const {
    return width;
}
unsigned int Map::getHeight() const {
    return height;
}
unsigned char Map::getCell(unsigned int x, unsigned int y) const {
    unsigned char cell = cells[x + width * y];
    if (cell == untouchedCell) return 0;
    return cell;
}
void Map::setCell(unsigned int x, unsigned int y, unsigned char value) {
    cells[x + width * y] = value;

    if (twoColorTable && value > 2) {
        twoColorTable = false;
        colorTable[0] = sf::Color(255, 255, 0);
        colorTable[1] = sf::Color(255, 0, 0);
        colorTable[2] = sf::Color(0, 0, 255);
        colorTable[3] = sf::Color(140, 70, 0);
        colorTable[4] = sf::Color(0, 255, 0);
        colorTable[5] = sf::Color(255, 128, 0);
        colorTable[6] = sf::Color(100, 200, 255);
    }
}
sf::Color Map::getColorAt(unsigned int x, unsigned int y) const {
    return colorTable[cells[x + width * y]];
}
void Map::setRenderFunction(void (* newRenderFunction)(sf::Image *, const Map *)) {
    renderFunction = newRenderFunction;
}

void Map::draw(sf::RenderTarget &window) const {
    renderFunction(image, this);

    texture->loadFromImage(*image);
    sf::Sprite sprite(*texture);
    window.draw(sprite);
}

///// Render functions /////

void colorTableRenderer(sf::Image *image, const Map *map) {
    // colorTable renderer
    for (unsigned int x = 0; x < map->getWidth(); x++) {
        for (unsigned int y = 0; y < map->getHeight(); y++) {
            image->setPixel(x, y, map->getColorAt(x, y));
        }
    }
}

void subpixelRenderer(sf::Image *image, const Map *map) {
    // 2x2 subpixel renderer
    for (unsigned int x = 0; x < map->getWidth(); x += 2) {
        for (unsigned int y = 0; y < map->getHeight(); y += 2) {
            sf::Color color = sf::Color(255, 0, 0);
            if (map->getCell(x, y) == 1
                    && map->getCell(x + 1, y + 1) == 1
                    && map->getCell(x + 1, y) == 2
                    && map->getCell(x, y + 1) == 2)
                color =  sf::Color(0, 255, 0);
            else if (map->getCell(x, y) == 2
                     && map->getCell(x + 1, y + 1) == 2
                     && map->getCell(x + 1, y) == 1
                     && map->getCell(x, y + 1) == 1)
                color =  sf::Color(0, 0, 255);

            image->setPixel(x, y, color);
            image->setPixel(x + 1, y, color);
            image->setPixel(x, y + 1, color);
            image->setPixel(x + 1, y + 1, color);
        }
    }
}
