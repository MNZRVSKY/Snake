#include "SnakePart.h"

SnakePart::SnakePart()
{
	_posX = 0;
	_posY = 0;
}
SnakePart::SnakePart(int x, int y)
{
	_posX = x;
	_posY = y;
}
SnakePart::SnakePart(const SnakePart & obj)
{
	_posX = obj._posX;
	_posY = obj._posY;
}
SnakePart::~SnakePart() {}

void SnakePart::setPosX(int x)	{ _posX = x; }
void SnakePart::setPosY(int y)	{ _posY = y; }
int  SnakePart::getPosX()		{ return _posX; }
int  SnakePart::getPosY()		{ return _posY; }

// if positions part of snake highter or lower
// then size of fild return false
bool SnakePart::isPartOutOfFieldSize(int width, int height)
{
	if (_posX < 0 || _posX >= width) { return true; }
	if (_posY < 0 || _posY >= height) { return true; }
	return false;
}
bool SnakePart::operator == (const SnakePart & obj)
{
	if (_posX == obj._posX && _posY == obj._posY) { return true; }
	return false;
}
SnakePart SnakePart::operator = (const SnakePart & obj)
{
	_posX = obj._posX;
	_posY = obj._posY;
	return *this;
}