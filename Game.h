#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "level.h"
#include "Config.h"
#include "Light.h"
#include <ltbl/lighting/LightSystem.h>
struct Game
{
	Level level;
	sf::View view;
	sf::View viewLight;
	Lights *light;
	sf::RenderWindow window;
	Player player;
	TextureGame textureGame;

	sf::Sprite cursorSprite;
};

void InitializeGame(Game & game);
void ResizeWindowGame(sf::RenderWindow & window);
void ReplaceCursor(sf::Texture &cursorTexture, sf::Sprite &cursorSprite);
void UpdateCursorPosition(sf::RenderWindow & window, sf::Sprite &cursorSprite);
void HandleEvents(sf::RenderWindow & window, Player &player);
void Update(Game &game, float elapsedTime);
void Render(sf::RenderWindow & window, sf::Sprite & playerSprite, sf::Sprite &cursorSprite, Game &game);
void GetPlayerCoordinateForView(sf::View & view, sf::Vector2f playerPosition);