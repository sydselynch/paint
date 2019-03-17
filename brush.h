#ifndef BRUSH_H
#define BRUSH_H

#include <TGUI/TGUI.hpp>

class Brush
{
    public:
        Brush(float size, sf::Color color);
        virtual ~Brush();

        void setBrushSize(float size);
        void setBrushColor(sf::Color color);
        void setBorder(float thickness, sf::Color color);
        void setBorderStatus(bool status);


        sf::RectangleShape getRectangle(float width, float height);
        sf::CircleShape getCircle();
        sf::CircleShape getTriangle();
        sf::CircleShape getSquare();
        sf::CircleShape getOctagon();
        sf::Vertex getVertex(sf::Vector2f position);


    private:
        bool hasBorder;
        float brushSize;
        float borderSize;

        sf::Color brushColor;
        sf::Color borderColor;

};

#endif // BRUSH_H
