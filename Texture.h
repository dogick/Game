#pragma once
#include <SFML/Graphics.hpp>

struct TextureGame
{
	sf::Texture playerTexture;
	sf::Texture cursorTexture;
	sf::Texture weaponTexture;
	sf::Texture bulletTexture;

	void LoadTextureFiles();
};