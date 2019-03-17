#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <TGUI/TGUI.hpp>

class UserInterface
{
    public:
        UserInterface();
        virtual ~UserInterface();
        bool isSquareBrush();
        bool isCircleBrush();
        bool isPenTool();
        bool isTriangleBrush();
        bool isOctagonBrush();
        bool gridSelected();
        void setSquare();
        void setCircle();
        void setPen();
        void setTriangle();
        void setOctagon();
        void setGrid(bool status);

        sf::VertexArray initializeBoundaryLines(sf::VideoMode resolution);
        sf::VertexArray initializeBoundaries(sf::VideoMode resolution);
        sf::VertexArray intializegridLat(sf::VideoMode resolution);
        sf::VertexArray initializegridLong(sf::VideoMode resolution);
        tgui::Button::Ptr clearButton();
        tgui::Button::Ptr closeButton(sf::VideoMode resolution);
        tgui::Slider::Ptr sliderBar();
        tgui::Button::Ptr undoButton();
        tgui::Button::Ptr squareBrush();
        tgui::Button::Ptr circleBrush();
        tgui::Button::Ptr penTool();
        tgui::Button::Ptr triangleBrush();
        tgui::Button::Ptr octagonBrush();
        tgui::Button::Ptr gridButton();
        tgui::CheckBox::Ptr backgroundCheckbox();
        tgui::CheckBox::Ptr brushCheckbox();
        tgui::Button::Ptr brushColorBlue();
        tgui::Button::Ptr brushColorGreen();
        tgui::Button::Ptr brushColorYellow();
        tgui::Button::Ptr brushColorBlack();
        tgui::Button::Ptr brushColorWhite();
        tgui::Button::Ptr brushColorRed();
        tgui::Button::Ptr brushColorMagenta();
        tgui::Button::Ptr brushColorCyan();

    private:
        bool squareSelected;
        bool circleSelected;
        bool penSelected;
        bool octagonSelected;
        bool triangleSelected;
        bool drawGrid;

};

#endif // USERINTERFACE_H
