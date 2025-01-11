// Clears sprites
void ClearSprites(void) {
	SMS_initSprites();
	UNSAFE_SMS_copySpritestoSAT();
}

// Clears VRAM
void ClearVRAM(void) {
    // Clear all tile data
    SMS_VRAMmemsetW(0, 0, TILE_MAP_0);
    // Clear sprite data
    ClearSprites();
}

// Clears the screen with the given tile id
void ClearScreen(unsigned short tileId) {
    SMS_VRAMmemsetW(XYtoADDR(0,0), tileId, 2048);
}

// Resets commonly used global variables for program flow
void ResetGlobalVariables(void) {
    ClearSprites();
    SMS_setBGScrollX(0);
    SMS_setBGScrollY(0);
    SMS_setLineCounter(0);
    SMS_disableLineInterrupt();
    SubState = 0;
	FrameCounter = 0;
	Timer = 0;
	Accumulator = 0;
    ScrollYAmount = 0;
    ScrollY = 0;
    ScrollLock = 0;
    Track = 0;
    PrevTrack = 0;
    Paused = 0;
    ActClackerFrame = 0;
    AutoScrollDir = DIRECTION_NONE;
}

// Resets player scores
void ResetScores(void) {
    // Clear player 1 score
	for (unsigned char i = 3; i < 9; i++) {
        Scores[i] = 259;
    }
    // Clear player 2 score
    for (unsigned char j = 23; j < 29; j++) {
        Scores[j] = 259;
    }
}

// Increments general use timer to the given threshold, then resets it
// Returns true, if the timer hit the threshold
unsigned char IncrementTimer(unsigned short threshold) {
    Timer++;
    if (Timer >= threshold) {
        Timer = 0;
        return 1;
    }
    return 0;
}

// Sets RNG based on frame counter and user input
void SetRng(unsigned char num) {
    Rng = (FrameCounter + num);
}

// Get random number, using power of two division
unsigned char GetRng(unsigned char powerOfTwo, unsigned char offset) {
    Rng += offset;
    return Rng >> powerOfTwo;
}

// Polls current input state
void PollInput(void) {
	KeysPressed = SMS_getKeysPressed();
    KeysHeld = SMS_getKeysHeld();
    if (KeysHeld != 0) {
        SetRng(KeysHeld << 3);
    }
}

// Gets row number when scrolled past 28 rows
unsigned char GetRow(unsigned char row) {
	return row >= 28 ? row - 28 : row;
}

// Gets tile id offset when scrolled past 28 rows
unsigned short GetRowOffset(unsigned char row) {
	return row >= 28 ? 1792 : 0;
}

// Gets a map tile id based on given index
unsigned short GetMapTileId(unsigned short index) {
    if (CurrentPlayer == INDEX_PLAYER_01) {
        return P1Map[index] & 511;
    }
    return P2Map[index] & 511;
}

// Set a map and vram tile at the given entity's tile index with the given value
void SetMapTile(unsigned char index, unsigned short value) {
    // Set tile
    if (CurrentPlayer == INDEX_PLAYER_01) {
	    P1Map[EntityTile[index]] = value;
        // Is the player in view, check needed for team play
        if (EntityVisibility[index] == IN_VIEW) {
            SMS_loadTileMapAreaatAddr(TILE_MAP_0 + ((EntityTile[index] << 1) - GetRowOffset(EntityY[index] >> 3)), &P1Map[EntityTile[index]], 1, 1);
        }
    } else {
        P2Map[EntityTile[index]] = value;
        SMS_loadTileMapAreaatAddr(TILE_MAP_0 + ((EntityTile[index] << 1) - GetRowOffset(EntityY[index] >> 3)), &P2Map[EntityTile[index]], 1, 1);
    }
}

