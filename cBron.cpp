#include "cBron.h"



cBron::cBron() {

}

cBron::~cBron(){

}

void cBron::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->tower_, state);
}

bool cBron::upgrade(int gold)
{
	return false;
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
	tower_.rotate(1);
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
	this->rangeSphere_.setRadius(this->range_);
	this->rangeSphere_.setOrigin(range_, range_);
	this->rangeSphere_.setPosition(this->center_);
	this->rangeSphere_.setOutlineColor(sf::Color::Black);
	this->rangeSphere_.setOutlineThickness(2);
	this->rangeSphere_.setFillColor(sf::Color::Transparent);
}


sf::Vector2f cBron::getPosition()
{

	return this->center_;
}
