#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <list>
#include "Field.h"
#include "SnakePart.h"
#include "enums.h"

namespace Sexy
{
class Field;

	class Snake
	{
	private:
		bool	_init;
		bool	_snakeGrow;

		std::list<SnakePart>	_body;
		SnakeDirection			_currDirection;
		SnakeDirection			_prewDirection;

	public:
		//
		// Constructors
		//
		Snake();

		//
		// Methods
		//
		bool	canMove(Field &);
		void	keyEvent(SnakeDirection);
		bool	isSnakeGrow();
	};

}


#endif	// __SNAKE_H__