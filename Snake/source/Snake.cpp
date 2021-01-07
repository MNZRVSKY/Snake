#include "Snake.h"
#include "Field.h"
#include <cstdlib>

using namespace Sexy;

Snake::Snake()
{
	_currDirection = SnakeDirection::UP;
	_prewDirection = SnakeDirection::UP;
	_init = false;
	_snakeGrow = false;
}

// Check if we can move to current direction
// when not return false
// else we add part to snake 
// If this function call at first generate and add part 
bool Snake::canMove(Field &field)
{
	if (_init == false)
	{
		int x,y;
		do
		{
			x = rand() % field.getWidth();
			y = rand() % field.getHeight();
		} while (field.getBlock(x, y) != FieldSectionType::EMPTY);
		field.setBlock(FieldSectionType::SNAKE, x, y);
		_body.push_back(SnakePart(x, y));
		_init = true;
	}

	_prewDirection = _currDirection;
	SnakePart head = _body.front();
	

	switch (_currDirection)
	{ 
		case LEFT:	head.setPosX(head.getPosX()-1);	break;
		case UP:	head.setPosY(head.getPosY()-1); break;
		case RIGHT: head.setPosX(head.getPosX()+1); break;
		case DOWN:	head.setPosY(head.getPosY()+1); break;
	}
	
	if (head.isPartOutOfFieldSize(field.getWidth(), field.getHeight())) { return false; }
		
	
	if		(field.getBlock(head.getPosX(), head.getPosY()) == FieldSectionType::SNAKE)	{ return false; }
	else if (field.getBlock(head.getPosX(), head.getPosY()) == FieldSectionType::WALL)	{ return false; }
	else { _body.push_front(head); }

	
	if (field.isSnakePartAtPostion(head.getPosX(), head.getPosY()))
	{
		field.setBlock(FieldSectionType::SNAKE, head.getPosX(), head.getPosY());
		field.generateNewSnakePart();
		_snakeGrow = true;
	}
	else
	{
		field.setBlock(FieldSectionType::SNAKE, head.getPosX(), head.getPosY());
		SnakePart tail = _body.back();
		field.setBlock(FieldSectionType::EMPTY, tail.getPosX(), tail.getPosY());
		_body.pop_back();
	}

	return true;    
}

// Check if we change direction
// when we can - changing
void Snake::keyEvent(SnakeDirection direction)
{
	bool canChangeDirection = true;
	if (direction == _currDirection) { canChangeDirection = false; }
  
	switch (direction)
	{
		case LEFT:	if (_prewDirection == RIGHT)	canChangeDirection = false;	break;
		case UP:	if (_prewDirection == DOWN)		canChangeDirection = false;	break;
		case RIGHT: if (_prewDirection == LEFT)		canChangeDirection = false;	break;
		case DOWN:	if (_prewDirection == UP)		canChangeDirection = false;	break;
	}
	if (canChangeDirection == true) { _currDirection = direction; }
}

// Get is Snake grow, when grew return value and reset current value
bool Snake::isSnakeGrow()
{
	if (_snakeGrow)
	{
		_snakeGrow = false;
		return true;
	}
	return false;
}