#include "cBron.h"
#include<iostream>


cBron::cBron() {

}

cBron::~cBron()
{
}

void cBron::shoot(std::list<cPocisk*>& p, Vector2f pos)
{
	float angle = atan2((pos.y - tower_.getPosition().y), (pos.x - tower_.getPosition().x)) * 180 / 3.14;
	angle_ = angle;
	if (shootAcces_) {
		cPocisk *temp = new cPocisk(pos, tower_.getPosition(), getType());
		p.push_back(temp);
		shootAcces_ = false;
	}
}

void cBron::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->tower_, state);
}

bool cBron::upgrade(int &gold)
{
	std::cout << getUpgradeCost() << std::endl;
	switch (type_) {
	case 'K': {
		if (getLvl() < 3) {
			if (gold >= getUpgradeCost()) {
				gold -= getUpgradeCost();
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
		break;
	}
	case 'W': {
		if (getLvl() < 3) {
			if (gold >= getUpgradeCost()) {
				gold -= getUpgradeCost();
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
		break;
	}
	case 'S': {
		if (getLvl() < 3) {
			if (gold >= getUpgradeCost()) {
				gold -= getUpgradeCost();

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

		break;
	}
	}
}


int cBron::getDmg() {
	return dmg_;
}
int cBron::getPrice() {
	return price_;
}
int cBron::getAttackSpeed() {
	return attack_speed_;
}
int cBron::getLvl() {
	return lvl_;
}
int cBron::getRange() {
	return range_;
}

sf::Sprite cBron::getTower()
{
	return this->tower_;
}

int cBron::getUpgradeCost()
{
	return this->upgrade_cost_;
}

sf::CircleShape cBron::getRangeSphere()
{
	return this->rangeSphere_;
}

void cBron::setTex(std::string direction)
{
	this->text_.loadFromFile(direction);
	this->tower_.setTexture(this->text_);

}

void cBron::setDmg(int dmg) {
	this->dmg_ = dmg;
}
void cBron::setPrice(int price) {
	this->price_ = price;
}
void cBron::setAttackSpeed(int as) {
	this->attack_speed_ = as;
}
void cBron::setLvl(int lvl) {
	this->lvl_ = lvl;
}
void cBron::setRange(int range) {
	this->range_ = range;
}

void cBron::setTexSize(float value)
{

	this->tower_.setScale(sf::Vector2f(value, value));
	this->tower_.setOrigin(this->text_.getSize().x / 2, this->text_.getSize().y / 2);
}

bool cBron::collisionWithMouse(sf::Vector2f coordinates)
{
	if (this->tower_.getGlobalBounds().contains(coordinates)) {
		return true;
	}
	else return false;

}

char cBron::getType()
{
	return this->type_;
}

void cBron::setUpgradeCost(int value)
{
	this->upgrade_cost_ = value;
}

void cBron::setType(char type)
{
	this->type_ = type;
}

void cBron::animate()
{
	rangeSphere_.setPosition(tower_.getPosition());
	if (timer_ % (360 / attack_speed_) == 0 && timer_ != 0) {
		shootAcces_ = true;
	}
	if (timer_ == 360)
	{
		timer_ = 0;
	}

	tower_.setRotation(angle_);
	timer_++;
}

void cBron::move(sf::Vector2f distance)
{
	this->center_ += distance;
	this->tower_.setPosition(this->center_);
}

void cBron::setPosition(sf::Vector2f xy)
{
	this->center_ = xy;
	this->tower_.setPosition(this->center_);
}


void cBron::setRangeSphere() {
	rangeSphere_.setRadius(range_);
	rangeSphere_.setOrigin(range_, range_);
	rangeSphere_.setPosition(center_);
	rangeSphere_.setOutlineColor(sf::Color::Black);

	rangeSphere_.setFillColor(sf::Color::Transparent);
}


sf::Vector2f cBron::getPosition()
{

	return this->center_;
}
