#include "Game.h"

using namespace Sexy;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	gHInstance = hInstance;

	Game* anApp = new Game();
	anApp->Init();

	anApp->Start();
	
	delete anApp;

	return 0;
}
