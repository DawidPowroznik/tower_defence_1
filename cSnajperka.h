#pragma once
#include "cBron.h"
class cSnajperka :
	public cBron
{
public:
	cSnajperka(sf::Vector2f xy);
	~cSnajperka();
	bool upgrade(int gold);
};

