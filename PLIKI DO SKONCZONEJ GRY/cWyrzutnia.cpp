#include "cWyrzutnia.h"



cWyrzutnia::cWyrzutnia(sf::Vector2f xy)
{

	setTex("grafiki/wyrzutnia.png");
	setTexSize(1);
	setAttackSpeed(1);
	setDmg(50);
	setLvl(1);
	setRange(150);
	setPrice(250);
	setPosition(xy);
	setUpgradeCost(500);
	setRangeSphere();

	setType('W');
}


cWyrzutnia::~cWyrzutnia()
{
}
bool cWyrzutnia::upgrade(int gold)
{
	if (getLvl() < 3) {
		if (gold >= getUpgradeCost()) {
			if (getLvl() == 2)
			{
				setAttackSpeed(getAttackSpeed() + 1);
			}
			setDmg(getDmg() + 50);
			setLvl(getLvl() + 1);
			setRange(getRange() + 50);
			setUpgradeCost(getUpgradeCost() * 3 * getLvl());
			return true;
		}
		else return false;
	}
	else return false;
}