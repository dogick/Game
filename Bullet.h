#pragma once
#include <SFML/Graphics.hpp>

struct Bullet
{
	Bullet(float x, float y, sf::Vector2f &Direction, float Rotation, float Damage);
	sf::Vector2f position;
	sf::Vector2f direction;
	float rotation;
	float damage;
	float speed = 2500;
};

void UpdateBullet(std::vector<Bullet*> bullets, float elapsedTime);