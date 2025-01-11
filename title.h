// Option coordinates
signed char OptionIndex;
const unsigned char OptionY[] = { 36, 60, 84, 108 };

// Title tilemaps
const unsigned short title_pal[] = { 402, 395, 313, 279 };
const unsigned short title_with[] = { 295, 285, 293, 284 };
const unsigned short title_blinky[] = { 312, 313, 314, 315, 316, 317 };
const unsigned short title_pinky[] = { 318, 319, 320, 321, 322 };
const unsigned short title_inky[] = { 323, 324, 325, 326 };
const unsigned short title_sue[] = { 309, 310, 311 };
const unsigned short title_starring[] = { 292, 293, 280, 291, 291, 285, 288, 283 };
const unsigned short title_ms_pac_man[] = { 331, 332, 279, 333, 334, 335, 336, 331, 334, 337 };
const unsigned short title_one_player[] = { 358, 279, 378, 374, 367, 381, 311, 379, 279 };
const unsigned short title_two_player[] = { 359, 279, 378, 374, 367, 381, 311, 379, 279 };
const unsigned short title_team[] = { 380, 311, 367, 375, 279, 378, 374, 367, 381 };
const unsigned short title_lives[] = { 327, 328, 329, 330 };
const unsigned short title_empty[] = { 279, 279, 279, 279 };
const unsigned short title_clear[] = { 279, 279, 279, 279, 279, 279 };
const unsigned short title_ms_pac_man_clear[] = { 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279 };
const unsigned short title_yes[] = { 381, 311, 309 };
const unsigned short title_no[] = { 376, 377, 279 };
const unsigned short title_additional_ms_pac_man[] = {
	279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 327, 328, 279, 279, 279, 
	279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 367, 370, 370, 373, 380, 373, 
	377, 376, 367, 374, 279, 329, 330, 279, 367, 380, 279, 358, 357, 357, 357, 357, 
	279, 354, 355, 356
};
const unsigned short title_options[] = { 
	279, 375, 377, 370, 311, 279, 358, 279, 378, 374, 367, 381, 311, 379, 279, 279, 
	279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 
	279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 
	279, 279, 279, 279, 279, 279, 279, 309, 378, 311, 311, 370, 279, 368, 377, 377, 
	309, 380, 279, 376, 377, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 
	279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 
	279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 309, 380, 367, 
	371, 311, 279, 358, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 
	279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 
	279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 
	279, 279, 279, 378, 374, 367, 381, 311, 379, 309, 279, 327, 328, 327, 328, 327, 
	328, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 329, 330, 329, 
	330, 329, 330, 279, 279, 279
};

// Marquee tiles
unsigned char MarqueeFrame;
unsigned char MarqueeIndexes[] = { 0, 8, 16, 24, 32, 40 };
const unsigned short Marquee[] = { 
	216, 215, 214, 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 
	200, 232, 264, 296, 328, 360, 392, 424, 
	425, 426, 427, 428, 429, 430, 431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 
	441, 409, 377, 345, 313, 281, 249, 217
};

// If PAL version, set on screen
void SetPal(void) {
#ifndef TIME_NTSC
	SMS_loadTileMapArea(24, 22, title_pal, 4, 1);
#endif
}

// Loads title data
void SetTitle(void) {
	SMS_displayOff();
	ResetGlobalVariables();
	ResetPlayerVariables();
	SMS_setSpriteMode (SPRITEMODE_TALL);
	SMS_useFirstHalfTilesforSprites(1);
    SMS_mapROMBank(title_bg_pal_bin_bank);
    SMS_loadBGPalette(title_bg_pal_bin);
	SMS_mapROMBank(main_spr_pal_bin_bank);
	SMS_loadSpritePalette(main_spr_pal_bin);
	SMS_mapROMBank(sprite_tiles_bin_bank);
	SMS_loadTiles(sprite_tiles_bin, 8, sprite_tiles_bin_size);
	SMS_mapROMBank(stage_tiles_bin_bank);
	SMS_loadTiles(stage_tiles_bin, 256, 736);
	SMS_mapROMBank(title_tiles_bin_bank);
	SMS_loadTiles(title_tiles_bin, 279, title_tiles_bin_size);
	SMS_mapROMBank(title_map_bin_bank);
	SMS_loadTileMap(0, 0, title_map_bin, title_map_bin_size);
	SetPlayer(INDEX_PLAYER_01, ENTITY_PLAYER_01, DIRECTION_LEFT, ENTITY_STATE_SCENE, 256, 200);
	SetGhost(INDEX_BLINKY, DIRECTION_LEFT, ENTITY_STATE_SCENE, 256, 200);
	SetGhost(INDEX_PINKY, DIRECTION_LEFT, ENTITY_STATE_SCENE, 256, 200);
	SetGhost(INDEX_INKY, DIRECTION_LEFT, ENTITY_STATE_SCENE, 256, 200);
	SetGhost(INDEX_SUE, DIRECTION_LEFT, ENTITY_STATE_SCENE, 256, 200);
	SMS_mapROMBank(stage_01_map_bin_bank);
	SMS_loadTileMapArea(0, 0, stage_01_map_bin, 32, 2);
	UpdateHudTop();
	SetPal();
	PacBoost = 0;
	OptionIndex = 0;
	GameMode = GAME_MODE_ONE_PLAYER;
	PrevGameState = GameState;
	SMS_displayOn();
}

