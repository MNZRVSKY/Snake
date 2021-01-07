#include "Game.h"
#include "GameWindow.h"
#include "../engine/SexyAppFramework/WidgetManager.h"
#include "../engine/SexyAppFramework/ImageFont.h"
#include "../engine/SexyAppFramework/DDImage.h"
#include "../engine/SexyAppFramework/SoundManager.h"

using namespace Sexy;

Game::Game()
{
	mProdName = "Snake";
	mTitle = StringToSexyStringFast(mProdName);

	mWidth = 800;
	mHeight = 600;

	_gameWindow = NULL;
	_textFont = NULL;
	_numberFont = NULL;
}

Game::~Game()
{
	mWidgetManager->RemoveWidget(_gameWindow);
	delete _gameWindow;
	delete _textFont;	
	mSoundManager->ReleaseSounds();
}

void Game::Init()
{
	SexyAppBase::Init();
}

// Load resurces
void Game::LoadingThreadProc()
{
	_textFont = new ImageFont(this, "../Snake/resource/fonts/ArmorPiercing22.txt");
	_textFont->mFontData->mInitialized;
}

//Initialize gameWindow after load resources
void Game::LoadingThreadCompleted()
{
	SexyAppBase::LoadingThreadCompleted();
	if (mLoadingFailed) { return; }

	_gameWindow = new GameWindow(this);
	_gameWindow->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(_gameWindow);
	mWidgetManager->SetFocus(_gameWindow);
}