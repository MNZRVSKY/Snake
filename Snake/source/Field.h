#ifndef __FIELD_H__
#define __FIELD_H__

#include "../engine/SexyAppFramework/Graphics.h"
#include "../engine/SexyAppFramework/Rect.h"

#include <fstream>
#include <string>

#include "enums.h"
#include "SnakePart.h"


namespace Sexy
{
	class Graphics;

	class Field 
	{
	private:
		int		_width;
		int		_height;
		
		FieldSectionType**	_map;
		SnakePart			_snakePart;

	public:
		//
		// Constructors
		//
		Field(std::string FileName);
		~Field();
		
		//
		// Methods
		//	
		int		getWidth();
		int		getHeight();
		void	setBlock(FieldSectionType type, int x, int y);
		FieldSectionType getBlock(int x, int y) const;

		bool	isSnakePartAtPostion(int x, int y);
		bool	isFieldBorderInPosition(int x, int y);
	
		void	draw(Graphics* g) const;
		void	generateNewSnakePart();	
	};
}

#endif