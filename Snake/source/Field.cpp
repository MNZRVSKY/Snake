#include "Field.h"
#include "Game.h"
#include "settings.h"
#include <cstdlib>
#include <fstream>
#include <string>

using namespace Sexy;

Field::Field(std::string FileName)
{	
	std::fstream fileMap(FileName);
	_height = -1;
	std::string buffer;

	// Count map width & height
	while (getline(fileMap, buffer))
	{
		if ((int)buffer.length() >= _width){ _width = (int)buffer.length(); }
		_height++;
	}
	fileMap.close();

	//Fill map by default
	_map = new FieldSectionType*[_height];
	for (int y = 0; y < _height; ++y)
	{
		_map[y] = new FieldSectionType[_width];
		for (int x = 0; x < _width; ++x)
		{
			if (isFieldBorderInPosition(x, y)) { this->_map[y][x] = FieldSectionType::WALL; }
			else { this->_map[y][x] = FieldSectionType::EMPTY; }
		}
	}

	//Fill map from file
	std::fstream fContent(FileName);
	for (int y = 0; y < _height; y++)
	{
		getline(fContent, buffer);
		for (int x = 0; x < (int)buffer.length(); x++)
		{
			if (buffer[x] == '1') { this->_map[y][x] = FieldSectionType::WALL; }
		}
	}

	generateNewSnakePart();
}
Field::~Field()
{
	int i;
	for (i = 0; i < _height; i++) 
		delete []_map[i];	
	delete []_map;
}

// Set block of field at current position
void Field::setBlock(FieldSectionType type, int x, int y)
{
  this->_map[y][x] = type;
}

// Get block of field at current position
FieldSectionType Field::getBlock(int x, int y) const
{
	return this->_map[y][x];
}

// Check is current block equal snake
bool Field::isSnakePartAtPostion(int x, int y)
{
	if (this->_map[y][x] == FieldSectionType::SNAKEPART) { return true; }
	return false;
}

// Chack is current block border of field
bool Field::isFieldBorderInPosition(int x, int y) 
{
	if (x == 0 || x == _width - 1 || y == 0 || y == _height - 1) { return true; }
	return false;
}

// Draw field
void Field::draw(Graphics* g) const
{		
	for (int y = 0; y < _height; ++y)
		for (int x = 0; x < _width; ++x)
			switch (_map[y][x])
			{	
				case FieldSectionType::SNAKE:
					g->SetColor(Color(68, 220, 115));
					g->FillRect(BLOCK_SIZE + x * BLOCK_SIZE, BLOCK_SIZE + y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
					break;
				case FieldSectionType::SNAKEPART:
					g->SetColor(Color(68, 220, 115));
					g->FillRect(BLOCK_SIZE + x * BLOCK_SIZE, BLOCK_SIZE + y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
					break;      
				case FieldSectionType::WALL:
					g->SetColor(Color(226, 177, 80));
					g->FillRect(BLOCK_SIZE + x * BLOCK_SIZE, BLOCK_SIZE + y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
					break;
				case FieldSectionType::EMPTY:
					g->SetColor(Color(157, 151, 131));
					g->FillRect(BLOCK_SIZE + x * BLOCK_SIZE, BLOCK_SIZE + y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
					break;
			}	       
}

// When we get snake part 
//we call this function for generate new part
void Field::generateNewSnakePart()
{
	int x = 0;
	int y = 0;
	do
	{
	    x = rand() % _width;
		y = rand() % _height;
	} while (getBlock(x, y) != EMPTY);

	setBlock(FieldSectionType::SNAKEPART, x, y);	
}

// Get size of field 
int Field::getWidth() { return _width; }
int Field::getHeight() { return _height; }