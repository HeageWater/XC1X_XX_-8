#pragma once
#include "BaseTrout.h"

class PowerupTrout : BaseTrout
{
public:
	//
	void Initialize();

	//
	void Update();

	//
	void Draw();

	//
	Status GetStatus() { return status; };

private:

};