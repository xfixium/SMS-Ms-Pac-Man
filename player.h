// Player sprites
const unsigned char player_01_sprite[] = { 0, 0, 0, 8, 0, 2, METASPRITE_END };
const unsigned char player_02_sprite[] = { 0, 0, 4, 8, 0, 6, METASPRITE_END };

// Player 1 frames
const unsigned short player_01_right[] = { 0, 128, 256, 128 };
const unsigned short player_01_down[] = { 384, 512, 640, 512 };
const unsigned short player_01_left[] = { 768, 896, 1024, 896 };
const unsigned short player_01_up[] = { 1152, 1280, 1408, 1280 };
const unsigned short player_01_dying[] = { 512, 896, 1280, 128, 512, 896, 1280, 128, 512, 896, 1280 };
const unsigned short player_01_marker_down[] = { 4224 };
const unsigned short player_01_marker_up[] = { 4480 };

// Player 2 frames
const unsigned short player_02_right[] = { 1536, 1664, 1792, 1664 };
const unsigned short player_02_down[] = { 1920, 2048, 2176, 2048 };
const unsigned short player_02_left[] = { 2304, 2432, 2560, 2432 };
const unsigned short player_02_up[] = { 2688, 2816, 2944, 2816 };
const unsigned short player_02_dying[] = { 2048, 2432, 2816, 1664, 2048, 2432, 2816, 1664, 2048, 2432, 2816 };
const unsigned short player_02_marker_down[] = { 4352 };
const unsigned short player_02_marker_up[] = { 4608 };

// Pac Man frames
const unsigned short pac_man_right[] = { 3072, 3200, 3328, 3200 };
const unsigned short pac_man_left[] = { 3456, 3584, 3712, 3584 };
const unsigned short pac_man_up[] = { 3840, 3968, 4096, 3968 };

// Resets player 1 and 2 game variables
void ResetPlayerVariables(void) {
	CurrentPlayer = INDEX_PLAYER_01;
	DefaultLives = 3;
	P1Lives = 3;
	P2Lives = 3;
	P1Stage = 0;
	P2Stage = 0;
	P1Score = 0;
	P2Score = 0;
	Stage = 0;
	P1PelletCount = 0;
	P2PelletCount = 0;
	P1Start = 1;
	P2Start = 1;
	P1GhostModeTimer = 0;
	P1GhostModeTimer = 0;
	P1GhostMode = ENTITY_STATE_SCATTERING;
	P2GhostMode = ENTITY_STATE_SCATTERING;
}

// Set player
void SetPlayer(unsigned char index, unsigned char type, unsigned char dir, unsigned char state, unsigned short x, unsigned short y) {
    EntityX[index] = x;
	EntityY[index] = y;
	EntityType[index] = type;
    EntityState[index] = state;
	EntitySubState[index] = ENTITY_STATE_NONE;
	EntityDir[index] = dir;
	EntityTimer[index] = 0;
	EntityFrame[index] = 1;
	EntityFrameDuration[index] = -1;
}

// Streamed player 1 and 2 tiles
void UpdatePlayerTiles(void) {
    SMS_mapROMBank(player_tiles_bin_bank);
	// Alternate drawing frames
	if (FrameCounter & 1 == 1) {
		UNSAFE_SMS_VRAMmemcpy128(0, &player_tiles_bin[PlayerFrame[0]]);
	} else {
		// If in team mode, current player is player 2, or if needed for something other than game play
		if (GameMode == GAME_MODE_TEAM_PLAY || CurrentPlayer == INDEX_PLAYER_02 || GameState != GAME_STATE_STAGE) {
			UNSAFE_SMS_VRAMmemcpy128(128, &player_tiles_bin[PlayerFrame[1]]);
		}
	}
}

// Updates player sprites
void UpdatePlayerSprites(unsigned char index) {
	// If state is none, return
	if (EntityState[index] == ENTITY_STATE_NONE) {
		return;
	}
	// Set visibility
	SetEntityVisibility(index);
	// Set sprite coordinates based on actual position
	unsigned char x = EntityX[index] - 8;
	unsigned char y = EntityY[index] - ScrollY - 8;
	// If this player is not the one causing the scrolling, add scroll offset
	if (Scroller != INDEX_NONE && Scroller != index) {
		y += ScrollYAmount;
	}
	// If out of view, on a game stage, and not auto scrolling, set as marker
	if (EntityVisibility[index] == OUT_OF_VIEW_TOP) {
		y = 0;
	} else if (EntityVisibility[index] == OUT_OF_VIEW_BOTTOM) {
		y = 176;
	}
	// Update sprite based on player
	if (index == INDEX_PLAYER_01) {
		SMS_addMetaSprite(x, y, player_01_sprite);
	} else {
		SMS_addMetaSprite(x, y, player_02_sprite);
	}
}

