#pragma once

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <vector>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

class State
{
public:
	// constructors / destructor
	State(std::shared_ptr<sf::RenderWindow> window);
	virtual ~State();

	// functions
	const bool& GetQuit() const;
	virtual void CheckForQuit();

	virtual void EndState() = 0;
	virtual void UpdateKeyBinds(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Render(std::shared_ptr<sf::RenderTarget> target = nullptr) = 0;
private:
	// variables
	std::vector<std::unique_ptr<sf::Texture>> mTextures;
	std::shared_ptr<sf::RenderWindow> mWindow;
	bool mbQuit;
};