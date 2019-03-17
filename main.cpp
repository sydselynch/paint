#include <TGUI/TGUI.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include "brush.h"
#include "UserInterface.h"

int main(){

    //prints local address/ connects to appropriate socket
	char mode;
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	std::cout << ip << std::endl;
	sf::TcpSocket socket;
	std::vector<sf::Vertex> getDraw;
	
	sf::Packet packet;
	char shapeSend;
	char colorSend = 'b';
    float xSend;
    float ySend;
    float slideSend;

	socket.connect(ip, 8127);
	
	std::string id;
	std::cout << "Enter an ID to start painting: ";
	std::cin >> id;
	
	sf::Packet packetID;
    packetID << id;
	socket.setBlocking(false);
	socket.send(packetID);

	std::cout << "Connected to: " << socket.getRemoteAddress() << std::endl;
	mode = 's';

    std::vector < sf::CircleShape > colorSelection;
    std::vector < sf::CircleShape > drawings;
    std::vector < sf::Vertex > pen;

    bool borderSelected = false;
    bool backgroundSelected = false;
    bool brushSelected = true;
    //bool drawGrid = false;
    unsigned int i;
    int mousedown = 0;
    UserInterface *interface = new UserInterface();

    sf::Color backgroundColor = sf::Color::White;
    sf::Color brushColor = sf::Color::Blue;

    sf::VideoMode resolution = sf::VideoMode().getDesktopMode();
    sf::RenderWindow window(resolution, "Paint", sf::Style::Fullscreen);
    sf::Image screenshot;

    //boundary lines
    sf::VertexArray lines = interface->initializeBoundaryLines(resolution);
    sf::VertexArray boundaries = interface->initializeBoundaries(resolution);

    // attach gui to window
    tgui::Gui gui{window};

    tgui::Button::Ptr clearButton = interface->clearButton();

    clearButton->connect("pressed", [&](){ drawings.clear(); });
    gui.add(clearButton);

    sf::IntRect rectangle;
    rectangle.height = resolution.height - 75;
    rectangle.width = resolution.width + 75;

    // copy to image
    sf::Texture tex;
    tex.create(resolution.width, resolution.height);
    sf::Image win;

    sf::IntRect r1(75,75, resolution.width, resolution.height);

    tgui::Button::Ptr save = tgui::Button::create();
    save->setPosition(20, 15);
    save->setText("Save Image");
    save->setSize(100, 40);
    save->connect("pressed", [&]() { win = window.capture(); tex.loadFromImage(win, r1); screenshot = tex.copyToImage(); screenshot.saveToFile("masterpiece.png");});
    gui.add(save);

    tgui::Button::Ptr close = interface->closeButton(resolution);
    close->connect("pressed", [&](){ window.close(); });
    gui.add(close);

    tgui::Slider::Ptr slider = interface->sliderBar();
    gui.add(slider);

    tgui::Button::Ptr undo = interface->undoButton();
    undo->connect("pressed", [&]() { if (interface->isPenTool()==false && drawings.size() > 0) { if (drawings.size() > 10) {for (int i = 0; i < 10; i++) {drawings.pop_back();}} else { drawings.pop_back();} } else if (interface->isPenTool() && pen.size() > 0) {pen.pop_back();} });
    gui.add(undo);

    tgui::Button::Ptr squareBrush = interface->squareBrush();
    gui.add(squareBrush);

    tgui::Button::Ptr circleBrush = interface->circleBrush();
    gui.add(circleBrush);

    tgui::Button::Ptr penTool = interface->penTool();
    gui.add(penTool);

    tgui::Button::Ptr triangleBrush = interface->triangleBrush();
    gui.add(triangleBrush);

    tgui::Button::Ptr octagonBrush = interface->octagonBrush();
    gui.add(octagonBrush);

    tgui::Button::Ptr gridButton = interface->gridButton();
    gridButton->connect("pressed", [&](){ if (interface->gridSelected()) {interface->setGrid(false);} else { interface->setGrid(true);} });
    gui.add(gridButton);

    tgui::CheckBox::Ptr background = interface->backgroundCheckbox();
    tgui::CheckBox::Ptr brush = interface->brushCheckbox();
    background->connect("checked", [&]() { brush->uncheck(); backgroundSelected=true; brushSelected=false;});
    gui.add(background);

    brush->check();
    brush->connect("checked", [&]() { background->uncheck(); backgroundSelected=false; brushSelected=true;});
    gui.add(brush);

    // color selection buttons //
    Brush *blue = new Brush(25, sf::Color::Blue);
    Brush *green = new Brush(25, sf::Color::Green);
    Brush *yellow = new Brush(25, sf::Color::Yellow);
    Brush *black = new Brush(25, sf::Color::Black);
    Brush *white = new Brush(25, sf::Color::White);
    Brush *red = new Brush (25, sf::Color::Red);
    Brush *magenta = new Brush(25, sf::Color::Magenta);
    Brush *cyan = new Brush(25, sf::Color::Cyan);
    colorSelection.push_back(blue->getSquare());
    colorSelection.push_back(green->getSquare());
    colorSelection.push_back(yellow->getSquare());
    colorSelection.push_back(black->getSquare());
    colorSelection.push_back(white->getSquare());
    colorSelection.push_back(red->getSquare());
    colorSelection.push_back(magenta->getSquare());
    colorSelection.push_back(cyan->getSquare());

    // Ability to draw a grid
    sf::VertexArray gridLat = interface->intializegridLat(resolution);
    sf::VertexArray gridLong = interface->initializegridLong(resolution);

    tgui::Button::Ptr brushColorBlue = interface->brushColorBlue();
    brushColorBlue->connect("pressed", [&](){ if (brushSelected) {brushColor = sf::Color::Blue;colorSend = 'b';} else {backgroundColor=sf::Color::Blue;}});
    gui.add(brushColorBlue);

    tgui::Button::Ptr brushColorGreen = interface->brushColorGreen();
    brushColorGreen->connect("pressed", [&](){ if (brushSelected) {brushColor = sf::Color::Green;colorSend = 'G';} else {backgroundColor=sf::Color::Green;}});
    gui.add(brushColorGreen);

    tgui::Button::Ptr brushColorYellow = interface->brushColorYellow();
    brushColorYellow->connect("pressed", [&](){ if (brushSelected) {brushColor = sf::Color::Yellow;colorSend = 'y';} else {backgroundColor=sf::Color::Yellow;}});
    gui.add(brushColorYellow);

    tgui::Button::Ptr brushColorBlack = interface->brushColorBlack();
    brushColorBlack->connect("pressed", [&](){ if (brushSelected) {brushColor = sf::Color::Black;colorSend = 'B';} else {backgroundColor=sf::Color::Black;}});
    gui.add(brushColorBlack);

    tgui::Button::Ptr brushColorWhite = interface->brushColorWhite();
    brushColorWhite->connect("pressed", [&](){ if (brushSelected) {brushColor = sf::Color::White;colorSend = 'w';} else {backgroundColor=sf::Color::White;}});
    gui.add(brushColorWhite);

    tgui::Button::Ptr brushColorRed = interface->brushColorRed();
    brushColorRed->connect("pressed", [&](){ if (brushSelected) {brushColor = sf::Color::Red;colorSend = 'r';} else {backgroundColor=sf::Color::Red;}});
    gui.add(brushColorRed);

    tgui::Button::Ptr brushColorMagenta = interface->brushColorMagenta();
    brushColorMagenta->connect("pressed", [&](){ if (brushSelected) {brushColor = sf::Color::Magenta;colorSend = 'm';} else {backgroundColor=sf::Color::Magenta;}});
    gui.add(brushColorMagenta);

    tgui::Button::Ptr brushColorCyan = interface->brushColorCyan();
    brushColorCyan->connect("pressed", [&](){ if (brushSelected) {brushColor = sf::Color::Cyan;colorSend = 'c';} else {backgroundColor=sf::Color::Cyan;}});
    gui.add(brushColorCyan);

    Brush *brushStroke = new Brush(slider->getValue(), brushColor);
	Brush *brushReceive = new Brush(slider->getValue(), brushColor);
	
    while(window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }

            gui.handleEvent(e);

        }

        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        sf::CircleShape cursor;

