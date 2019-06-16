#pragma once
#include<SFML\Graphics.hpp>


class cBron :public sf::Drawable
{
public:


	cBron();
	~cBron();

	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	bool upgrade(int gold);
	void move(sf::Vector2f distance);
	void setPosition(sf::Vector2f xy);
	sf::Vector2f getPosition();
	int getDmg();
	int getPrice();
	int getAttackSpeed();
	int getLvl();
	int getRange();
	sf::Sprite getTower();
	int getUpgradeCost();
	sf::CircleShape getRangeSphere();
	void setTexSize(float value);
	bool collisionWithMouse(sf::Vector2f coordinates);
	char getType();
	void setType(char type);
	void animate();

protected:


	void setTex(std::string direction);
	void setDmg(int dmg);
	void setPrice(int price);
	void setAttackSpeed(int as);
	void setLvl(int lvl);
	void setRange(int range);

	void setUpgradeCost(int value);

	void setRangeSphere();


private:
	sf::Sprite tower_;
	sf::Texture text_;
	int price_;
	int attack_speed_;
	int dmg_;
	int range_;
	int lvl_;
	int upgrade_cost_;
	float radius_ = 50.0;
	sf::Vector2f center_;
	sf::CircleShape rangeSphere_;
	char type_ = NULL;
};
