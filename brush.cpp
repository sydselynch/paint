#include "brush.h"

Brush::Brush(float size, sf::Color color) {
    this->brushSize = size;
    this->brushColor = color;
    this->hasBorder = false;
    this->borderSize = 0;
    this->borderColor = sf::Color::White;
}

Brush::~Brush(){
}

void Brush::setBrushSize(float size) {
    this->brushSize = size;
}

void Brush::setBrushColor(sf::Color color) {
    this->brushColor = color;
}

void Brush::setBorder(float size, sf::Color color) {
    this->borderSize = size;
    this->borderColor = color;
}

void Brush::setBorderStatus(bool status) {
    this->hasBorder = status;
}

sf::RectangleShape Brush::getRectangle(float width, float height) {
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setFillColor(this->brushColor);
    rect.setOrigin(this->brushSize/2, this->brushSize/2);

    if (this->hasBorder) {
        rect.setOutlineColor(this->borderColor);
        rect.setOutlineThickness(this->borderSize);
    }

    return rect;
}

sf::CircleShape Brush::getCircle() {
    sf::CircleShape circle(this->brushSize);
    circle.setFillColor(this->brushColor);
    circle.setOrigin(this->brushSize, this->brushSize);

    if (this->hasBorder) {
        circle.setOutlineColor(this->borderColor);
        circle.setOutlineThickness(this->borderSize);
    }

    return circle;
}

sf::CircleShape Brush::getTriangle() {
    sf::CircleShape triangle(this->brushSize, 3);
    triangle.setFillColor(this->brushColor);
    triangle.setOrigin(this->brushSize, this->brushSize);

    if(this->hasBorder) {
        triangle.setOutlineColor(this->borderColor);
        triangle.setOutlineThickness(this->borderSize);
    }

    return triangle;
}

sf::CircleShape Brush::getSquare() {
    sf::CircleShape square(this->brushSize, 4);
    square.setFillColor(this->brushColor);
    square.setOrigin(this->brushSize, this->brushSize);

    if(this->hasBorder) {
        square.setOutlineColor(this->borderColor);
        square.setOutlineThickness(this->borderSize);
    }

    return square;
}

sf::CircleShape Brush::getOctagon() {
    sf::CircleShape octagon(this->brushSize, 8);
    octagon.setFillColor(this->brushColor);
    octagon.setOrigin(this->brushSize, this->brushSize);

    if(this->hasBorder) {
        octagon.setOutlineColor(this->borderColor);
        octagon.setOutlineThickness(this->borderSize);
    }

    return octagon;
}

sf::Vertex Brush::getVertex(sf::Vector2f position) {
    sf::Vertex vertex(sf::Vector2f(position), this->brushColor);

    return vertex;
}
