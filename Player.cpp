#include "Player.h"
#include "Config.h"

void InitializePlayer(Player & player, TextureGame & texture)
{
	player.playerSprite.setTexture(texture.playerTexture);
	player.bulletSprite.setTexture(texture.bulletTexture);
	InitializePlayerSound(player);
	player.playerSprite.setTextureRect(sf::IntRect(150, 121, 150, 121));
	player.playerSprite.setPosition(250, 250);
	player.direction = Direction::NONE;
	player.countFrame = 0;
	player.currentFrame = 0;
	player.isShot = false;
	player.weapon = Arms::SHOTGUN;
	player.shootingTime = 0;
}

void PlayerSound::LoadingFromFileSound()
{
	soundShotgunShotBuffer.loadFromFile("resources/sound/shotgun.ogg");
	soundM4A1ShotBuffer.loadFromFile("resources/sound/shoot.ogg");
}

void InitializePlayerSound(Player & player)
{
	player.playerSound.soundShotgunShot.setBuffer(player.playerSound.soundShotgunShotBuffer);
	player.playerSound.soundM4A1Shot.setBuffer(player.playerSound.soundM4A1ShotBuffer);
}


sf::Vector2f GetMousePosition(sf::RenderWindow &window)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	return window.mapPixelToCoords(pixelPos);
}

void UpdatePlayerRotation(Player &player) //Поворот игрока за курсором мыши
{
	float dx = player.mousePosition.x - player.playerSprite.getPosition().x;
	float dy = player.mousePosition.y - player.playerSprite.getPosition().y;
	sf::IntRect textureRect = player.playerSprite.getTextureRect();
	player.playerSprite.setOrigin(textureRect.width / 2.f, textureRect.height / 2.f);
	float rotation = (atan2(dy, dx)) * 180 / PI;
	player.playerSprite.setRotation(rotation);
}

void PlayerShootingM4A1(Player &player, sf::Vector2f &vectorNormal)
{
	if (player.isShot && (player.weapon == Arms::M4A1) && (player.shootingTime > 0.2))
	{
		player.playerSound.soundM4A1Shot.play();
		player.bullets.push_back(new Bullet(player.playerSprite.getPosition().x, player.playerSprite.getPosition().y, vectorNormal + sf::Vector2f(0, 0), player.playerSprite.getRotation(), static_cast<float>(Arms::M4A1)));
		player.shootingTime = 0;
	}
}

void PlayerShootingShotgun(Player &player, sf::Vector2f &vectorNormal)
{
	if (player.isShot && (player.weapon == Arms::SHOTGUN))
	{
		player.playerSound.soundShotgunShot.play();

		player.bullets.push_back(new Bullet(player.playerSprite.getPosition().x, player.playerSprite.getPosition().y, vectorNormal + sf::Vector2f(0.1f, 0.1f), player.playerSprite.getRotation(), static_cast<float>(Arms::SHOTGUN)));
		player.bullets.push_back(new Bullet(player.playerSprite.getPosition().x, player.playerSprite.getPosition().y, vectorNormal + sf::Vector2f(0, 0), player.playerSprite.getRotation(), static_cast<float>(Arms::SHOTGUN)));
		player.bullets.push_back(new Bullet(player.playerSprite.getPosition().x, player.playerSprite.getPosition().y, vectorNormal + sf::Vector2f(-0.1f, -0.1f), player.playerSprite.getRotation(), static_cast<float>(Arms::SHOTGUN)));
		player.shootingTime = 0;

	}
}

void UpdatePlayerFrame(Player &player, float const step, sf::Vector2i &textureRect, sf::Vector2f &vectorNormal)
{
	player.currentFrame += step;
	PlayerShootingM4A1(player, vectorNormal);
	if (player.currentFrame > player.countFrame)
	{
		PlayerShootingShotgun(player, vectorNormal);
		player.currentFrame -= player.countFrame;
	}
	player.playerSprite.setTextureRect(sf::IntRect(textureRect.x, textureRect.y * int(player.currentFrame), 150, 122));
}

