#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <list>
#include "cBron.h"
#include "cKarabin.h"
#include "cSnajperka.h"
#include "cWyrzutnia.h"


std::vector<cBron> towers; //vector przechowywujacy wszystkie postawione wiezyczki
sf::Vector2i WindowSize = sf::Vector2i(1280, 720); //Vector okreslajacy rozmiar okna gry
sf::Vector2i MousePosition; //pozycja myszy
std::vector<cBron> icon;
cBron carriedTower;
int playerGold = 1000;
bool kolizja(sf::Sprite &przeszkoda, sf::Sprite &gracz)
{

	sf::FloatRect obiekt1(przeszkoda.getGlobalBounds());
	sf::FloatRect obiekt2(gracz.getGlobalBounds());

	if (obiekt1.intersects(obiekt2))
	{
		return true;
	}
	else return false;
}
void makeInterface() {

	cKarabin *karabinek = new cKarabin(sf::Vector2f(450, 675));
	karabinek->setTexSize(2);
	icon.push_back(*karabinek);
	cSnajperka *snajperka = new cSnajperka(sf::Vector2f(600, 675));
	snajperka->setTexSize(2);
	icon.push_back(*snajperka);
	cWyrzutnia *wyrzutnia = new cWyrzutnia(sf::Vector2f(750, 675));
	wyrzutnia->setTexSize(2);
	icon.push_back(*wyrzutnia);

}

sf::RenderWindow window(sf::VideoMode(WindowSize.x, WindowSize.y), "Dawid Powroznik - Tower Defence", sf::Style::Close | sf::Style::Titlebar);
//rysowanie ikonek na interfejsie na dolnym pasku
void drawInterface()
{
	for (auto itr = icon.begin(); itr != icon.end(); itr++)
	{
		window.draw(*itr);
	}
}
//obsluga ikonek na pasku dolnym
void handleInterface() {

	for (auto itr = icon.begin(); itr != icon.end(); itr++)
	{

		if (itr->collisionWithMouse(sf::Vector2f(MousePosition)) && itr->getPrice() <= playerGold)
		{
			std::cout << playerGold << std::endl;
			char type = itr->getType();
			if (type == 'K') {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					cKarabin *temp = new cKarabin(sf::Vector2f(MousePosition));
					carriedTower = *temp;

				}
			}
			else if (type == 'S') {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					cSnajperka *temp = new cSnajperka(sf::Vector2f(MousePosition));
					carriedTower = *temp;
				}
			}
			else if (type == 'W') {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					cWyrzutnia *temp = new cWyrzutnia(sf::Vector2f(MousePosition));
					carriedTower = *temp;
				}
			}


		}
		else if (itr->collisionWithMouse(sf::Vector2f(MousePosition)) && itr->getPrice() > playerGold)std::cout <<playerGold<< " - Brak hajsu"<<std::endl;



	}
	carriedTower.setPosition(sf::Vector2f(MousePosition));
}
//obsluga kupowania wiezyczek, dodawanie 
void handleBuyingTowers() {
	if (!(carriedTower.getType() == NULL)) {
		if (MousePosition.y < 600 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			towers.push_back(carriedTower);
			playerGold -= carriedTower.getPrice();
			carriedTower.setType(NULL);

		}

	}
}
//obracanie sie wiezyczek
void handleTowers() {
	for (int i = 0; i < towers.size(); i++)
	{
		towers[i].animate();
	}
}
//rysowanie postawionych wiezyczek
void drawinTowers() {
	for (int i = 0; i < towers.size(); i++)
	{
		
		window.draw(towers[i]);


	}
}

void mouse() {

}




int main()
{
	sf::Texture background;
	background.loadFromFile("grafiki/tlo.png");
	sf::Sprite backgroundSprite(background);
	window.setFramerateLimit(60);
	makeInterface();



	while (window.isOpen())
	{
		window.clear();

		MousePosition = sf::Mouse::getPosition(window);
		handleBuyingTowers();
		handleTowers();
		//std::cout << "Pozycja myszy x: " << MousePosition.x << ", y: " << MousePosition.y << std::endl;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		handleInterface();
		//rysowanie wszystkiego
		window.draw(backgroundSprite);
		drawInterface();
		if (carriedTower.getType() != NULL) { window.draw(carriedTower); }
		drawinTowers();
		window.display();

	}



	return 0;
}