#ifndef __ENUMS_H__
#define __ENUMS_H__

// Type of snake direction
enum SnakeDirection{
	LEFT, 
	UP, 
	RIGHT, 
	DOWN
};

//Type of ich type of field
enum FieldSectionType{
	EMPTY,
	SNAKE,
	WALL,
	SNAKEPART
};

// Current game status
enum GameStatus {
	NEWGAME,
	PLAY,
	PAUSE,
	GAMEWIN,
	GAMEOVER
};



#endif // __ENUMS_H__