// Updates player animation frame
void UpdatePlayerFrame(unsigned char index) {
	// If team play and a player chomped or got chomped, don't process the other player's animation
	if (GameMode == GAME_MODE_TEAM_PLAY && Paused == 2 && EntityState[index] < ENTITY_STATE_DYING) {
		return;
	}
    // If not ready to update frame, return
    if (--EntityFrameDuration[index] > -1) {
		return;
	}
	// Increment frame based on state, reset if over max frame count
	EntityFrame[index] = EntityFrame[index] + 1 >= (EntityState[index] == ENTITY_STATE_DYING ? 11 : 4) ? 0 : EntityFrame[index] + 1;
	// Set player frame graphics
	switch (EntityState[index]) {
		case ENTITY_STATE_DEAD:
			EntityFrame[index] = 2;
		case ENTITY_STATE_DYING:
			// Reset duration
			EntityFrameDuration[index] = TIME_06;
			// Set frame of animation
			if (EntityType[index] == ENTITY_PLAYER_01) {
				PlayerFrame[0] = player_01_dying[EntityFrame[index]];
			} else {
				PlayerFrame[1] = player_02_dying[EntityFrame[index]];
			}
		break;
		// If chomped or idle, set to middle frame
		case ENTITY_STATE_CHOMPED:
		case ENTITY_STATE_IDLE:
			EntityFrame[index] = 1;
		// Default graphics
		default:
			// Reset duration
			EntityFrameDuration[index] = EntityState[index] == ENTITY_STATE_SCENE ? TIME_02 : TIME_01;
			switch (EntityType[index]) {
				// Player 1
				case ENTITY_PLAYER_01:
					// If off screen, set as marker, and return
					if (EntityVisibility[index] == OUT_OF_VIEW_TOP) {
						PlayerFrame[0] = player_01_marker_up[0];
						return;
					} else if (EntityVisibility[index] == OUT_OF_VIEW_BOTTOM) {
						PlayerFrame[0] = player_01_marker_down[0];
						return;
					}
					// Set graphic based on direction
					switch (EntityDir[index]) {
						case DIRECTION_RIGHT: PlayerFrame[0] = player_01_right[EntityFrame[index]]; return;
						case DIRECTION_DOWN: PlayerFrame[0] = player_01_down[EntityFrame[index]]; return;
						case DIRECTION_LEFT: PlayerFrame[0] = player_01_left[EntityFrame[index]]; return;
						case DIRECTION_UP: PlayerFrame[0] = player_01_up[EntityFrame[index]]; return;
					}
				break;
				// Player 2
				case ENTITY_PLAYER_02:
					// If off screen, set as marker, and return
					if (EntityVisibility[index] == OUT_OF_VIEW_TOP) {
						PlayerFrame[1] = player_02_marker_up[0];
						return;
					} else if (EntityVisibility[index] == OUT_OF_VIEW_BOTTOM) {
						PlayerFrame[1] = player_02_marker_down[0];
						return;
					}
					// Set graphic based on direction
					switch (EntityDir[index]) {
						case DIRECTION_RIGHT: PlayerFrame[1] = player_02_right[EntityFrame[index]]; return;
						case DIRECTION_DOWN: PlayerFrame[1] = player_02_down[EntityFrame[index]]; return;
						case DIRECTION_LEFT: PlayerFrame[1] = player_02_left[EntityFrame[index]]; return;
						case DIRECTION_UP: PlayerFrame[1] = player_02_up[EntityFrame[index]]; return;
					}
				break;
				// Pac man (Scenes)
				default:
					// Set graphic based on direction (Pac Man never faces down)
					switch (EntityDir[index]) {
						case DIRECTION_RIGHT: PlayerFrame[1] = pac_man_right[EntityFrame[index]]; return;
						case DIRECTION_LEFT: PlayerFrame[1] = pac_man_left[EntityFrame[index]]; return;
						case DIRECTION_UP: PlayerFrame[1] = pac_man_up[EntityFrame[index]]; return;
					}
				break;
			}
		break;
	}
}

