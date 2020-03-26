#pragma once

#include "State.h"

class GameState : public State
{
public:
	// constructors / destructor
	GameState(std::shared_ptr<sf::RenderWindow> window);
	virtual ~GameState();

	// functions
	virtual void UpdateKeyBinds(const float& dt) override;

	virtual void EndState() override;
	virtual void Update(const float& dt) override;
	virtual void Render(std::shared_ptr<sf::RenderTarget> target = nullptr) override;
private:
};