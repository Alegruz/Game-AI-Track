#include "Game.h"

std::shared_ptr<sf::RenderWindow> Game::mWindow = nullptr;

// constructor / destructor
Game::Game()
// Creates a SFML window using options from a window.ini file
{
	Game::InitWindow();
	Game::InitStates();
}

Game::~Game()
{
}

// general functions
void Game::EndApplication()
{
	std::cerr << "Ending Application" << std::endl;
	mWindow->close();
}

// update functions
inline void Game::UpdateDt()
// Updates mDt with the time it took to update and render a single frame
{
	mDt = mDtClock.restart().asSeconds();

	std::cout << "FPS: " << 1 / mDt << std::endl;
}

void Game::Update()
{
	Game::UpdateSFMLEvents();

	if (!(mStates.empty()))
	{
		mStates.top()->Update(mDt);

		if (mStates.top()->GetQuit())
		{
			mStates.top()->EndState();
			mStates.pop();
		}
	}
	
	if (mStates.empty())
	{
		Game::EndApplication();
	}
}

void Game::UpdateSFMLEvents()
{
	while (mWindow->pollEvent(mSfEvent))
	{
		if (mSfEvent.type == sf::Event::Closed)
		{
			mWindow->close();
		}
	}
}

// render functions
void Game::Render()
{
	mWindow->clear();

	// Render
	if (!(mStates.empty()))
	{
		mStates.top()->Render(mWindow);
	}

	mWindow->display();
}

void Game::Run()
{
	while (mWindow->isOpen())
	{
		Game::UpdateDt();
		Game::Update();
		Game::Render();
	}
}

// initialization
void Game::InitWindow()
{
	sf::VideoMode windowBounds;
	std::string title;
	unsigned int framerateLimit;
	bool bVerticalSyncEnable;
	
	std::ifstream gameConfig("config/window.ini");
	if (gameConfig.is_open())
	{
		std::getline(gameConfig, title);
		gameConfig >> windowBounds.width >> windowBounds.height;
		gameConfig >> framerateLimit;
		gameConfig >> bVerticalSyncEnable;
	}

	gameConfig.close();

	mWindow = std::make_shared<sf::RenderWindow>(windowBounds, title);

	mWindow->setFramerateLimit(framerateLimit); 
	mWindow->setVerticalSyncEnabled(bVerticalSyncEnable);
}
void Game::InitWindow(const unsigned int width, const unsigned int height, const std::string& title)
{
	mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title);
}

void Game::InitWindow(const sf::VideoMode& windowBounds, const std::string& title)
{
	mWindow = std::make_shared<sf::RenderWindow>(windowBounds, title);
}

void Game::InitStates()
{
	mStates.push(std::make_unique<GameState>(mWindow));
}