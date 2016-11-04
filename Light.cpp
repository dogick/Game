#include "stdafx.h"
#include "Light.h"
#include "Config.h"

Lights::Lights(sf::Vector2f const& tileSize)
{
	penumbraTexture.loadFromFile("light/penumbraTexture.png");
	penumbraTexture.setSmooth(true);
	ConeLightTexture.loadFromFile("light/spotLightTexture.png");
	ConeLightTexture.setSmooth(true);
	unshadowShader.loadFromFile("light/unshadowShader.vert", "light/unshadowShader.frag");
	lightOverShapeShader.loadFromFile("light/lightOverShapeShader.vert", "light/lightOverShapeShader.frag");
	ls.create(ltbl::rectFromBounds(-tileSize, tileSize), sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT), penumbraTexture, unshadowShader, lightOverShapeShader);
	flashLight = std::make_shared<ltbl::LightPointEmission>();
	flashLight->_emissionSprite.setOrigin(sf::Vector2f(ConeLightTexture.getSize().x * 0.5f, ConeLightTexture.getSize().y * 0.5f));
	flashLight->_emissionSprite.setTexture(ConeLightTexture);//Текстура свечения как у фонаря.
	flashLight->_emissionSprite.setScale(sf::Vector2f(20, 10));
	flashLight->_emissionSprite.setColor(sf::Color(255, 255, 255));
	ls.addLight(flashLight);
}