// Sets current player's next stage
void SetPlayerNextStage(void) {
    if (CurrentPlayer == INDEX_PLAYER_01) {
        P1Stage++;
        P1PelletCount = 0;
        P1GhostMode = ENTITY_STATE_SCATTERING;
        P1GhostModeTimer = 0;
    } else {
        P2Stage++;
        P2PelletCount = 0;
        P2GhostMode = ENTITY_STATE_SCATTERING;
        P2GhostModeTimer = 0;
    }
}

// Changes screen BG tile and map tile, sets pellet count and checks for stage clear
void PlayerEatPellet(unsigned char index) {
	// If pellet count reached 70 or 170 and it hasn't been rolled out yet, roll out the bonus
	if (EntityState[INDEX_BONUS] == ENTITY_STATE_NONE && (PelletCount == 70 || PelletCount == 170)) {
		BonusTypeIndex = PelletCount >= 170 ? 1 : 0;
		SetBonus(ENTITY_STATE_ENTERING);
	}
	// Set pellet tile empty in map and vram
	SetMapTile(index, TILE_EMPTY);
	// Increase player 2 pellet count, if in 2 player mode
	if (GameMode == GAME_MODE_TWO_PLAYER && CurrentPlayer == INDEX_PLAYER_02) {
		P2PelletCount++;
		PelletCount = P2PelletCount;
	// Increase player one pellet count
	} else {
		P1PelletCount++;
		PelletCount = P1PelletCount;
	}
	PlaySFX(SFX_PELLET, SFX_CHANNEL2);
	// Stage cleared
	if (PelletCount >= PelletCounts[Stage]) {
		// Stop everything
		PSGStop();
		PSGSFXStop();
		Paused = 1;
		EntityState[index] = ENTITY_STATE_IDLE;
		// Reset for flash timing
		Accumulator = 0;
		// Set to stage clear
		SubState = 6;
	}
}

// Checks for pellet tile for the given player
unsigned char PlayerCheckPellet(unsigned char index, unsigned short tile) {
	// If pellet tile
	if (tile == TILE_PELLET) {
		AddScore(index, POINTS_10);
		PlayerEatPellet(index);
		return 1;
	// If energizer tile
	} else if (tile == TILE_ENERGIZER) {
		EnergizerTimer = GhostFrightenedDurations[Stage];
		EnergizerTimerHalf = EnergizerTimer >> 1;
		GhostPointAcc = 0;
		AddScore(index, POINTS_50);
		// If the frightened duration is greater than zero, play energizer sound
		if (GhostFrightenedDurations[Stage] > 0) {
			PlayTrack(AUDIO_ENERGIZER, 1);
		}
		PlayerEatPellet(index);
		SetAllGhostStates(ENTITY_STATE_FRIGHTENED);
		return 1;
	}
	return 0;
}

// Return sign of a number if it's over, under, or equal to zero
signed char GetSign(signed char num) {
	// If over zero, positive number
	if (num > 0) {
		return 1;
	// If less than zero negative number
	} else if (num < 0) {
		return -1;
	}
	// Zero
	return 0;
}

// Set inner tile pixel position for given entity
void SetTilePixels(unsigned char index) {
	// Mod current pixel position to get tile pixel position
    EntityPixelX[index] = EntityX[index] & 7;
    EntityPixelY[index] = EntityY[index] & 7;
	// Reset horizontal pixel if under zero
    if (EntityPixelX[index] < 0) {
        EntityPixelX[index] += 8;
    }
	// Reset vertical pixel if under zero
    if (EntityPixelY[index] < 0) {
        EntityPixelY[index] += 8;
    }
    EntityDistX[index] = 4 - EntityPixelX[index];
    EntityDistY[index] = 4 - EntityPixelY[index];
}

