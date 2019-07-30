#pragma once
#include "cBron.h"
class cWyrzutnia :
	public cBron
{
public:
	cWyrzutnia(sf::Vector2f xy);
	~cWyrzutnia();
	bool upgrade(int gold);
};