//        if (drawings.size() > 5000) {
//            sf::Sprite sprite;
//            win = window.capture();
//            window.draw(win);
//            drawings.clear();
//        }

        float slideNum = slider->getValue();
        if((mouse.x - (slideNum / 2)) <= 100 && (mouse.y - (slideNum / 2)) <= 150){
            window.setMouseCursorVisible(true);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // Left click draws current brush
                mousedown = 1;
                sf::CircleShape stroke;
                sf::Vertex penStroke;
                brushStroke->setBrushSize(slideNum);
                brushStroke->setBrushColor(brushColor);

                if (borderSelected) {
                    brushStroke->setBorderStatus(true);
                    brushStroke->setBorder(5, sf::Color::Black);
                }

                if (interface->isSquareBrush()) {
                    stroke = brushStroke->getSquare();
                    stroke.setRotation(45);
                    stroke.setPosition((float)mouse.x, (float)mouse.y);
                    if (mode == 's' && mousedown == 1){
						shapeSend = 's';
						slideSend = slider->getValue();						
						xSend = sf::Mouse::getPosition().x;
						ySend = sf::Mouse::getPosition().y;
						packet << xSend << ySend << slideSend << colorSend << shapeSend;
						socket.send(packet);
						//window.draw(cursor);
						mode = 'r';
					}
                }

                else if (interface->isCircleBrush()) {
                    stroke = brushStroke->getCircle();
                    stroke.setPosition((float)mouse.x, (float)mouse.y);
                    if (mode == 's' && mousedown == 1){
						shapeSend = 's';
						slideSend = slider->getValue();						
						xSend = sf::Mouse::getPosition().x;
						ySend = sf::Mouse::getPosition().y;
						packet << xSend << ySend << slideSend << colorSend << shapeSend;
						socket.send(packet);
						//window.draw(cursor);
						mode = 'r';
					}
                }

                else if (interface->isTriangleBrush()) {
                    stroke = brushStroke->getTriangle();
                    stroke.setPosition((float)mouse.x, (float)mouse.y);
                    if (mode == 's' && mousedown == 1){
						shapeSend = 's';
						slideSend = slider->getValue();						
						xSend = sf::Mouse::getPosition().x;
						ySend = sf::Mouse::getPosition().y;
						packet << xSend << ySend << slideSend << colorSend << shapeSend;
						socket.send(packet);
						//window.draw(cursor);
						mode = 'r';
					}
                }

                else if (interface->isOctagonBrush()) {
                    stroke = brushStroke->getOctagon();
                    stroke.setPosition((float)mouse.x, (float)mouse.y);
                    if (mode == 's' && mousedown == 1){
						shapeSend = 's';
						slideSend = slider->getValue();						
						xSend = sf::Mouse::getPosition().x;
						ySend = sf::Mouse::getPosition().y;
						packet << xSend << ySend << slideSend << colorSend << shapeSend;
						socket.send(packet);
						//window.draw(cursor);
						mode = 'r';
					}
                }

                else if (interface->isPenTool()) {
                    sf::Vertex penStroke = brushStroke->getVertex(sf::Vector2f(mouse));
                }

                //Checks and preserves boundaries
                if (interface->isPenTool() && (mouse.x - (slideNum / 2) > 70) && (mouse.y - (slideNum / 2) > 60)) {
                    pen.push_back(penStroke);
                }
                else {
                    if ((mouse.x - (slideNum / 2)) > 70 && (mouse.y - (slideNum / 2)) > 60) {
                        drawings.push_back(stroke);
                    }
                }
            }

            else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                // Set right click to "erase"
                mousedown = 1;
                brushStroke->setBrushColor(backgroundColor);
                sf::CircleShape eraserShape = brushStroke->getSquare();
                eraserShape.setPosition((float)mouse.x, (float)mouse.y);
                eraserShape.setRotation(45);
                if (mode == 's' && mousedown == 1){
					slideSend = slider->getValue();
					xSend = sf::Mouse::getPosition().x;
					ySend = sf::Mouse::getPosition().y;
					packet << xSend << ySend << slideSend << 'w' << 's';
					socket.send(packet);
					//window.draw(cursor);
					mode = 'r';
				}

                if ((mouse.x - (slideNum / 2)) > 70 && (mouse.y - (slideNum / 2)) > 60) {
                        drawings.push_back(eraserShape);
                }
            }

            else if(sf::Event::MouseButtonReleased){
				mousedown = 0;
			}

        window.clear(backgroundColor);

        // Draw vector of shapes
        for (i = 0; i < drawings.size(); i++) {
            window.draw(drawings[i]);
        }

        //window.draw(&pen[0], pen.size(), sf::LinesStrip);

        // Draw grid lines
        if (interface->gridSelected()) {
            window.draw(gridLat);
            window.draw(gridLong);
        }

        // Sets cursor to be current brush
        brushStroke->setBrushSize(slideNum);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            brushStroke->setBrushColor(backgroundColor);
        }

        else {
            brushStroke->setBrushColor(brushColor);
        }

        brushStroke->setBorder(2, sf::Color::Black);
        brushStroke->setBorderStatus(true);

        if (interface->isSquareBrush()) {
            sf::CircleShape cursor = brushStroke->getSquare();
            cursor.setRotation(45);
            cursor.setPosition((float)mouse.x, (float)mouse.y);
            if((mouse.x < 75) || (mouse.y < 75)){
                window.setMouseCursorVisible(true);
            }
            else {
                window.setMouseCursorVisible(false);
                window.draw(cursor);
                brushStroke->setBorderStatus(false);
            }
        }

        else if (interface->isCircleBrush()) {
            sf::CircleShape cursor = brushStroke->getCircle();
            cursor.setPosition((float)mouse.x, (float)mouse.y);
            if((mouse.x < 70) || (mouse.y < 70)){
                window.setMouseCursorVisible(true);
            }

            else {
                window.setMouseCursorVisible(false);
                window.draw(cursor);
                brushStroke->setBorderStatus(false);
            }
        }

        else if (interface->isPenTool()) {
            brushStroke->setBrushSize(2);
            sf::CircleShape cursor = brushStroke->getCircle();
            cursor.setPosition((float)mouse.x, (float)mouse.y);
            if((mouse.x < 70) || (mouse.y < 70)){
                window.setMouseCursorVisible(true);
            }

            else {
                window.setMouseCursorVisible(false);
                window.draw(cursor);
                brushStroke->setBorderStatus(false);
            }
        }

        else if (interface->isTriangleBrush()) {
            sf::CircleShape cursor = brushStroke->getTriangle();
            cursor.setPosition((float)mouse.x, (float)mouse.y);
            if((mouse.x < 70) || (mouse.y < 70)){
                window.setMouseCursorVisible(true);
            }

            else {
                window.setMouseCursorVisible(false);
                window.draw(cursor);
                brushStroke->setBorderStatus(false);
            }
        }

        else if (interface->isOctagonBrush()) {
            sf::CircleShape cursor = brushStroke->getOctagon();
            cursor.setPosition((float)mouse.x, (float)mouse.y);
            if((mouse.x < 70) || (mouse.y < 70)){
                window.setMouseCursorVisible(true);
            }

            else {
                window.setMouseCursorVisible(false);
                window.draw(cursor);
                brushStroke->setBorderStatus(false);
            }
        }

        // Draw boundaries
        window.draw(boundaries);

        // Draw color selection buttons
        float x = 850;
        float y = 38;
        for (i = 0; i < colorSelection.size(); i++) {
            colorSelection[i].setPosition(x, y);
            colorSelection[i].setRotation(45);
            colorSelection[i].setOutlineColor(sf::Color::Black);
            colorSelection[i].setOutlineThickness(3);
            x+=50;
            window.draw(colorSelection[i]);
        }
        
        if (mode == 'r'){
			socket.receive(packet);
			std::cout << "Received: " << xSend << " " << ySend << " " << slideSend << " " << colorSend << " " << shapeSend << std::endl;
			sf::CircleShape strokeReceive;
			if (colorSend == 'b'){
				brushReceive->setBrushColor(sf::Color::Blue);
			}
			if (colorSend == 'g'){
				brushReceive->setBrushColor(sf::Color::Green);
			}
			if (colorSend == 'y'){
				brushReceive->setBrushColor(sf::Color::Yellow);				
			}
			if (colorSend == 'B'){
				brushReceive->setBrushColor(sf::Color::Black);				
			}
			if (colorSend == 'w'){
				brushReceive->setBrushColor(sf::Color::White);				
			}
			if (colorSend == 'r'){
				brushReceive->setBrushColor(sf::Color::Red);				
			}
			if (colorSend == 'm'){
				brushReceive->setBrushColor(sf::Color::Magenta);				
			}
			if (colorSend == 'c'){
				brushReceive->setBrushColor(sf::Color::Cyan);				
			}
			strokeReceive = brushReceive->getCircle();
			strokeReceive.setPosition(xSend,ySend);
			
			window.draw(strokeReceive);
			
            //getDraw.push_back(strokeReceive);
			//getDraw.push_back(stroke);
			//getDraw.push_back(sf::Vertex(sf::Vector2f(xSend,ySend),sf::Color::Black));
			//window.draw(&getDraw[0], getDraw.size(), sf::LinesStrip);
			//for (i = 0; i < getDraw.size(); i++) {
			//	window.draw(getDraw[i]);
			//}
			mode = 's';
		}
		
        gui.draw();
        window.draw(lines);
        window.display();
    }

    return 0;
}
