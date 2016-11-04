#pragma once
#include <ltbl/lighting/LightSystem.h>
#include <SFML/Graphics.hpp>

struct Lights
{
	Lights(sf::Vector2f const& tileSize);
	ltbl::LightSystem ls;
	sf::Shader unshadowShader;
	sf::Shader lightOverShapeShader;
	sf::Sprite Lsprite;
	sf::RenderStates lightRenderStates;
	std::shared_ptr<ltbl::LightPointEmission> flashLight;
	sf::Texture pointLightTexture;
	sf::Texture ConeLightTexture;
	sf::Texture  penumbraTexture;
};
