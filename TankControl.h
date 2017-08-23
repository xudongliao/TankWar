#pragma once
class TankControl
{
public:
	TankControl();
	~TankControl();

public:
	static Vector<Tank*> getTanks();
	static Tank* getPlayerTank() ;
};

