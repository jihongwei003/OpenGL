#pragma once

class Movable
{
public:
	Movable(){};

	virtual ~Movable() = 0{};

	virtual void Move() = 0;
};