void UpdateShotRunFrame(Player &player, sf::Vector2i &textureRect)
{
	if (player.isShot)
	{
		if (player.weapon == Arms::SHOTGUN)
		{
			textureRect = sf::Vector2i(450, 122);
			player.countFrame = CF_RUN_SHOT_SHOTGUN;
		}
		else
		{
			textureRect = sf::Vector2i(600, 122);
			player.countFrame = CF_RUN_SHOT_M4A1;
		}
	}
	else
	{
		player.countFrame = CF_RUN;
	}
}

void UpdateShotStandFrame(Player &player, sf::Vector2i &textureRect)
{
	if (player.isShot)
	{
		if (player.weapon == Arms::SHOTGUN)
		{
			textureRect = sf::Vector2i(300, 122);
		}
		else
		{
			textureRect = sf::Vector2i(750, 122);
			player.countFrame = CF_STAND_SHOT_M4A1;
		}
	}
	else
	{
		textureRect = sf::Vector2i(150, 122);
	}
}


void UpdatePlayer(Player &player, float elapsedTime)
{
	const float step = PLAYER_SPEED * elapsedTime;
	player.shootingTime += elapsedTime;
	UpdatePlayerRotation(player);
	UpdateBullet(player.bullets, elapsedTime);

	float dx = player.mousePosition.x - player.playerSprite.getPosition().x;
	float dy = player.mousePosition.y - player.playerSprite.getPosition().y;
	float distance = hypot(dx, dy);
	sf::Vector2f vectorNormal = sf::Vector2f(dx, dy)/ distance;

	sf::Vector2f speed(0, 0);
	sf::Vector2i textureRect(0, 122);
	if (distance < 25)
	{
		player.direction = Direction::NONE;
	}


	UpdateShotRunFrame(player, textureRect);
	switch (player.direction)
	{
	case Direction::UP:
		speed = sf::Vector2f(step * 5 * vectorNormal.x, step * 5 * vectorNormal.y);
	break;
	case Direction::DOWN:
		speed = sf::Vector2f(-step * 3 * vectorNormal.x, -step * 3 * vectorNormal.y);
	break;
	case Direction::LEFT:
		speed = sf::Vector2f(step * 3 * std::sin(PI * player.playerSprite.getRotation() / 180.f), -std::cos(PI * player.playerSprite.getRotation() / 180.f) *step * 3 );
	break;
	case Direction::RIGHT:
		speed = sf::Vector2f(-step * 3 * std::sin(PI * player.playerSprite.getRotation() / 180.f), std::cos(PI * player.playerSprite.getRotation() / 180.f) *step * 3);
	break;
	case Direction::NONE:
		player.countFrame = CF_STAND;
		UpdateShotStandFrame(player, textureRect);
	break;
	}
	UpdatePlayerFrame(player, step, textureRect, vectorNormal);
	player.playerSprite.move(speed);
}

void HandlePlayerKeyPress(const sf::Event::KeyEvent &event, Player &player)
{

	switch (event.code)
	{
	case sf::Keyboard::W:
		player.direction = Direction::UP;
		break;
	case sf::Keyboard::S:
		player.direction = Direction::DOWN;
		break;
	case sf::Keyboard::A:
		player.direction = Direction::LEFT;
		break;
	case sf::Keyboard::D:
		player.direction = Direction::RIGHT;
		break;
	case sf::Keyboard::Q:
		player.weapon = Arms::M4A1;
		break;
	case sf::Keyboard::E:
		player.weapon = Arms::SHOTGUN;
		break;
	default:
		player.direction = Direction::NONE;
		break;
	}
}

void HandlePlayerKeyRelease(const sf::Event::KeyEvent &event, Player &player)
{
	bool handled = true;
	switch (event.code)
	{
	case sf::Keyboard::W:
		if (player.direction == Direction::UP)
		{
			player.direction = Direction::NONE;
		}
		break;
	case sf::Keyboard::S:
		if (player.direction == Direction::DOWN)
		{
			player.direction = Direction::NONE;
		}
		break;
	case sf::Keyboard::A:
		if (player.direction == Direction::LEFT)
		{
			player.direction = Direction::NONE;
		}
		break;
	case sf::Keyboard::D:
		if (player.direction == Direction::RIGHT)
		{
			player.direction = Direction::NONE;
		}
		break;
	default:
		handled = false;
		break;
	}
}