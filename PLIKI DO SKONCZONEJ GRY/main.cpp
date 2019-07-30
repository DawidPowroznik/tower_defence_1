#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <list>
#include "cBron.h"
#include "cKarabin.h"
#include "cSnajperka.h"
#include "cWyrzutnia.h"
#include "cPrzeciwnik.h"
#include "cRoad.h"
#include "cTowerPlace.h"
#include "cPocisk.h"


std::vector<cBron> towers; //vector przechowywujacy wszystkie postawione wiezyczki
sf::Vector2i WindowSize = sf::Vector2i(1280, 720); //Vector okreslajacy rozmiar okna gry
sf::Vector2i MousePosition; //vector intigerow - pozycja myszy
std::vector<cBron> icon;
std::vector<cRoad*> mapSprites;
std::vector<cTowerPlace*> towerPlaces;
std::vector<string> mapka;
std::list<cPrzeciwnik*> enemies;
std::list<cPocisk*> bullets;
cBron carriedTower;
int playerHp = 10;
int playerGold = 1000;
int timer = 0;
bool upgradeButton = true;
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
void makeMap() {
	fstream file;
	file.open("mapa.txt", std::ios::in);

	while (!file.eof()) {
		string line;
		getline(file, line);
		if (line[0] == '*') break;
		else mapka.push_back(line);
	}
	file.close();

	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++)
		{
			if (mapka[i][j] == '2') {
				cTowerPlace *towerPlace = new cTowerPlace(Vector2f(20 + j * 40, 20 + i * 40));
				towerPlaces.push_back(towerPlace);
			}
			else if (mapka[i][j] != '0') {
				cRoad *dirt = new cRoad(mapka[i][j], 20 + j * 40, 20 + i * 40);

				mapSprites.push_back(dirt);

			}

			else {

			}
		}
	}
}
sf::RenderWindow window(sf::VideoMode(WindowSize.x, WindowSize.y), "Tower Defence - Dawid Powroznik", sf::Style::Close | sf::Style::Titlebar);
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
		else if (itr->collisionWithMouse(sf::Vector2f(MousePosition)) && itr->getPrice() > playerGold); //std::cout << "Brak hajsu";



	}
	carriedTower.setPosition(sf::Vector2f(MousePosition));

	if (timer % 60 == 0 && upgradeButton == false)upgradeButton = true;
}

void handleBuyingTowers() {
	if (!(carriedTower.getType() == NULL)) {
		for (int i = 0; i < towerPlaces.size(); i++)
		{
			if (towerPlaces[i]->collision(Vector2f(MousePosition.x, MousePosition.y)) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && towerPlaces[i]->isFree()) {
				towerPlaces[i]->claimPlace();
				carriedTower.setPosition(towerPlaces[i]->getPosition());
				towers.push_back(carriedTower);
				playerGold -= carriedTower.getPrice();
				carriedTower.setType(NULL);

			}
		}


	}
}
//obsluga obracania sie wiezyczek
void handleTowers() {

	for (int i = 0; i < towers.size(); i++)
	{
		if (towers[i].getTower().getGlobalBounds().contains(float(MousePosition.x), float(MousePosition.y)) && Mouse::isButtonPressed(Mouse::Right) && upgradeButton) {
			upgradeButton = false;
			towers[i].upgrade(playerGold);

		}
		towers[i].animate();
		for (auto itr = enemies.begin(); itr != enemies.end(); itr++)
		{

			if ((*itr)->colision(towers[i].getRangeSphere())) {
				//cout << "hejka";
				towers[i].shoot(bullets, (*itr)->getPos());
			}
		}



	}
}
//rysowanie postawionych wiezyczek
void drawinTowers() {
	for (int i = 0; i < towers.size(); i++)
	{
		window.draw(towers[i].getRangeSphere());
		window.draw(towers[i]);

	}
}
void drawinMap() {
	for (int i = 0; i < mapSprites.size(); i++)
	{
		mapSprites[i]->draw(window);
	}
	for (int i = 0; i < towerPlaces.size(); i++)
	{
		towerPlaces[i]->draw(window);
	}
}
void mouse() {

}
void handleMoving() {


	for (int i = 0; i < mapSprites.size(); i++)
	{
		for (auto itr = enemies.begin(); itr != enemies.end(); itr++)
		{
			(*itr)->animate(mapSprites[i]->getInstruction(), mapSprites[i]->getPos(), mapSprites[i]->getSprite());
		}

	}
	for (auto itr = enemies.begin(); itr != enemies.end();)
	{
		(*itr)->animate();
		if ((*itr)->ifSurvive()) {
			playerHp -= 1;
			itr = enemies.erase(itr);
		}
		else itr++;

	}



}
void drawinEnemies() {

	for (auto itr = enemies.begin(); itr != enemies.end(); itr++)
	{
		(*itr)->draw(window);
	}
}
void spawnEnemies() {
	if (timer % 180 == 0) {

		cPrzeciwnik *e = new cPrzeciwnik(Vector2f(20.0, 140.0));
		enemies.push_back(e);
	}

}
void handleBullets() {

	for (auto itr = bullets.begin(); itr != bullets.end(); itr++)
	{
		(*itr)->animate();
		(*itr)->draw(window);
	}
}
void handleEnemies() {





	for (auto ktr = enemies.begin(); ktr != enemies.end(); ktr++)
	{
		for (auto itr = bullets.begin(); itr != bullets.end();)
		{
			if ((*ktr)->colision((*itr)->getBullet(), 1)) {


				if ((*ktr)->isDead((*itr)->dealDmg())) {
					ktr = enemies.erase(ktr);
				}
				itr = bullets.erase(itr);
			}
			else itr++;
		}
	}
}


int main()
{
	sf::Texture background;
	background.loadFromFile("grafiki/tlo.png");
	sf::Sprite backgroundSprite(background);
	window.setFramerateLimit(60);
	makeInterface();
	cPrzeciwnik e(Vector2f(100.0, 100.0));
	makeMap();

	while (window.isOpen())
	{
		
		//cout << bullets.size() << endl;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		timer++;
		window.clear();
		MousePosition = sf::Mouse::getPosition(window);
		handleBuyingTowers();
		handleTowers();
		spawnEnemies();

		handleInterface();

		//rysowanie wszystkiego
		std::cout << playerGold << std::endl;
		window.draw(backgroundSprite);
		drawinMap();
		drawInterface();
		handleMoving();
		drawinEnemies();
		if (carriedTower.getType() != NULL) { window.draw(carriedTower); }


		drawinTowers();
		handleBullets();
		handleEnemies();
		window.display();
		if (timer == 360) {
			timer = 0;
		}
	}



	return 0;
}