#include "stdafx.h"
#include "Texture.h"

void TextureGame::LoadTextureFiles()
{
	playerTexture.loadFromFile("resources/images/player-m4a1+stand.png");
	cursorTexture.loadFromFile("resources/images/crosshair.png");
	weaponTexture.loadFromFile("resources/images/weapon.png");
	bulletTexture.loadFromFile("resources/images/bullet.gif");
}
