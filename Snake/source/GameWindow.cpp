#include "../engine/SexyAppFramework/Graphics.h"
#include "../engine/SexyAppFramework/Color.h"
#include "../engine/SexyAppFramework/ImageFont.h"
#include "../engine/SexyAppFramework/DDImage.h"
#include "../engine/SexyAppFramework/Rect.h"
#include "../engine/SexyAppFramework/WidgetManager.h"

#include "GameWindow.h"
#include "Game.h"
#include "settings.h"

#include <string>
#include <sstream>

using namespace Sexy;
GameWindow::GameWindow(Game* obj)
{
	_game = obj;

	_snake = new Snake();
	_field = new Field("../Snake/resource/level/level1.txt");

	_scores = 0;
	_lives = 3; 
	_speed = LEVEL1_SPEED;
	_level = 1;
	_partCount = 0;
	_status = GameStatus::NEWGAME;
	_message = "New Game";
}
GameWindow::~GameWindow()
{
	delete _snake;
	delete _field;
}

// Init user info depent level and scores  
void GameWindow::initLevel(int score, int lives, int speed, int level, int partCount, GameStatus status)
{
	delete _snake;
	delete _field;

	std::stringstream  path;
	path << "../Snake/resource/level/level" << level << ".txt";

	_snake = new Snake();
	_field = new Field(std::string(path.str()));
	_scores = score;
	_lives = lives;
	_speed = speed;
	_level = level;
	_partCount = partCount;
	_status = status;
}
// Reset user info after over game or win
void GameWindow::resetInfo() {
	_scores = 0;
	_lives = SNAKE_LIVES;
	_speed = LEVEL1_SPEED;
	_level = 1;
	_partCount = 0;
}
void GameWindow::Update()
{		
	Widget::Update();	
	
	if (_status == GameStatus::PLAY) 
	{
		if (mUpdateCnt % _speed == 0)
		{
			if (_snake->canMove(*_field) == false)
			{
				initLevel(_scores, _lives, _speed, _level, _partCount, _status);
				_lives--;
				if (_lives == 0) 
				{ 
					resetInfo();
					_status = GameStatus::NEWGAME; 
					_message = "Game Over"; 
				}
			}
			else
			{
				if (_snake->isSnakeGrow())
				{
					_scores += SNAKE_PART_VALUE;
					_partCount++;
				}

				if (_scores <= LEVEL1_SCORE)
				{
					if (_level != 1) { initLevel(_scores, _lives, LEVEL1_SPEED, 1, 0, _status); }
					_speed = LEVEL1_SPEED;
					_level = 1;
				}
				else if (_scores <= LEVEL2_SCORE)
				{
					if (_level != 2) { initLevel(_scores, _lives, LEVEL2_SPEED, ++_level, 0, _status); }
					_speed = LEVEL2_SPEED;
					_level = 2;
				}
				else if (_scores <= LEVEL3_SCORE)
				{
					if (_level != 3) { initLevel(_scores, _lives, LEVEL3_SPEED, ++_level, 0, _status); }
					_speed = LEVEL3_SPEED;
					_level = 3; 
				}
				else
				{
					_speed = LEVEL1_SPEED;
					_level = 1;
					_message = "You Win!";
					_status = GameStatus::NEWGAME;
				}
			}
		}
	}

	MarkDirty();
}

//Drow window depend of game status
void GameWindow::Draw(Graphics* g)
{
	g->SetColor(Color(157, 151, 131));
	g->FillRect(0, 0, mWidth, mHeight);

	g->SetColor(Color(236, 187, 90));
	g->SetFont(_game->_textFont);

	if (_status == GameStatus::PLAY)
	{
		drawInfo(g);
		_field->draw(g);
	}
	else
	{
		WriteString(g, _S(_message), 0, mHeight / 2, mWidth, 0);
		WriteString(g, _S("Press any key to start"), 0, 550, mWidth, 0);
	}
	
}

// Check snake direction
// Change game status
void GameWindow::KeyDown(KeyCode theKey) {

	if (_status != GameStatus::PAUSE) {
		switch(theKey)
		{
			case KEYCODE_RIGHT:		_snake->keyEvent(SnakeDirection::RIGHT);	break;
			case KEYCODE_LEFT:		_snake->keyEvent(SnakeDirection::LEFT);		break;
			case KEYCODE_UP:		_snake->keyEvent(SnakeDirection::UP);		break;
			case KEYCODE_DOWN:		_snake->keyEvent(SnakeDirection::DOWN);		break;											
		}
	}	
	
	if ( theKey == KEYCODE_ESCAPE || _status == GameStatus::PAUSE)
	{
		if (_status == GameStatus::PAUSE)		{ _status = GameStatus::PLAY;	_message = "New Game"; }
		else if (_status = GameStatus::PLAY)	{ _status = GameStatus::PAUSE;	_message = "Pause"; }
	}
	
	switch (_status)
	{
		case GameStatus::GAMEOVER:	_status = GameStatus::NEWGAME;	_message = "Game Over"; break;
		case GameStatus::NEWGAME:	_status = GameStatus::PLAY;		_message = "New Game";
									resetInfo();
									initLevel(0, SNAKE_LIVES, LEVEL1_SPEED, 1, 0, _status); break;
	}
}

// Drow info sach as: level, amount of colected part of snake etc.
// And how we can control current game
void GameWindow::drawInfo(Graphics* g)
{
	g->DrawString(StrFormat("game info"), 655, 45);
	g->DrawString(StrFormat(_S("score:  %d"), _scores), 650, 75);
	g->DrawString(StrFormat(_S("lives:  %d"), _lives), 650, 105);
	g->DrawString(StrFormat(_S("parts:  %d"), _partCount), 650, 135);
	g->DrawString(StrFormat(_S("level:  %d"), _level), 650, 165);

	g->DrawString(StrFormat("control"), 650, 440);
	g->DrawString(StrFormat("up     - to up"), 630, 470);
	g->DrawString(StrFormat("right - to right"), 630, 500);
	g->DrawString(StrFormat("down - to down"), 630, 530);
	g->DrawString(StrFormat("left  - to left"), 630, 560);
	g->DrawString(StrFormat("esc    - pause"), 630, 590);
}