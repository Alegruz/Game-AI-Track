#pragma once
#include "states/GameState.h"

class Game final
{
public:
	// constructor / destructor
	Game();
	virtual ~Game();

	// general functions
	void EndApplication();

	// update functions
	void Update();
	void UpdateDt();
	void UpdateSFMLEvents();

	// render functions
	void Render();
	void Run();

private:
	// variables
	static std::shared_ptr<sf::RenderWindow> mWindow;
	sf::Event mSfEvent;
	sf::Clock mDtClock;
	float mDt;
	std::stack<std::unique_ptr<State>> mStates;

	// initialization
	void InitWindow();
	void InitWindow(const unsigned int width, const unsigned int height, const std::string& title);
	void InitWindow(const sf::VideoMode& windowBounds, const std::string& title);
	void InitStates();
};