// Updates view rows in the given direction and amount
void UpdateRow(unsigned char dir, unsigned char amount) {
    // If facing down
	if (dir == DIRECTION_DOWN) {
        // If beyond or at the position threshold
		if (ScrollY + amount >= 96) {
            ScrollY = 96;
            Scroller = INDEX_NONE;
            ScrollYAmount = 0;
            SMS_setBGScrollY(ScrollY);
        // Else, do scroll row update
		} else {
            // Set scroll amount, and the amount that entites will be affected by this scroll
            ScrollY += amount;
            ScrollYAmount = -amount;
			SMS_setBGScrollY(ScrollY);
            // Get row to update, 1 row after row 24
            unsigned char row = ((ScrollY + 200) >> 3);
            // Load map based on current player
            if (CurrentPlayer == INDEX_PLAYER_01) {
                UNSAFE_SMS_VRAMmemcpy64(TILE_MAP_0 + (GetRow(row) << 6), &P1Map[row << 5]);
            } else {
                UNSAFE_SMS_VRAMmemcpy64(TILE_MAP_0 + (GetRow(row) << 6), &P2Map[row << 5]);
            }
		}
	} else if (dir == DIRECTION_UP) {
        // If beyond or at the position threshold
        if (ScrollY - amount <= 0) {
            ScrollY = 0;
            Scroller = INDEX_NONE;
            ScrollYAmount = 0;
            SMS_setBGScrollY(ScrollY);
        } else {
            // Set scroll amount, and the amount that entites will be affected by this scroll
            ScrollY -= amount;
            ScrollYAmount = amount;
            SMS_setBGScrollY(ScrollY);
            // Get row to update
            unsigned char row = ScrollY >> 3;
            // Load map based on current player
            if (CurrentPlayer == INDEX_PLAYER_01) {
                UNSAFE_SMS_VRAMmemcpy64(TILE_MAP_0 + (row << 6), &P1Map[row << 5]);
            } else {
                UNSAFE_SMS_VRAMmemcpy64(TILE_MAP_0 + (row << 6), &P2Map[row << 5]);
            }
        }
    }
}

// Updates view rows in the given direction and amount, using VDP safe calls
void UpdateRowSafe(unsigned char dir, unsigned char amount) {
    // If facing down
	if (dir == DIRECTION_DOWN) {
        // Set scroll amount, and the amount that entites will be affected by this scroll
        ScrollY += amount;
        ScrollYAmount = -amount;
        SMS_setBGScrollY(ScrollY);
        // Get row to update, 1 row after row 24
        unsigned short row = ((ScrollY + 200) >> 3);
        // Load map based on current player
        if (CurrentPlayer == INDEX_PLAYER_01) {
            SMS_loadTileMapArea(0, GetRow(row), &P1Map[row << 5], 32, 1);
        } else {
            SMS_loadTileMapArea(0, GetRow(row), &P2Map[row << 5], 32, 1);
        }
	} else if (dir == DIRECTION_UP) {
        // Set scroll amount, and the amount that entites will be affected by this scroll
        ScrollY -= amount;
        ScrollYAmount = amount;
        SMS_setBGScrollY(ScrollY);
        // Get row to update, 1 row after row 24
        unsigned short row = ScrollY >> 3;
        // Load map based on current player
        if (CurrentPlayer == INDEX_PLAYER_01) {
            SMS_loadTileMapArea(0, row, &P1Map[row << 5], 32, 1);
        } else {
            SMS_loadTileMapArea(0, row, &P2Map[row << 5], 32, 1);
        }
    }
}

// Update act number sprite
void UpdateActNumber(unsigned char x, unsigned char y) {
    unsigned char number[] = { 0, 0, 164, METASPRITE_END };
    SMS_addMetaSprite(x, y, number);
}

// Updates clacker animation
void UpdateClacker(unsigned char x, unsigned char y) {
    // If initial setup
    if (ActClackerFrame == 0) {
        SMS_loadTileMapArea(x, y, ActTop_00, 4, 2);
        SMS_loadTileMapArea(x, y + 2, ActBottom, 4, 2);
        ActClackerFrame++;
        return;
    }
    // Draw frame
    switch (ActClackerFrame++) {
        case 1: SMS_loadTileMapArea(x, y, ActTop_01, 4, 2); break;
        case 2: SMS_loadTileMapArea(x, y, ActTop_02, 4, 2); break;
        default: SMS_loadTileMapArea(x, y, ActTop_00, 4, 2); break;
    }
}