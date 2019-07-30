#pragma once
#include "cRoad.h"

using namespace sf;
using namespace std;
class cTowerPlace
{
public:
	cTowerPlace(Vector2f pos) {

		towerPlaceTexture_.loadFromFile("grafiki/towerPlace.png");
		towerPlace_.setTexture(towerPlaceTexture_);
		towerPlace_.setScale(40.0 / 32, 40.0 / 33);
		towerPlace_.setOrigin(16, 15.5);
		towerPlace_.setPosition(pos);
	}
	~cTowerPlace() {

	}
	bool collision(Vector2f pos) {
		if (towerPlace_.getGlobalBounds().contains(pos)) return true;
		else return false;
	}
	void draw(RenderWindow &w) {
		w.draw(towerPlace_);
	}
	void claimPlace() {
		isFree_ = false;
	}

	bool isFree() {
		return isFree_;
	}
	Vector2f getPosition() {
		return towerPlace_.getPosition();
	}
private:
	Sprite towerPlace_;
	Texture towerPlaceTexture_;
	bool isFree_ = true;
};


