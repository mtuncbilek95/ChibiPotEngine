#pragma once

#include <Core/CoreMinimal.h>

struct Drawable2D {

	Drawable2D(int width, int height) {
		tileSize = atlasWidth = atlasHeight = 0;
	}

	int tileCount;
	XMINT2 atlasSize;
	XMINT2 Position;
};