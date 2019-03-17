#include "UserInterface.h"

UserInterface::UserInterface(){
    this->squareSelected = true;
    this->circleSelected = false;
    this->penSelected = false;
    this->triangleSelected = false;
    this->octagonSelected = false;
    this->drawGrid = false;
}

UserInterface::~UserInterface(){
}

bool UserInterface::isSquareBrush() {
    return this->squareSelected;
}

bool UserInterface::isCircleBrush() {
    return this->circleSelected;
}

bool UserInterface::isPenTool() {
    return this->penSelected;
}

bool UserInterface::isTriangleBrush() {
    return this->triangleSelected;
}

bool UserInterface::isOctagonBrush() {
    return this->octagonSelected;
}

bool UserInterface::gridSelected() {
    return this->drawGrid;
}

void UserInterface::setSquare() {
    this->squareSelected = true;
    this->circleSelected = false;
    this->penSelected = false;
    this->triangleSelected = false;
    this->octagonSelected = false;
}

void UserInterface::setCircle() {
    this->squareSelected = false;
    this->circleSelected = true;
    this->penSelected = false;
    this->triangleSelected = false;
    this->octagonSelected = false;
}

void UserInterface::setPen() {
    this->squareSelected = false;
    this->circleSelected = false;
    this->penSelected = true;
    this->triangleSelected = false;
    this->octagonSelected = false;
}

void UserInterface::setTriangle() {
    this->squareSelected = false;
    this->circleSelected = false;
    this->penSelected = false;
    this->triangleSelected = true;
    this->octagonSelected = false;
}

void UserInterface::setOctagon() {
    this->squareSelected = false;
    this->circleSelected = false;
    this->penSelected = false;
    this->triangleSelected = false;
    this->octagonSelected = true;
}

void UserInterface::setGrid(bool status) {
    this->drawGrid = status;
}

sf::VertexArray UserInterface::initializeBoundaryLines(sf::VideoMode resolution) {
    sf::VertexArray lines(sf::Lines, 4);
    lines[0].position = sf::Vector2f(75, 75);
    lines[1].position = sf::Vector2f(resolution.width, 75);
    lines[2].position = sf::Vector2f(75, 74);
    lines[3].position = sf::Vector2f(75, resolution.height);
    for (int i = 0; i < 4; i++) {
        lines[i].color = sf::Color::Black;
    }

    return lines;
}

sf::VertexArray UserInterface::initializeBoundaries(sf::VideoMode resolution) {
    sf::VertexArray boundaries(sf::Quads, 8);
    boundaries[0].position = sf::Vector2f(0, 0);
    boundaries[1].position = sf::Vector2f(resolution.width, 0);
    boundaries[2].position = sf::Vector2f(resolution.width, 75);
    boundaries[3].position = sf::Vector2f(0, 75);
    boundaries[4].position = sf::Vector2f(0, 0);
    boundaries[5].position = sf::Vector2f(75, 0);
    boundaries[6].position = sf::Vector2f(75, resolution.height);
    boundaries[7].position = sf::Vector2f(0, resolution.height);
    for (int i = 0; i < 8; i++) {
        boundaries[i].color = sf::Color::White;
    }

    return boundaries;
}

tgui::Button::Ptr UserInterface::clearButton() {
    tgui::Button::Ptr clearbutton = tgui::Button::create();
    clearbutton->setPosition(150, 15);
    clearbutton->setText("Clear");
    clearbutton->setSize(100, 40);

    return clearbutton;

}

tgui::Button::Ptr UserInterface::closeButton(sf::VideoMode resolution) {
    tgui::Button::Ptr close = tgui::Button::create();
    close->setPosition(resolution.width-55, (resolution.height+15)-(resolution.height));
    close->setText("X");
    close->setSize(35, 35);

    return close;
}

tgui::Slider::Ptr UserInterface::sliderBar(){
    tgui::Slider::Ptr slider = tgui::Slider::create();
    slider->setPosition(30, 200);
    slider->setSize(20, 200);
    slider->setMinimum(5);
    slider->setMaximum(75);

    return slider;

}

tgui::Button::Ptr UserInterface::undoButton() {
    tgui::Button::Ptr undo = tgui::Button::create();
    undo->setPosition(280, 15);
    undo->setText("Undo");
    undo->setSize(100, 40);

    return undo;
}

tgui::Button::Ptr UserInterface::squareBrush() {
    tgui::Button::Ptr squareBrush = tgui::Button::create();
    squareBrush->setPosition(450, 15);
    squareBrush->setSize(45, 45);
    squareBrush->setText("Square");
    squareBrush->connect("pressed", [&](){ this->setSquare(); });


    return squareBrush;
}

tgui::Button::Ptr UserInterface::circleBrush() {
    tgui::Button::Ptr circleBrush = tgui::Button::create();
    circleBrush->setPosition(520, 15);
    circleBrush->setSize(45, 45);
    circleBrush->setText("Circle");
    circleBrush->connect("pressed", [&](){ this->setCircle(); });

    return circleBrush;
}

tgui::Button::Ptr UserInterface::penTool() {
    tgui::Button::Ptr penTool = tgui::Button::create();
    penTool->setPosition(600, 15);
    penTool->setSize(45, 45);
    penTool->setText("Pen");
    penTool->setOpacity(0);
    penTool->connect("pressed", [&](){ this->setPen(); });

    return penTool;
}

