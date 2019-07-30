#pragma once
#include "cBron.h"
class cKarabin :
	public cBron
{
public:
	cKarabin(sf::Vector2f xy);
	~cKarabin();
	bool upgrade(int gold);
};

