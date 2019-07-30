#include "cKarabin.h"



cKarabin::cKarabin(sf::Vector2f xy)
{

	setTex("grafiki/karabin.png");
	setTexSize(1);
	setAttackSpeed(5);
	setDmg(10);
	setLvl(1);
	setRange(50);
	setPrice(100);
	setPosition(xy);
	setUpgradeCost(150);
	setRangeSphere();
	setType('K');
}


cKarabin::~cKarabin()
{
}

bool cKarabin::upgrade(int gold)
{
	if (getLvl() < 3) {
		if (gold >= getUpgradeCost()) {
			setAttackSpeed(getAttackSpeed() + 2);
			setDmg(getDmg() + 5);
			setLvl(getLvl() + 1);
			setRange(getRange() + 25);
			setRangeSphere();
			setUpgradeCost(getUpgradeCost() * 2 * getLvl());
			return true;
		}
		else return false;
	}
	else return false;

}
