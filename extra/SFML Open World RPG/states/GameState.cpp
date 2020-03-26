#include "GameState.h"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window)
	: State(window)
{
}

GameState::~GameState()
{
}

void GameState::UpdateKeyBinds(const float& dt)
{
	GameState::CheckForQuit();
}

void GameState::EndState()
{
	std::cerr << "Ending GameState" << std::endl;
}

void GameState::Update(const float& dt)
{
	GameState::UpdateKeyBinds(dt);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		std::cout << "A";
	}
}

void GameState::Render(std::shared_ptr<sf::RenderTarget> target)
{
}