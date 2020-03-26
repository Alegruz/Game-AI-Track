#include "State.h"

State::State(std::shared_ptr<sf::RenderWindow> window)
	: mWindow(window)
	, mbQuit(false)
{
}

State::~State()
{
	mWindow = nullptr;
}

const bool& State::GetQuit() const
{
	return mbQuit;
}

void State::CheckForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		mbQuit = true;
	}
}