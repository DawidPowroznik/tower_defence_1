#pragma once
#include "cBron.h"
using namespace sf;
using namespace std;
class cRoad
{
public:

	cRoad(char type, int x, int y) {
		item_texture_.loadFromFile("grafiki/ziemia.png");
		item_.setTexture(item_texture_);
		item_.setScale(40.0 / 300.0, 40.0 / 300.0);
		item_.setOrigin(150.0, 150.0);

		item_.setPosition(x, y);

		switch (type) {
		case '4': {instruction_ = 4; break; }
		case '5': {instruction_ = 5; break; }
		case '6': {instruction_ = 6; break; }
		case '7': {instruction_ = 7; break; }
		case '2': {instruction_ = 2; break; }
		}


	}
	~cRoad() {

	}
	void draw(RenderWindow &w) {
		w.draw(item_);
	}
	int getInstruction() {
		return instruction_;
	}
	Sprite getSprite() {
		return item_;
	}
	Vector2f getPos() {
		return item_.getPosition();
	}
private:
	Sprite item_;
	Texture item_texture_;
	int instruction_;

};



