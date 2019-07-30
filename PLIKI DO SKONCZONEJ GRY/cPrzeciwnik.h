#pragma once
#include "cBron.h"
using namespace sf;
using namespace std;
class cPrzeciwnik
{



public:
	cPrzeciwnik(Vector2f position) {

		setTex();
		position_ = position;
		monster_.setPosition(position_);
		hp_ = 110;
	}
	~cPrzeciwnik() {

	}


	bool colision(Sprite s) {
		if (s.getGlobalBounds().contains(monster_.getPosition())) return true;
		else return false;
	}
	bool colision(CircleShape s) {
		if (s.getGlobalBounds().contains(monster_.getPosition())) return true;
		else return false;
	}
	bool colision(Sprite s, int x) {
		if (s.getGlobalBounds().intersects(monster_.getGlobalBounds())) return true;
		else return false;
	}
	void draw(RenderWindow &w) {
		w.draw(monster_);
	}
	bool isDead(int dmg) {
		hp_ -= dmg;
		if (hp_ <= 0) return true;
		else return false;
	}
	void animate(int instruction, Vector2f pos, Sprite s) {

		if (colision(s)) {


			switch (instruction) {
			case 4: {
				if ((monster_.getPosition().x > pos.x - 1) && (monster_.getPosition().x < pos.x + 1)) {
					monster_.setPosition(pos.x, monster_.getPosition().y);
					monster_.setRotation(270);
					velocity_ = Vector2f(0.0, -1.0);

				}
				break;
			}
			case 5: {

				if ((monster_.getPosition().x > pos.x - 1) && (monster_.getPosition().x < pos.x + 1)) {
					monster_.setPosition(pos.x, monster_.getPosition().y);
					monster_.setRotation(90);
					velocity_ = Vector2f(0.0, 1.0);

				}
				break;
			}
			case 6: {
				if ((monster_.getPosition().y > pos.y - 1) && (monster_.getPosition().y < pos.y + 1)) {
					monster_.setPosition(monster_.getPosition().x, pos.y);
					monster_.setRotation(0);
					velocity_ = Vector2f(1.0, 0.0);

				}
				break;
			}
			case 7: {
				if ((monster_.getPosition().y > pos.y - 1) && (monster_.getPosition().y < pos.y + 1)) {
					monster_.setPosition(monster_.getPosition().x, pos.y);
					monster_.setRotation(180);
					velocity_ = Vector2f(-1.0, 0.0);

				}
				break;
			}
			}
		}

	}
	void animate() {
		changeTex();
		monster_.move(velocity_.x, velocity_.y);

		texnr_++;
		if (texnr_ == 60) {
			texnr_ = 0;
		}
	}
	int ifSurvive() {
		if (monster_.getPosition().x > 1250) {
			return 1;
		}
		else return 0;
	}
	Vector2f getPos() {

		return monster_.getPosition();
	}
private:

	void setTex() {
		mt1_.loadFromFile("grafiki/monster1.png");
		mt2_.loadFromFile("grafiki/monster2.png");
		mt3_.loadFromFile("grafiki/monster3.png");
		mt4_.loadFromFile("grafiki/monster4.png");
		monster_.setTexture(mt1_);
		monster_.setOrigin(mt1_.getSize().x / 2, mt1_.getSize().y / 2);
		monster_.setScale(2, 2);


	}
	void changeTex() {
		switch (texnr_) {
		case 0: {
			monster_.setTexture(mt1_);
			break;
		}

		case 10: {
			monster_.setTexture(mt2_);
			break;
		}

		case 20: {
			monster_.setTexture(mt3_);
			break;
		}

		case 30: {
			monster_.setTexture(mt4_);
			break;
		}
		case 40: {
			monster_.setTexture(mt3_);
			break;
		}
		case 50: {
			monster_.setTexture(mt2_);
			break;
		}
		}
	}
	int hp_;
	int texnr_ = 1;
	Vector2f velocity_;
	Vector2f position_;
	Sprite monster_;
	Texture mt1_, mt2_, mt3_, mt4_;
	int gold_;
};



