#include "stdafx.h"
#include "Texture.h"

void TextureGame::LoadingFromFileTexture()
{
	playerTexture.loadFromFile("resources/images/player-m4a1+stand.png");
	cursorTexture.loadFromFile("resources/images/cursor_aim_min.png");
	weaponTexture.loadFromFile("resources/images/weapon.png");
	bulletTexture.loadFromFile("resources/images/bullet.gif");
}
