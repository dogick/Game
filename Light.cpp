#include "Light.h"
#include "Config.h"

Lights::Lights(sf::Vector2f const& tileSize)
{
	penumbraTexture.loadFromFile("data/penumbraTexture.png");
	penumbraTexture.setSmooth(true);

	ConeLightTexture.loadFromFile("data/spotLightTexture.png");
	ConeLightTexture.setSmooth(true);

	unshadowShader.loadFromFile("data/unshadowShader.vert", "data/unshadowShader.frag");
	lightOverShapeShader.loadFromFile("data/lightOverShapeShader.vert", "data/lightOverShapeShader.frag");

	ls.create(ltbl::rectFromBounds(-tileSize, tileSize), sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT), penumbraTexture, unshadowShader, lightOverShapeShader);


	light2 = std::make_shared<ltbl::LightPointEmission>();
	light2->_emissionSprite.setOrigin(sf::Vector2f(ConeLightTexture.getSize().x * 0.5f, ConeLightTexture.getSize().y * 0.5f));
	light2->_emissionSprite.setTexture(ConeLightTexture);//Текстура свечения как у фонаря.
	light2->_emissionSprite.setScale(sf::Vector2f(20, 10));
	light2->_emissionSprite.setColor(sf::Color(255, 255, 255));
	ls.addLight(light2);
}