tgui::Button::Ptr UserInterface::triangleBrush() {
    tgui::Button::Ptr triangleBrush = tgui::Button::create();
    triangleBrush->setPosition(675, 15);
    triangleBrush->setSize(45, 45);
    triangleBrush->setText("Triangle");
    triangleBrush->connect("pressed", [&](){ this->setTriangle(); });

    return triangleBrush;
}

tgui::Button::Ptr UserInterface::octagonBrush() {
    tgui::Button::Ptr octagonBrush = tgui::Button::create();
    octagonBrush->setPosition(750, 15);
    octagonBrush->setSize(45, 45);
    octagonBrush->setText("Octagon");
    octagonBrush->connect("pressed", [&](){ this->setOctagon(); });

    return octagonBrush;
}

tgui::Button::Ptr UserInterface::gridButton() {
    tgui::Button::Ptr gridButton = tgui::Button::create();
    gridButton->setPosition(25, 80);
    gridButton->setSize(30, 30);
    gridButton->setText("Grid");

    return gridButton;
}

tgui::CheckBox::Ptr UserInterface::backgroundCheckbox() {
    tgui::CheckBox::Ptr background = tgui::CheckBox::create();
    background->setPosition(1300, 20);
    background->setSize(30, 30);
    background->setText("Background Color");

    return background;
}

tgui::CheckBox::Ptr UserInterface::brushCheckbox() {
    tgui::CheckBox::Ptr brush = tgui::CheckBox::create();
    brush->setPosition(1550, 20);
    brush->setSize(30, 30);
    brush->setText("Brush Color");

    return brush;
}

sf::VertexArray UserInterface::intializegridLat(sf::VideoMode resolution) {
    sf::VertexArray gridLat(sf::Lines, (resolution.height/12.5));
    for(int i = 6; i < (resolution.height/12.5); i += 2){
        gridLat[i - 6].position = sf::Vector2f(75, (12.5 * i));
        gridLat[i - 6].color = sf::Color(0,0,0,100);
        gridLat[i - 5].position = sf::Vector2f(resolution.width, (12.5 * i));
        gridLat[i - 5].color = sf::Color(0,0,0,100);
    }

    return gridLat;
}

sf::VertexArray UserInterface::initializegridLong(sf::VideoMode resolution) {
    sf::VertexArray gridLong(sf::Lines, (resolution.width/12.5));
    for(int i = 6; i < (resolution.width/12.5); i += 2){
        gridLong[i - 6].position = sf::Vector2f((12.5 * i), 75);
        gridLong[i - 6].color = sf::Color(0,0,0,100);
        gridLong[i - 5].position = sf::Vector2f((12.5 * i), resolution.height);
        gridLong[i - 5].color = sf::Color(0,0,0,100);
    }

    return gridLong;
}

tgui::Button::Ptr UserInterface::brushColorBlue(){
    tgui::Button::Ptr brushColorBlue = tgui::Button::create();
    brushColorBlue->setPosition(832, 20);
    brushColorBlue->setOpacity(0);
    brushColorBlue->setSize(35, 35);

    return brushColorBlue;

}

tgui::Button::Ptr UserInterface::brushColorGreen(){
    tgui::Button::Ptr brushColorGreen = tgui::Button::create();
    brushColorGreen->setPosition(882, 20);
    brushColorGreen->setOpacity(0);
    brushColorGreen->setSize(35, 35);

    return brushColorGreen;

}

tgui::Button::Ptr UserInterface::brushColorYellow(){
    tgui::Button::Ptr brushColorYellow = tgui::Button::create();
    brushColorYellow->setPosition(932, 20);
    brushColorYellow->setOpacity(0);
    brushColorYellow->setSize(35, 35);

    return brushColorYellow;
}

tgui::Button::Ptr UserInterface::brushColorBlack(){
    tgui::Button::Ptr brushColorBlack = tgui::Button::create();
    brushColorBlack->setPosition(982, 20);
    brushColorBlack->setOpacity(0);
    brushColorBlack->setSize(35, 35);

    return brushColorBlack;
}

tgui::Button::Ptr UserInterface::brushColorWhite(){
    tgui::Button::Ptr brushColorWhite = tgui::Button::create();
    brushColorWhite->setPosition(1032, 20);
    brushColorWhite->setOpacity(0);
    brushColorWhite->setSize(35, 35);

    return brushColorWhite;
}

tgui::Button::Ptr UserInterface::brushColorRed(){
    tgui::Button::Ptr brushColorRed = tgui::Button::create();
    brushColorRed->setPosition(1082, 20);
    brushColorRed->setOpacity(0);
    brushColorRed->setSize(35, 35);

    return brushColorRed;
}

tgui::Button::Ptr UserInterface::brushColorMagenta(){
    tgui::Button::Ptr brushColorMagenta = tgui::Button::create();
    brushColorMagenta->setPosition(1132, 20);
    brushColorMagenta->setOpacity(0);
    brushColorMagenta->setSize(35, 35);

    return brushColorMagenta;

}

tgui::Button::Ptr UserInterface::brushColorCyan(){
    tgui::Button::Ptr brushColorCyan = tgui::Button::create();
    brushColorCyan->setPosition(1182, 20);
    brushColorCyan->setOpacity(0);
    brushColorCyan->setSize(35, 35);

    return brushColorCyan;
}