// Updates title marquee animation
void UpdateTitleMarquee(unsigned char index) {
	// If 3 frame animation has played through, increment marquee index to next tile
	if (MarqueeFrame == 0) {
		MarqueeIndexes[index] = MarqueeIndexes[index] + 1 >= 48 ? 0 : MarqueeIndexes[index] + 1;
	}
	// Get starting tile for animation, based on the position in the marquee
	unsigned char value = MarqueeIndexes[index];
	unsigned short tileBase = value < 16 ? 297 : value < 24 ? 300 : value < 40 ? 303 : 306;
	// Get coordinates from tile
	unsigned char y = Marquee[value] >> 5;
	unsigned char x = Marquee[value] - (y << 5);
	// Set tile
	SMS_setTileatXY(x, y, tileBase + MarqueeFrame);
}

// Update title entities
void UpdateTitleEntities(void) {
	UNSAFE_SMS_copySpritestoSAT();
	SMS_initSprites();
	UpdatePlayerTiles();
	UpdatePlayer(INDEX_PLAYER_01);
	// If on options screen, skip further processing
	if (SubState >= 11) {
		return;
	}
	// Update ghosts
	UpdateGhost(INDEX_BLINKY);
	UpdateGhost(INDEX_PINKY);
	UpdateGhost(INDEX_INKY);
	UpdateGhost(INDEX_SUE);
	// Update marquee animation
	UpdateTitleMarquee(0);
	UpdateTitleMarquee(1);
	UpdateTitleMarquee(2);
	UpdateTitleMarquee(3);
	UpdateTitleMarquee(4);
	UpdateTitleMarquee(5);
	// Increment frame of animation
	MarqueeFrame++;
	// Reset animation to first frame, if over 3 frames
	if (MarqueeFrame > 2) {
		MarqueeFrame = 0;
	}
}

// Move given character to destination
void MoveTitleCharacter(unsigned char index, unsigned char x, unsigned char y) {
	// Move character to the left, if it hasn't reached the horizontal threshold
	if (EntityX[index] != x) {
		EntityX[index]--;
	// Horizontal threshold met, move to vertical threshold
	} else if (EntityX[index] == x && EntityY[index] != y) {
		EntityDir[index] = DIRECTION_UP;
		EntityY[index]--;
	// Vertical threshold met, next sub state
	} else if (EntityY[index] == y) {
		SubState++;
	}
}

// Updates game mode display
void UpdateTitleGameMode(void) {
	// Set mode text based on game mode selected
	switch (GameMode) {
		case GAME_MODE_ONE_PLAYER: SMS_loadTileMapArea(14, 4, title_one_player, 9, 1); break;
		case GAME_MODE_TWO_PLAYER: SMS_loadTileMapArea(14, 4, title_two_player, 9, 1); break;
		case GAME_MODE_TEAM_PLAY: SMS_loadTileMapArea(14, 4, title_team, 9, 1); break;
	}
}

