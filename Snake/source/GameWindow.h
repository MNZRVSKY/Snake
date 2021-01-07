#ifndef __GAMEWINDOW_H__
#define __GAMEWINDOW_H__

#include "Field.h"
#include "Snake.h"

#include "../engine/SexyAppFramework/Widget.h"

namespace Sexy
{
	class Graphics;
	class Game;
	class WidgetManager;

	class GameWindow : public Widget
	{
	private:
		int _scores;
		int _lives;
		int _speed;
		int _partCount;
		int _level;
		std::string _message;
	
		Game*		_game;
		GameStatus	_status;
		Field*		_field;
		Snake*		_snake;

	public:
		//
		// Constructors
		//
		GameWindow(Game* obj);
		virtual ~GameWindow();

		//
		// Methods
		//
		void resetInfo();
		void initLevel(int score, int lives, int speed, int level, int partCount, GameStatus status);
		void drawInfo(Graphics* g);
		virtual void Draw(Graphics* g);
		virtual void Update();
		virtual void KeyDown(KeyCode theKey);				
	};


}

#endif // __GAMEWINDOW_H__