// Moves the given player in the given direction
// Returns speed of movement
unsigned char MoveEntityPlayer(unsigned char index, unsigned char dir) {
	// Get tile pixel amounts
	SetTilePixels(index);
	// Check if we can move in the desired direction
	unsigned char canMove = EntityCanMove(EntityTile[index], EntityDir[index]);
	// Get speed
	unsigned char speed = GetEntityMoveSpeed(index);
	// Try and move entity, apply corner cutting
	if (dir == DIRECTION_RIGHT && (canMove == 1 || EntityDistX[index] > 0)) {
		EntityX[index] += speed;
		EntityY[index] += GetSign(EntityDistY[index]);
	} else if (dir == DIRECTION_DOWN && (canMove == 1 || EntityDistY[index] > 0)) {
		EntityY[index] += speed;
		EntityX[index] += GetSign(EntityDistX[index]);
	} else if (dir == DIRECTION_LEFT && (canMove == 1 || EntityDistX[index] < 0)) {
		EntityX[index] -= speed;
		EntityY[index] += GetSign(EntityDistY[index]);
	} else if (dir == DIRECTION_UP && (canMove == 1 || EntityDistY[index] < 0)) {
		EntityY[index] -= speed;
		EntityX[index] += GetSign(EntityDistX[index]);
	} else {
		return 0;
	}
	return speed;
}

// Moves player based on desired direction
void MovePlayer(unsigned char index, unsigned char dir) {
	// Unlock vertical scroll lock
	ScrollLock = 0;
	// If paused or if pellet consumed
	if (Paused > 0 || PlayerCheckPellet(index, GetMapTileId(EntityTile[index])) == 1) {
		// If scrolling, lock in vertical scroll amount, so that it does not get reset
		if (ScrollYAmount != 0) {
			ScrollLock = 1;
		}
		return;
	}
	// Check moving in the desired direction, if available, set player to desired direction
	// Else we're moving in current direction
	if (EntityCanMove(EntityTile[index], dir) == 1) {
		EntityDir[index] = dir;
	}
	// If we are not moving in set direction, set player to idle, return
	if (MoveEntityPlayer(index, EntityDir[index]) == 0) {
		EntityState[index] = ENTITY_STATE_IDLE;
		return;
	}
	// We are moving
	EntityState[index] = ENTITY_STATE_MOVING;
	// Check for tunnel wrap
	CheckWrap(index);
}

#ifdef TIME_NTSC
	// Sets player speed
	void SetPlayerSpeed(unsigned char index) {
		// If not in actual game play, return
		if (GameState != GAME_STATE_STAGE) {
			return;
		}
		// If pac boost enabled, set double speed and return
		if (PacBoost == 1) {
			EntitySpeed[index] = 2;
			EntitySubSpeed[index] = 0;
			return;
		// Normal speed
		} else {
			EntitySpeed[index] = 1;
		}
		// Set sub pixel speed
		// If player energized
		if (EnergizerTimer > 0) {
			// lvl 1: 32, lvls 2-4: 48, lvls 5-20: 64, lvls 21+: 32
			if (Stage == 0) {
				EntitySubSpeed[index] = 32;
			} else if (Stage < 4) {
				EntitySubSpeed[index] = 48;
			} else if (Stage < 20) {
				EntitySubSpeed[index] = 64;
			} else {
				EntitySubSpeed[index] = 32;
			}
		// Normal state
		} else {
			// lvl 1: 0, lvls 2-4: 32, lvls 5-20: 64, lvls 21+: 32
			if (Stage == 0) {
				EntitySubSpeed[index] = 32;
			} else if (Stage < 4) {
				EntitySubSpeed[index] = 32;
			} else if (Stage < 20) {
				EntitySubSpeed[index] = 64;
			} else {
				EntitySubSpeed[index] = 32;
			}
		}
	}
#else
	// Sets player speed
	void SetPlayerSpeed(unsigned char index) {
		// If not in actual game play, return
		if (GameState != GAME_STATE_STAGE) {
			return;
		}
		// If pac boost enabled, set double speed and return
		if (PacBoost == 1) {
			EntitySpeed[index] = 2;
			EntitySubSpeed[index] = 0;
			return;
		// Normal speed
		} else {
			EntitySpeed[index] = 1;
		}
		// Set sub pixel speed
		// If player energized
		if (EnergizerTimer > 0) {
			// lvl 1: 32, lvls 2-4: 48, lvls 5-20: 64, lvls 21+: 32
			if (Stage == 0) {
				EntitySubSpeed[index] = 32;
			} else if (Stage < 4) {
				EntitySubSpeed[index] = 48;
			} else if (Stage < 20) {
				EntitySubSpeed[index] = 64;
			} else {
				EntitySubSpeed[index] = 32;
			}
		// Normal state
		} else {
			// lvl 1: 0, lvls 2-4: 32, lvls 5-20: 64, lvls 21+: 32
			if (Stage == 0) {
				EntitySubSpeed[index] = 0;
			} else if (Stage < 4) {
				EntitySubSpeed[index] = 32;
			} else if (Stage < 20) {
				EntitySubSpeed[index] = 64;
			} else {
				EntitySubSpeed[index] = 32;
			}
		}
	}
