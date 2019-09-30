#pragma once
#include "cBron.h"
using namespace sf;
using namespace std;
class cPocisk
{
	friend class cBron;
public:
	cPocisk(Vector2f pe, Vector2f pt, char type) {
		type_ = type;
		float angle = atan2((pe.y - pt.y), (pe.x - pt.x)) * 180 / 3.14;
		switch (type_) {
		case 'W': {
			setTex("grafiki/pW.png");
			bullet_.setScale(20.0 / 384.0, 15.0 / 306.0);
			bullet_.setOrigin(192, 153);
			bullet_.rotate(angle);
			velocityMultiplicator_ = 1;
			dmg_ = 50;

			break;
		}
		case 'S': {
			setTex("grafiki/pS.png");
			bullet_.setScale(13.5 / 813.0, 5.0 / 306.0);
			bullet_.setOrigin(406, 153);
			bullet_.rotate(angle);
			velocityMultiplicator_ = 5;
			dmg_ = 50;
			break;
		}
		case 'K': {
			setTex("grafiki/pK.png");
			bullet_.setScale(10.0 / 414.0, 10.0 / 204.0);
			bullet_.setOrigin(207, 204);
			velocityMultiplicator_ = 2;
			dmg_ = 10;
			break;
		}

		}
		bullet_.setPosition(pt);
		Vector2f vektor = pe - pt;
		Vector2f vektor_normal = vektor / sqrt(pow(vektor.x, 2) + pow(vektor.y, 2));


		velocity_ = Vector2f(velocityMultiplicator_*vektor_normal.x, velocityMultiplicator_*vektor_normal.y);
	}
	~cPocisk() {
	}

	int dealDmg() {
		return dmg_;
	}


	void setTex(string dir) {
		bulletTexture_.loadFromFile(dir);
		bullet_.setTexture(bulletTexture_);
	}
	void animate() {
		bullet_.move(velocity_);
	}
	void draw(RenderWindow &w) {
		w.draw(bullet_);
	}
	Sprite getBullet() {
		return bullet_;
	}
private:
	Vector2f velocity_;
	Sprite bullet_;
	Texture bulletTexture_;
	char type_;
	float velocityMultiplicator_;
	int dmg_;

};



