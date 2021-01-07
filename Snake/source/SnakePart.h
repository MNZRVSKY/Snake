#ifndef __SNAKEPART_H__
#define __SNAKEPART_H__

class SnakePart
{
private:
	int _posX;
	int _posY;

public:
	//
	// Constructors
	//
	SnakePart();
	SnakePart(int x, int y);
	SnakePart(const SnakePart & obj);
	~SnakePart();

	//
	// Methods
	//
	void	setPosX(int x);
	void	setPosY(int y);
	int		getPosX();
	int		getPosY();

	bool	isPartOutOfFieldSize(int width, int height);
	bool	operator==(const SnakePart & obj);
	SnakePart operator=(const SnakePart & obj);

};

#endif // __SNAKEPART_H__