// Updates stage select display
void UpdateTitleStageSelect(void) {
	// Set graphics based on stage selected
	switch (Stage) {
		case 0: SMS_setTileatXY(15, 10, 358); SMS_setTileatXY(16, 10, 279); break;  // 1
		case 1: SMS_setTileatXY(15, 10, 359); SMS_setTileatXY(16, 10, 279); break;  // 2
		case 2: SMS_setTileatXY(15, 10, 360); SMS_setTileatXY(16, 10, 279); break;  // 3
		case 3: SMS_setTileatXY(15, 10, 361); SMS_setTileatXY(16, 10, 279); break;  // 4
		case 4: SMS_setTileatXY(15, 10, 362); SMS_setTileatXY(16, 10, 279); break;  // 5
		case 5: SMS_setTileatXY(15, 10, 363); SMS_setTileatXY(16, 10, 279); break;  // 6
		case 6: SMS_setTileatXY(15, 10, 364); SMS_setTileatXY(16, 10, 279); break;  // 7
		case 7: SMS_setTileatXY(15, 10, 365); SMS_setTileatXY(16, 10, 279); break;  // 8
		case 8: SMS_setTileatXY(15, 10, 366); SMS_setTileatXY(16, 10, 279); break;  // 9
		case 9: SMS_setTileatXY(15, 10, 358); SMS_setTileatXY(16, 10, 357); break;  // 10
		case 10: SMS_setTileatXY(15, 10, 358); SMS_setTileatXY(16, 10, 358); break; // 11
		case 11: SMS_setTileatXY(15, 10, 358); SMS_setTileatXY(16, 10, 359); break; // 12
		case 12: SMS_setTileatXY(15, 10, 358); SMS_setTileatXY(16, 10, 360); break; // 13
		case 13: SMS_setTileatXY(15, 10, 358); SMS_setTileatXY(16, 10, 361); break; // 14
		case 14: SMS_setTileatXY(15, 10, 358); SMS_setTileatXY(16, 10, 362); break; // 15
		case 15: SMS_setTileatXY(15, 10, 358); SMS_setTileatXY(16, 10, 363); break; // 16
		case 16: SMS_setTileatXY(15, 10, 358); SMS_setTileatXY(16, 10, 364); break; // 17
		case 17: SMS_setTileatXY(15, 10, 358); SMS_setTileatXY(16, 10, 365); break; // 18
		case 18: SMS_setTileatXY(15, 10, 358); SMS_setTileatXY(16, 10, 366); break; // 19
		case 19: SMS_setTileatXY(15, 10, 359); SMS_setTileatXY(16, 10, 357); break; // 20
		case 20: SMS_setTileatXY(15, 10, 359); SMS_setTileatXY(16, 10, 358); break; // 21
		case 21: SMS_setTileatXY(15, 10, 359); SMS_setTileatXY(16, 10, 359); break; // 22
		case 22: SMS_setTileatXY(15, 10, 359); SMS_setTileatXY(16, 10, 360); break; // 23
		case 23: SMS_setTileatXY(15, 10, 359); SMS_setTileatXY(16, 10, 361); break; // 24
		case 24: SMS_setTileatXY(15, 10, 359); SMS_setTileatXY(16, 10, 362); break; // 25
	}
}

// Updates ms pac man lives display
void UpdateTitleLives(void) {
	// Iterate through lives (Max is 5 lives)
	for (unsigned char i = 0; i < 5; i++) {
		// If indexer is less than set default lives, display a ms pac man character
		if (i < DefaultLives) {
			SMS_loadTileMapArea(17 + (i << 1), 13, title_lives, 2, 2);
		// If indexer is greater than set default lives, place as empty
		} else {
			SMS_loadTileMapArea(17 + (i << 1), 13, title_empty, 2, 2);
		}
	}
}

