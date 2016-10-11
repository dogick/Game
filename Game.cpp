#include "Game.h"
#include <iostream>

void InitializeGame(Game & game)
{
	game.level.LoadFromFile("platformer.tmx");
	game.view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	game.window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game");
	game.textureGame.LoadingFromFileTexture();
	game.player.playerSound.LoadingFromFileSound();
	InitializePlayer(game.player, game.textureGame);
	InitializePlayer(game.player, game.textureGame);
	ReplaceCursor(game.textureGame.cursorTexture, game.cursorSprite);
}

void ResizeWindowGame(sf::RenderWindow & window)
{
	float windowWidth = static_cast<float>(window.getSize().x);
	float windowHeight = static_cast<float>(window.getSize().y);
	window.setView(sf::View(sf::FloatRect(0, 0, windowWidth, windowHeight)));
}

void UpdateCursorPosition(sf::RenderWindow & window, sf::Sprite &cursorSprite)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
	cursorSprite.setPosition(static_cast<sf::Vector2f>(pos));
}

void ReplaceCursor(sf::Texture &cursorTexture, sf::Sprite &cursorSprite)
{
	cursorSprite.setTexture(cursorTexture);
	cursorSprite.setOrigin(cursorTexture.getSize().x / 2.f, cursorTexture.getSize().y / 2.f);
	cursorSprite.setPosition(100, 100);
}


void HandleEvents(sf::RenderWindow & window, Player &player)
{

	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Resized:
			std::cout << "RESIZE" << std::endl;
			ResizeWindowGame(window);
			break;
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			HandlePlayerKeyPress(event.key, player);
			break;
		case sf::Event::KeyReleased:
			HandlePlayerKeyRelease(event.key, player);
		default:
			break;
		}


		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left)
			{
				player.isShot = true;
				
			}
		}
		else  if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.key.code == sf::Mouse::Left)
			{
				player.isShot = false;
			}
		}

	}
}

void Update(Game &game, float elapsedTime)
{
	game.player.mousePosition = GetMousePosition(game.window);
	UpdatePlayer(game.player, elapsedTime);
	UpdateCursorPosition(game.window, game.cursorSprite);
}

void RenderBullets(Game &game)
{
	for (int i = 0; i < game.player.bullets.size(); ++i)
	{
		game.player.bulletSprite.setPosition(game.player.bullets[i]->position);
		game.player.bulletSprite.setRotation(game.player.bullets[i]->rotation);
		game.window.draw(game.player.bulletSprite);
	}
}

void Render(sf::RenderWindow & window, sf::Sprite & playerSprite, sf::Sprite &cursorSprite, Game &game)
{
	window.clear();
	window.setView(game.view);
	game.level.Draw(window);
	RenderBullets(game);
	window.draw(cursorSprite);
	window.draw(playerSprite);
	window.display();
}

void GetPlayerCoordinateForView(sf::View & view, sf::Vector2f playerPosition)
{
	float tempX = playerPosition.x;
	float tempY = playerPosition.y;

	if (tempX < 600) tempX = 600;
	if (tempY < 300) tempY = 300;


	view.setCenter(tempX, tempY);

}
