#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(float x, float y, sf::Vector2f &Direction, float Rotation, float Damage)
{
	position = sf::Vector2f(x, y);
	direction = Direction;
	rotation = Rotation;
	damage = Damage;
}

void UpdateBullet(std::vector<Bullet*> bullets, float elapsedTime)
{
	for (int i = 0; i < bullets.size(); ++i)
	{
		float offsetX = bullets[i]->speed * elapsedTime * bullets[i]->direction.x;
		float offsetY = bullets[i]->speed * elapsedTime * bullets[i]->direction.y;
		bullets[i]->position += sf::Vector2f(offsetX, offsetY);
	}
}

