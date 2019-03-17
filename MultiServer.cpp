#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <TGUI/TGUI.hpp>

int main(){
	//listens to a specific port on a network
	sf::TcpListener listener;
	sf::SocketSelector selector;
	bool done = false;
	std::vector<sf::TcpSocket*> clients;
	listener.listen(8127);
	selector.add(listener);
	
	float x;
	float y;
	float slide;
	char shape[1];
	char color[1];

	while(!done){
		if (selector.wait()){
			if (selector.isReady(listener)){
				sf::TcpSocket *socket = new sf::TcpSocket;
				listener.accept(*socket);
				sf::Packet packetID;
				std::string id;
				if (socket->receive(packetID) == sf::Socket::Done){
					packetID >> id;
					}
				std::cout << id << " has connected to Server: " << socket->getRemoteAddress() << std::endl;
				clients.push_back(socket);
				selector.add(*socket);
				}
				else{
					for(int i =0; i < (signed int)clients.size(); i++){
						if(selector.isReady(*clients[i])){
							sf::Packet packet, sendPacket;
							if(clients[i]->receive(packet) == sf::Socket::Done){
								packet >> x >> y >> slide >> color >> shape;
								std::cout << x << " " << y << " " << slide << " " << color << " " << shape << std::endl;
								sendPacket << x << y << slide << color << shape;
								for(int j = 0; j < (signed int)clients.size(); j++){
									if (i != j){
										clients[j]->send(sendPacket);
									}
								}
							}
						}
					}
				}
			}
		}
	
	for(std::vector<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++){
		delete *it;
	}
	
	return 0;
}