#endif

// Updates player state
void UpdatePlayerState(unsigned char index) {
	// Set player previous and current tile index
	EntityPrevTile[index] = EntityTile[index];
	EntityTile[index] = PositionToTile(EntityX[index], EntityY[index]);
	// Set player speed
	SetPlayerSpeed(index);
	// Do process based on state
	switch (EntityState[index]) {
		case ENTITY_STATE_NONE:
		case ENTITY_STATE_SCENE:
			return;
		break;
		// Wait for a bit, hide all entities except for this entity, set player to dying
		case ENTITY_STATE_CHOMPED:
			SubState = 5;
			// Auto scroll down to get player into view
			if (AutoScrollDir == DIRECTION_DOWN && ScrollY < 96) {
				Scroller = INDEX_AUTO_SCROLL;
				UpdateRowSafe(DIRECTION_DOWN, 1);
			// Auto scroll up to get player into view
			} else if (AutoScrollDir == DIRECTION_UP && ScrollY > 0) {
				Scroller = INDEX_AUTO_SCROLL;
				UpdateRowSafe(DIRECTION_UP, 1);
			// Player in view
			} else {
				if (EntityIncrementTimer(index, TIME_60) == 1) {
					SetAllGhostStates(ENTITY_STATE_NONE);
					EntityState[INDEX_BONUS] = ENTITY_STATE_NONE;
					if (index == INDEX_PLAYER_01) {
						EntityState[INDEX_PLAYER_02] = ENTITY_STATE_NONE;
					} else {
						EntityState[INDEX_PLAYER_01] = ENTITY_STATE_NONE;
					}
					EntityState[index] = ENTITY_STATE_DYING;
					EntityFrameDuration[index] = -1;
					EntityFrame[index] = 255;
					PlayTrack(AUDIO_PLAYER_CHOMPED, 0);
				}
			}
		break;
		// Wait for animation to end, set player to dead
		case ENTITY_STATE_DYING:
			if (EntityFrame[index] == 10) {
				EntityState[index] = ENTITY_STATE_DEAD;
			}
		break;
		// Wait for a bit, then reset the stage
		case ENTITY_STATE_DEAD:
			if (EntityIncrementTimer(index, TIME_40) == 1) {
				FrameCounter = 0;
				SubState = 9;
			}
		break;
		// Everything else
		default:
			if (index == INDEX_PLAYER_01) {
				if (KeysHeld & PORT_A_KEY_RIGHT) {
					MovePlayer(index, DIRECTION_RIGHT);
				} else if (KeysHeld & PORT_A_KEY_DOWN) {
					MovePlayer(index, DIRECTION_DOWN);
				} else if (KeysHeld & PORT_A_KEY_LEFT) {
					MovePlayer(index, DIRECTION_LEFT);
				} else if (KeysHeld & PORT_A_KEY_UP) {
					MovePlayer(index, DIRECTION_UP);
				} else {
					MovePlayer(index, EntityDir[index]);
				}
			} else {
				if (KeysHeld & PORT_B_KEY_RIGHT) {
					MovePlayer(index, DIRECTION_RIGHT);
				} else if (KeysHeld & PORT_B_KEY_DOWN) {
					MovePlayer(index, DIRECTION_DOWN);
				} else if (KeysHeld & PORT_B_KEY_LEFT) {
					MovePlayer(index, DIRECTION_LEFT);
				} else if (KeysHeld & PORT_B_KEY_UP) {
					MovePlayer(index, DIRECTION_UP);
				} else {
					MovePlayer(index, EntityDir[index]);
				}
			}
		break;
	}
}

// Updates player
void UpdatePlayer(unsigned char index) {
	UpdatePlayerSprites(index);
	UpdatePlayerState(index);
	UpdatePlayerFrame(index);
}