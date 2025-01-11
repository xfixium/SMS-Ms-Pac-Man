// Increments given entity's timer to the given threshold, then resets it
// Returns true, if the timer hit the threshold
unsigned char EntityIncrementTimer(unsigned char index, unsigned short threshold) {
    EntityTimer[index]++;
    if (EntityTimer[index] >= threshold) {
        EntityTimer[index] = 0;
        return 1;
    }
    return 0;
}

// Sets the given entity's visibility in game viewport
void SetEntityVisibility(unsigned char index) {
	// If not playing a stage, in view
	if (GameState != GAME_STATE_STAGE) {
		EntityVisibility[index] = IN_VIEW;
	// If autoscrolling, in view
	} else if (Scroller == INDEX_AUTO_SCROLL) {
		EntityVisibility[index] = IN_VIEW;
	// If out of view at the top
	} else if (EntityY[index] + 8 < ScrollY) {
		EntityVisibility[index] = OUT_OF_VIEW_TOP;
	// If out of view at the bottom
	} else if (EntityY[index] > (ScrollY + 192)) {
		EntityVisibility[index] = OUT_OF_VIEW_BOTTOM;
	// In view
	} else {
		EntityVisibility[index] = IN_VIEW;
	}
}

// Sets entity move speed for the given entity
void SetEntityMoveSpeed(unsigned char index, unsigned char speed, unsigned char subSpeed) {
	EntitySpeed[index] = speed;
	EntitySubSpeed[index] = subSpeed;
}

// Gets entity move speed based on subspeed increments
unsigned char GetEntityMoveSpeed(unsigned char index) {
	// Get current speed
	unsigned char speed = EntitySpeed[index];
	unsigned short acc = EntityAccSubSpeed[index] + EntitySubSpeed[index];
	// If the accumulated speed overflows when sub speed is applied, increase speed
	if (acc > 255) {
		speed++;
	}
	// Increment accumulated speed
	EntityAccSubSpeed[index] = acc;
	// Return incremented speed
	return speed;
}

// Check if entity collision with player(s)
unsigned char CheckEntityCollision(unsigned char index) {
	// If team mode, check both players
	if (GameMode == GAME_MODE_TEAM_PLAY) {
		// Check collision with player 1
		if (EntityTile[index] == EntityTile[INDEX_PLAYER_01] || EntityTile[index] == EntityPrevTile[INDEX_PLAYER_01]) {
			return INDEX_PLAYER_01;
		// Check collision with player 2
		} else if (EntityTile[index] == EntityTile[INDEX_PLAYER_02] || EntityTile[index] == EntityPrevTile[INDEX_PLAYER_02]) {
			return INDEX_PLAYER_02;
		// No collision
		} else {
			return 0;
		}
	// If player 1 or 2 mode
	} else {
		// Check collision with current player
		if (EntityTile[index] == EntityTile[CurrentPlayer] || EntityTile[index] == EntityPrevTile[CurrentPlayer]) {
			return CurrentPlayer;
		// No collision
		} else {
			return 0;
		}
	}
}

// Gets the tile index based on the pixel coordinates given
unsigned short PositionToTile(unsigned short x, unsigned short y) {
	return ((y >> 3) << 5) + (x >> 3);
}

// Gets the tile index based on centered offsets
unsigned short PositionToTileOffset(unsigned char index) {
	switch (EntityDir[index]) {
		case DIRECTION_DOWN: return (((EntityY[index] - 4) >> 3) << 5) + (EntityX[index] >> 3);
		case DIRECTION_LEFT: return ((EntityY[index] >> 3) << 5) + ((EntityX[index] + 3) >> 3);
		case DIRECTION_UP: return (((EntityY[index] + 3) >> 3) << 5) + (EntityX[index] >> 3);
		default: return ((EntityY[index] >> 3) << 5) + ((EntityX[index] - 4) >> 3);
	}
}

// Sets given entity's position based on the given tile index
void SetEntityPositionByTileIndex(unsigned char index, unsigned short tileIndex) {
	unsigned short row = tileIndex >> 5;
	EntityX[index] = (tileIndex - (row << 5)) << 3;
	EntityY[index] = row << 3;
}

// Check if given entity can move in given direction
unsigned char EntityCanMove(unsigned short tile, unsigned char dir) {
	// Check if tile is solid
	switch (dir) {
		case DIRECTION_DOWN: return GetMapTileId(tile + 32) > TILE_SOLID ? 0 : 1;
		case DIRECTION_LEFT: return GetMapTileId(tile - 1) > TILE_SOLID ? 0 : 1;
		case DIRECTION_UP: return GetMapTileId(tile - 32) > TILE_SOLID ? 0 : 1;
		default: return GetMapTileId(tile + 1) > TILE_SOLID ? 0 : 1;
	}
}

// Moves the given entity by their movement speed
void MoveEntity(unsigned char index, unsigned char dir) {
	// Get frame move speed
	unsigned char speed = GetEntityMoveSpeed(index);
	// Increment given direction with speed amount
	switch (dir) {
		case DIRECTION_RIGHT: EntityX[index] += speed; break;
		case DIRECTION_DOWN: EntityY[index] += speed; break;
		case DIRECTION_LEFT: EntityX[index] -= speed; break;
		case DIRECTION_UP: EntityY[index] -= speed; break;
	}
}

// Rounds off position by 8, and then adjust to center of tile
// Called only after tile index changes
void EntitySnapTile(unsigned char index, unsigned char dir) {
	if (dir == DIRECTION_RIGHT || dir == DIRECTION_LEFT) {
		EntityY[index] = ((EntityY[index] >> 3) << 3) + 4;
		return;
	}
	EntityX[index] = ((EntityX[index] >> 3) << 3) + 4;
}

// Check for tunnel wrap
void CheckWrap(unsigned char index) {
	if (EntityX[index] < 8) {
		EntityX[index] = 240;
	} else if (EntityX[index] > 246) {
		EntityX[index] = 8;
	}
}

// Squared numbers pre calculated
const unsigned short NumbersSquared[] = { 
    0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 
    100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 
    400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 
    900, 961, 1024, 1089, 1156, 1225
};

// Gets the distance between two tiles
unsigned short GetDistance(unsigned short tile1, unsigned short tile2) {
    // Get source tile x and y
    unsigned char y1 = tile1 >> 5;
    unsigned char x1 = tile1 - (y1 << 5);
    // Get target tile x and y
    unsigned char y2 = tile2 >> 5;
    unsigned char x2 = tile2 - (y2 << 5);
    // Get number of tiles between source and target
    unsigned char x = x1 > x2 ? x1 - x2 : x2 - x1;
    unsigned char y = y1 > y2 ? y1 - y2 : y2 - y1;
    // Return distance
	return NumbersSquared[x] + NumbersSquared[y];
}