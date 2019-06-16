#include "cSnajperka.h"



cSnajperka::cSnajperka(sf::Vector2f xy)
{
	setTex("grafiki/snajperka.png");
	setTexSize(1);
	setAttackSpeed(2);
	setDmg(50);
	setLvl(1);
	setRange(250);
	setPrice(200);
	setPosition(xy);
	setUpgradeCost(300);
	setRangeSphere();
	setType('S');
}


cSnajperka::~cSnajperka()
{
}
bool cSnajperka::upgrade(int gold)
{
	if (getLvl() < 3) {
		if (gold >= getUpgradeCost()) {


			setAttackSpeed(getAttackSpeed() + 1);
			setDmg(getDmg() + 50);
			setLvl(getLvl() + 1);
			setRange(getRange() + 75);
			setUpgradeCost(getUpgradeCost() * 2.5 * getLvl());
			return true;
		}
		else return false;
	}
	else return false;
}