// Updates title
void UpdateTitle(void) {
	// Update entities
	UpdateTitleEntities();
	// If key pressed, go to options
	if (SubState < 11 && KeysPressed & PORT_A_KEY_1) {
		PlaySFX(SFX_CONFIRM, SFX_CHANNELS2AND3);
		SubState = 11;
	}
	switch (SubState) {
		// Wait a little, load Blinky
		case 0:
			if (IncrementTimer(TIME_60) == 1) {
				SMS_loadTileMapArea(11, 8, title_with, 4, 1);
				SMS_loadTileMapArea(14, 11, title_blinky, 6, 1);
				EntityY[INDEX_BLINKY] = 120;
				SubState++;
			}
		break;
		// Introduce Blinky
		case 1:
			MoveTitleCharacter(INDEX_BLINKY, 56, 52);
		break;
		// Load Pinky
		case 2:
			SMS_loadTileMapArea(11, 8, title_clear, 6, 1);
			SMS_loadTileMapArea(14, 11, title_clear, 6, 1);
			SMS_loadTileMapArea(14, 11, title_pinky, 5, 1);
			EntityY[INDEX_PINKY] = 120;
			SubState++;
		break;
		// Introduce Pinky
		case 3:
			MoveTitleCharacter(INDEX_PINKY, 56, 68);
		break;
		// Load Inky
		case 4:
			SMS_loadTileMapArea(14, 11, title_clear, 6, 1);
			SMS_loadTileMapArea(15, 11, title_inky, 4, 1);
			EntityY[INDEX_INKY] = 120;
			SubState++;
		break;
		// Introduce Inky
		case 5:
			MoveTitleCharacter(INDEX_INKY, 56, 84);
		break;
		// Load Sue
		case 6:
			SMS_loadTileMapArea(14, 11, title_clear, 6, 1);
			SMS_loadTileMapArea(15, 11, title_sue, 3, 1);
			EntityY[INDEX_SUE] = 120;
			SubState++;
		break;
		// Introduce Sue
		case 7:
			MoveTitleCharacter(INDEX_SUE, 56, 100);
		break;
		// Load Ms Pac Man
		case 8:
			SMS_loadTileMapArea(11, 8, title_starring, 8, 1);
			SMS_loadTileMapArea(11, 11, title_ms_pac_man, 10, 1);
			EntityY[INDEX_PLAYER_01] = 120;
			SubState++;
		break;
		// Introduce Ms Pac Man
		case 9:
			MoveTitleCharacter(INDEX_PLAYER_01, 136, 120);
		break;
		// Freeze Ms Pac Man frame
		case 10:
			EntityFrame[INDEX_PLAYER_01] = 0;
		break;
		// Load options screen
		case 11:
			SMS_loadTileMapArea(10, 3, title_ms_pac_man_clear, 12, 1);
			SMS_loadTileMapArea(8, 4, title_options, 18, 11);
			SMS_loadTileMapArea(3, 16, title_additional_ms_pac_man, 26, 2);
			EntityDir[INDEX_PLAYER_01] = DIRECTION_RIGHT;
			EntityX[INDEX_PLAYER_01] = 56;
			SubState++;
		break;
		// Set options
		case 12:
			// If up or down keys pressed, set pac cursor index
			if (KeysPressed & PORT_A_KEY_UP) {
				OptionIndex = OptionIndex - 1 < 0 ? 0 : OptionIndex - 1;
			} else if (KeysPressed & PORT_A_KEY_DOWN) {
				OptionIndex = OptionIndex + 1 > 3 ? 3 : OptionIndex + 1;
			// If pressing right
			} else if (KeysPressed & PORT_A_KEY_RIGHT) {
				// If game mode option
				if (OptionIndex == 0) {
					GameMode = GameMode + 1 > 2 ? 2 : GameMode + 1;
					UpdateTitleGameMode();
				// If pac boost option
				} else if (OptionIndex == 1) {
					PacBoost = 1;
					SMS_loadTileMapArea(21, 7, title_yes, 3, 1);
				// If stage select option
				} else if (OptionIndex == 2) {
					Stage = Stage + 1 > 24 ? 24 : Stage + 1;
					UpdateTitleStageSelect();
				// If extra lives option
				} else if (OptionIndex == 3) {
					DefaultLives = DefaultLives + 1 > 5 ? 5 : DefaultLives + 1;
					UpdateTitleLives();
				}
			// If pressing left
			} else if (KeysPressed & PORT_A_KEY_LEFT) {
				// If game mode option
				if (OptionIndex == 0) {
					GameMode = GameMode - 1 < 0 ? 0 : GameMode - 1;
					UpdateTitleGameMode();
				// If pac boost option
				} else if (OptionIndex == 1) {
					PacBoost = 0;
					SMS_loadTileMapArea(21, 7, title_no, 3, 1);
				// If stage select option
				} else if (OptionIndex == 2) {
					Stage = Stage - 1 < 0 ? 0 : Stage - 1;
					UpdateTitleStageSelect();
				// If extra lives option
				} else if (OptionIndex == 3) {
					DefaultLives = DefaultLives - 1 < 3 ? 3 : DefaultLives - 1;
					UpdateTitleLives();
				}
			// If start button pressed on valid option
			} else if (KeysPressed & PORT_A_KEY_1) {
				// Play confirmation sound, go to next state
				PlaySFX(SFX_CONFIRM, SFX_CHANNELS2AND3);
				SubState++;
				return;
			}
			// Set pac cursor position
			EntityY[INDEX_PLAYER_01] = OptionY[OptionIndex];
		break;
		// Wait for confirmation sound
		case 13:
			// Set game variables, move on to the actual game play
			if (PSGSFXGetStatus() != PSG_PLAYING) {
				GameState = GAME_STATE_STAGE;
				P1Stage = Stage;
				P2Stage = Stage;
				Stage = 0;
				P1Lives = DefaultLives;
				P2Lives = DefaultLives;
				ResetScores();
			}
		break;
	}
}