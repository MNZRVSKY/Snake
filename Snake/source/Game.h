#ifndef __GAME_H__
#define __GAME_H__

#include "../engine/SexyAppFramework/SexyAppBase.h"

namespace Sexy
{
	class GameWindow;
	class ImageFont;
	class Image;

	class Game : public SexyAppBase
	{
	private:
		GameWindow*	_gameWindow;	

	public:
		ImageFont*	_textFont;
		ImageFont*	_numberFont;		

		//
		// Constructors
		//
		Game();
		virtual ~Game();

		//
		// Methods
		//
		virtual void	Init();
		virtual void	LoadingThreadProc();
		virtual void	LoadingThreadCompleted();
	};

}


#endif	// __GAME_H__