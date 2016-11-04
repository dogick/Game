#include "stdafx.h"
#include "Game.h"
#include <iostream>

void InitializeGame(Game & game)
{
    game.level.LoadFromFile("map/map.tmx");
	game.light = new Lights(sf::Vector2f(static_cast<float>(game.level.GetTileSize().x), static_cast<float>(game.level.GetTileSize().y)));
	game.view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	game.window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game");
	game.viewLight = game.window.getDefaultView();
	game.textureGame.LoadTextureFiles();
	game.player.playerSound.LoadSoundFiles();
	game.barrier = game.level.GetObjects("solid");
	InitializePlayer(game.player, game.textureGame);
	InitializePlayer(game.player, game.textureGame);
    game.bulletSprite.setTexture(game.textureGame.bulletTexture);
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
		if ((event.key.code == sf::Mouse::Left) && (event.type == sf::Event::MouseButtonPressed))
		{
			player.isShot = true;
				
		}
		else  if ((event.key.code == sf::Mouse::Left) && (event.type == sf::Event::MouseButtonReleased))
		{
			player.isShot = false;
		}
	}
}

void Update(Game &game, float elapsedTime)
{
	game.player.mousePosition = GetMousePosition(game.window);
	UpdatePlayer(game.player, elapsedTime, game.barrier);
	UpdateCursorPosition(game.window, game.cursorSprite);
}

void RenderBullets(Game &game)
{
	for (int i = 0; i < game.player.bullets.size(); ++i)
	{
		game.bulletSprite.setPosition(game.player.bullets[i]->position);
		game.bulletSprite.setRotation(game.player.bullets[i]->rotation);
		game.window.draw(game.bulletSprite);
	}
}

void RenderLight(Game & game, sf::RenderWindow & window)
{
	window.setView(game.viewLight);
	game.light->flashLight->_emissionSprite.setPosition(game.player.playerSprite.getPosition());
	game.light->flashLight->_emissionSprite.setRotation(game.player.playerSprite.getRotation());
	game.light->ls.render(game.view, game.light->unshadowShader, game.light->lightOverShapeShader);
	game.light->Lsprite.setTexture(game.light->ls.getLightingTexture()); 
	game.light->lightRenderStates.blendMode = sf::BlendMultiply; //фон
	window.draw(game.light->Lsprite, game.light->lightRenderStates);
}

void Render(sf::RenderWindow & window, sf::Sprite & playerSprite, sf::Sprite &cursorSprite, Game &game)
{
	window.clear();
	game.level.Draw(window);
	RenderBullets(game);
	window.draw(playerSprite);
	RenderLight(game, window);
	window.setView(game.view);
	window.draw(cursorSprite);

    /*sf::RectangleShape shape1;
    shape1.setSize(sf::Vector2f(40, 40));
    sf::IntRect textureRect = playerSprite.getTextureRect();
    shape1.setPosition(playerSprite.getPosition().x - 20, playerSprite.getPosition().y - 20);
    shape1.setFillColor(sf::Color(255,255,255, 60));
    window.draw(shape1);*/
	window.display();
}

void GetPlayerCoordinateForView(sf::View & view, sf::Vector2f playerPosition)
{
	float tempX = int(playerPosition.x);
	float tempY = int(playerPosition.y);

	if (tempX < 700) tempX = 700;
	if (tempY < 400) tempY = 400;


	view.setCenter(tempX, tempY);

}
