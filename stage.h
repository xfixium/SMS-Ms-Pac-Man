// Stage tilemaps
const unsigned short stage_1up[] = { 260, 269, 270 };
const unsigned short stage_2up[] = { 261, 269, 270 };
const unsigned short stage_1up_flash[] = { 303, 305, 306 };
const unsigned short stage_2up_flash[] = { 304, 305, 306 };
const unsigned short stage_player_one[] = { 285, 286, 287, 288, 289, 290, 256, 291, 292, 289 };
const unsigned short stage_player_two[] = { 285, 286, 287, 288, 289, 290, 256, 293, 294, 291 };
const unsigned short stage_player_team[] = { 293, 289, 287, 295, 256, 256, 285, 286, 287, 288 };
const unsigned short stage_game_over[] = { 296, 297, 298, 299, 256, 256, 300, 301, 299, 302 };
const unsigned short stage_ready[] = { 279, 280, 281, 282, 283, 284 };
const unsigned short stage_empty[] = { 256, 256, 256, 256, 256, 256, 256, 256, 256, 256 };

// Clears Player One / Two text
void ClearPlayerText(void) {
	SMS_loadTileMapArea(11, 14, stage_empty, 10, 1);
}

// Clears Ready! text
void ClearReadyText(void) {
	SMS_loadTileMapArea(13, 20, stage_empty, 6, 1);
}

// Sets Ready! text
void SetReadyText(void) {
	SMS_loadTileMapArea(13, 20, stage_ready, 6, 1);
}

// Sets game over text
void SetGameOverText(void) {
	SMS_loadTileMapArea(11, 20, stage_game_over, 10, 1);
}

// Sets Player One / Two text
void SetPlayerStart(void) {
	// If team mode and first stage played
	if (GameMode == GAME_MODE_TEAM_PLAY && P1Start == 1) {
		SMS_loadTileMapArea(11, 14, stage_player_team, 10, 1);
		PlayTrack(AUDIO_READY, 0);
	// If player 1 is current player and first stage played
	} else if (CurrentPlayer == INDEX_PLAYER_01 && P1Start == 1) {
		SMS_loadTileMapArea(11, 14, stage_player_one, 10, 1);
		PlayTrack(AUDIO_READY, 0);
	// If player 2 is current player and first stage played
	} else if (CurrentPlayer == INDEX_PLAYER_02 && P2Start == 1) {
		SMS_loadTileMapArea(11, 14, stage_player_two, 10, 1);
		PlayTrack(AUDIO_READY, 0);
	}
	// Wait for vertical blank
	SMS_waitForVBlank();
}

// Sets flashing 1UP 2UP text in current player in memory map
void SetPlayerFlashingText(void) {
	// If team mode, flash both player texts
	if (GameMode == GAME_MODE_TEAM_PLAY) {
		memcpy(&P1Map[5], stage_1up_flash, sizeof(stage_1up_flash));
		memcpy(&P1Map[24], stage_2up_flash, sizeof(stage_2up_flash));
	// If player 1 is current player, flash 1UP
	} else if (CurrentPlayer == INDEX_PLAYER_01) {
		memcpy(&P1Map[5], stage_1up_flash, sizeof(stage_1up_flash));
		memcpy(&P2Map[24], stage_2up, sizeof(stage_2up));
	// If player 2 is current player, flash 2UP
	} else {
		memcpy(&P1Map[5], stage_1up, sizeof(stage_1up));
		memcpy(&P2Map[24], stage_2up_flash, sizeof(stage_2up_flash));
	}
	// Wait for vertical blank
	SMS_waitForVBlank();
}

// Sets player stage data
void SetPlayerStage(unsigned char refresh) {
	// Check if current player stage should loop back
	if (CurrentPlayer == INDEX_PLAYER_01) {
		if (P1Stage >= 25) {
			P1Stage = 13;
		}
		Stage = P1Stage;
	} else {
		if (P2Stage >= 25) {
			P2Stage = 13;
		}
		Stage = P2Stage;
	}
	// Set stage map
	StageMap = StageMaps[Stage];
	// If loading fresh stage data
	if (refresh == 1) {
		// Stage data variables
		unsigned char stageBank = 0;
		const unsigned char* stageBin = 0;
		// Set stage data based on current stage map
		switch (StageMap) {
			case 0: stageBank = stage_01_map_bin_bank; stageBin = stage_01_map_bin; break;
			case 1: stageBank = stage_02_map_bin_bank; stageBin = stage_02_map_bin; break;
			case 2: stageBank = stage_03_map_bin_bank; stageBin = stage_03_map_bin; break;
			case 3: stageBank = stage_04_map_bin_bank; stageBin = stage_04_map_bin; break;
			case 4: stageBank = stage_03_map_bin_bank; stageBin = stage_03_map_bin; break;
			case 5: stageBank = stage_04_map_bin_bank; stageBin = stage_04_map_bin; break;
			case 6: stageBank = stage_07_map_bin_bank; stageBin = stage_07_map_bin; break;
		}
		// Load stage map data
		SMS_mapROMBank(stageBank);
		if (CurrentPlayer == INDEX_PLAYER_01) {
			memcpy(P1Map, stageBin, 2304);
			SMS_loadTileMap(0, 0, P1Map, 1600);
		} else {
			memcpy(P2Map, stageBin, 2304);
			SMS_loadTileMap(0, 0, P2Map, 1600);
		}
	} else {
		// Load in existing map data
		if (CurrentPlayer == INDEX_PLAYER_01) {
			SMS_loadTileMap(0, 0, P1Map, 1600);
		} else {
			SMS_loadTileMap(0, 0, P2Map, 1600);
		}
	}
	// Wait for vertical blank
	SMS_waitForVBlank();
}

// Sets player palette data
void SetPlayerPalette(void) {
	// Set palette data based on current stage map
	switch (StageMap) {
		case 0: StagePaletteBank = stage_01_bg_pal_bin_bank; StagePaletteBin = stage_01_bg_pal_bin; break;
		case 1: StagePaletteBank = stage_02_bg_pal_bin_bank; StagePaletteBin = stage_02_bg_pal_bin; break;
		case 2: StagePaletteBank = stage_03_bg_pal_bin_bank; StagePaletteBin = stage_03_bg_pal_bin; break;
		case 3: StagePaletteBank = stage_04_bg_pal_bin_bank; StagePaletteBin = stage_04_bg_pal_bin; break;
		case 4: StagePaletteBank = stage_05_bg_pal_bin_bank; StagePaletteBin = stage_05_bg_pal_bin; break;
		case 5: StagePaletteBank = stage_06_bg_pal_bin_bank; StagePaletteBin = stage_06_bg_pal_bin; break;
		case 6: StagePaletteBank = stage_07_bg_pal_bin_bank; StagePaletteBin = stage_07_bg_pal_bin; break;
	}
}

// Sets variables base on current player
void SetStageVariables(void) {
	Stage = CurrentPlayer == INDEX_PLAYER_01 ? P1Stage : P2Stage;
	PelletCount = CurrentPlayer == INDEX_PLAYER_01 ? P1PelletCount : P2PelletCount;
	GhostMode = CurrentPlayer == INDEX_PLAYER_01 ? P1GhostMode : P2GhostMode;
    GhostModeTimer = CurrentPlayer == INDEX_PLAYER_01 ? P1GhostModeTimer : P2GhostModeTimer;
}

// Sets stage data based on current player
// Refreshes with new data, or player current progress stage data
void SetStageData(unsigned char refresh, unsigned char clearScrollY) {
	// Reset vertical scroll if ScrollY reset
	if (clearScrollY == 1) {
		ScrollYAmount = 0;
    	ScrollY = 0;
		SMS_setBGScrollY(0);
		SMS_displayOff();
	}
	// Set game as paused
	Paused = 1;
	// Set stage variables based on current player, if ScrollY reset
	SetStageVariables();
	// Set current player stage data
	if (clearScrollY == 1) {
		SetPlayerStage(refresh);
	}
	// Set current player(s) flashing text
	SetPlayerFlashingText();
	// Set current player palette
	SetPlayerPalette();
	// Load BG palette and save palette index for energizer flashing
	SMS_mapROMBank(StagePaletteBank);
	SMS_loadBGPalette(StagePaletteBin);
	EnergizerColor = StagePaletteBin[12];
	// Load SPR palette
	SMS_mapROMBank(main_spr_pal_bin_bank);
	SMS_loadSpritePalette(main_spr_pal_bin);
	// Load sprite tiles
	SMS_mapROMBank(sprite_tiles_bin_bank);
	SMS_loadTiles(sprite_tiles_bin, 8, sprite_tiles_bin_size);
	// Wait for vertical blank
	SMS_waitForVBlank();
	// Load stage tiles
	SMS_mapROMBank(stage_tiles_bin_bank);
	SMS_loadTiles(stage_tiles_bin, 256, stage_tiles_bin_size);
	// Wait for vertical blank
	SMS_waitForVBlank();
	// Update HUD
	SetHud();
	// Clear sprites on screen
	ClearSprites();
	// Set ghosts
	SetGhost(INDEX_BLINKY, DIRECTION_LEFT, ENTITY_STATE_IDLE, 128, 116);
	SetGhost(INDEX_PINKY, DIRECTION_DOWN, ENTITY_STATE_IDLE, 128, 140);
	SetGhost(INDEX_INKY, DIRECTION_UP, ENTITY_STATE_IDLE, 112, 140);
	SetGhost(INDEX_SUE, DIRECTION_UP, ENTITY_STATE_IDLE, 144, 140);
	// Set player(s)
	if (GameMode == GAME_MODE_TEAM_PLAY) {
		SetPlayer(INDEX_PLAYER_01, ENTITY_PLAYER_01, DIRECTION_LEFT, ENTITY_STATE_IDLE, 120, 212);
		SetPlayer(INDEX_PLAYER_02, ENTITY_PLAYER_02, DIRECTION_RIGHT, ENTITY_STATE_IDLE, 136, 212);
	} else if (GameMode == GAME_MODE_TWO_PLAYER) {
		SetPlayer(INDEX_PLAYER_01, ENTITY_PLAYER_01, DIRECTION_LEFT, ENTITY_STATE_IDLE, 128, 212);
		SetPlayer(INDEX_PLAYER_02, ENTITY_PLAYER_02, DIRECTION_LEFT, ENTITY_STATE_IDLE, 128, 212);
	} else {
		SetPlayer(INDEX_PLAYER_01, ENTITY_PLAYER_01, DIRECTION_LEFT, ENTITY_STATE_IDLE, 128, 212);
	}
	// Set bonus
	SetBonus(ENTITY_STATE_NONE);
	// Wait for vertical blank
	SMS_waitForVBlank();
	UpdateBonusTiles(0);
	// Wait for vertical blank
	SMS_waitForVBlank();
	UpdateBonusTiles(1);
	// Wait for vertical blank
	SMS_waitForVBlank();
	SMS_displayOn();
}

// Loads stage data
void SetStage(void) {
	SMS_displayOff();
	ResetGlobalVariables();
	ClearVRAM();
    SMS_waitForVBlank();
	SMS_setSpriteMode (SPRITEMODE_TALL);
	SMS_useFirstHalfTilesforSprites(1);
	SetStageData(1, 1);
	PrevGameState = GameState;
	SMS_displayOn();
}

// Flash stage tiles using palette updates
void UpdateStagePalette(void) {
	// If game not running yet, return
	if (SubState < 4) {
		return;
	}
	// Flash energizers and 1up/2up
	if (Accumulator++ == TIME_32) {
		// 1UP/2UP flash off
		SMS_setBGPaletteColor(11, 0);
		// Energizers flash off
		SMS_setBGPaletteColor(12, 0);
	} else if (Accumulator++ == TIME_64) {
		// 1UP/2UP flash on
		SMS_setBGPaletteColor(11, 63);
		// Energizers flash on
		SMS_setBGPaletteColor(12, EnergizerColor);
		Accumulator = 0;
	}
}

// Flash stage when cleared
void FlashStage(void) {
	// Flash stage graphics off
	if (Accumulator++ == TIME_24) {
		SMS_mapROMBank(flash_bg_pal_bin_bank);
		SMS_loadBGPalette(flash_bg_pal_bin);
	// Flash stage graphics on
	} else if (Accumulator++ >= TIME_48) {
		SMS_mapROMBank(StagePaletteBank);
		SMS_loadBGPalette(StagePaletteBin);
		Accumulator = 0;
	}
}

// Updates sprites with set states
void UpdateStageSprites(void) {
	// Refresh frames from any previous state
	UpdateGhostSprites(INDEX_BLINKY);
	UpdateGhostSprites(INDEX_PINKY);
	UpdateGhostSprites(INDEX_INKY);
	UpdateGhostSprites(INDEX_SUE);
}

// Updates scrolling for the stage based on player
void UpdateStageScroll(void) {
	if (EntityState[CurrentPlayer] == ENTITY_STATE_MOVING && EntityDir[CurrentPlayer] == DIRECTION_UP && EntityY[CurrentPlayer] - ScrollY <= 88) {
		Scroller = CurrentPlayer;
		UpdateRow(DIRECTION_UP, EntitySpeed[CurrentPlayer]);
	} else if (EntityState[CurrentPlayer] == ENTITY_STATE_MOVING && EntityDir[CurrentPlayer] == DIRECTION_DOWN && EntityY[CurrentPlayer] - ScrollY >= 96) {
		Scroller = CurrentPlayer;
		UpdateRow(DIRECTION_DOWN, EntitySpeed[CurrentPlayer]);
	}
}

// Updates energizer and ghost mode timers
void UpdateStageTimers(void) {
	if (Paused > 0) {
		return;
	}
	// If deincrementing the energizer timer
	if (EnergizerTimer > -1) {
		EnergizerTimer--;
	// Restore BGM
	} else if (EnergizerTimer == -1) {
		PlayTrack(AUDIO_BGM, 1);
		EnergizerTimer--;
	}
	// If ghost mode timer past max value, return
	if (GhostModeTimer > TIME_1680) {
		return;
	}
	// Set ghost mode based on timer amount
	if (GhostModeTimer == TIME_450) {
		SetGhostMode(ENTITY_STATE_CHASING);
	} else if (GhostModeTimer == TIME_1080) {
		SetGhostMode(ENTITY_STATE_SCATTERING);
	} else if (GhostModeTimer == TIME_1680) {
		SetGhostMode(ENTITY_STATE_CHASING);
	}
	// Increment timer for player 1, set global timer
	if (CurrentPlayer == INDEX_PLAYER_01) {
		P1GhostModeTimer++;
		GhostModeTimer = P1GhostModeTimer;
	// Increment timer for player 2, set global timer
	} else {
		P2GhostModeTimer++;
		GhostModeTimer = P2GhostModeTimer;
	}
}

// Run game
void RunGame(void) {
	// Copy sprites to sprite attribute tables
	UNSAFE_SMS_copySpritestoSAT();
	// Clear sprites, ready for new sprites
	SMS_initSprites();
	// Refresh score in VRAM
	UpdateHudTop();
	// Stream player tiles
	UpdatePlayerTiles();
	// Handle scrolling
	UpdateStageScroll();
	// Flash energizer and current player 1up/2up tiles
	UpdateStagePalette();
	// Update entities
	UpdateGhost(INDEX_BLINKY);
	UpdateGhost(INDEX_PINKY);
	UpdateGhost(INDEX_INKY);
	UpdateGhost(INDEX_SUE);
	UpdateBonus();
	// Update player 1 if current player
	if (CurrentPlayer == INDEX_PLAYER_01) {
		UpdatePlayer(INDEX_PLAYER_01);
	}
	// Update plyaer 2 if current player or in team mode
	if (GameMode == GAME_MODE_TEAM_PLAY || CurrentPlayer == INDEX_PLAYER_02) {
		UpdatePlayer(INDEX_PLAYER_02);
	}
	// If not locking in vertical scroll amount, reset it
	if (ScrollLock == 0) {
		ScrollYAmount = 0;
	}
	// Clear ghost processing flag
	GhostProcessing = 0;
}

// Updates stage
void UpdateStage(void) {
	// Process based on substate
	switch (SubState) {
		// Stage start
		case 0:
			// Set player start
			SetPlayerStart();
			SubState++;
		break;
		// Pause to show the score a bit
		case 1:
			if (IncrementTimer(TIME_60) == 1) { 
				SubState++;
			}
		break;
		// Scroll screen to bottom
		case 2:
			// Scroll down
			Scroller = INDEX_AUTO_SCROLL;
			UpdateRow(DIRECTION_DOWN, 1);
			// If current player is player 1 and has not not been through first run
			if (CurrentPlayer == INDEX_PLAYER_01 && P1Start == 1) {
				// When scroll reaches bottom of screen
				if (ScrollY >= 96) {
					// Clear out player 1 text or team text
					ClearPlayerText();
					// Remove a life
					P1Lives -= 1;
					// Update HUD to show removal
					UpdateHudBottom();
					// Set start flag and move on to next substate
					P1Start = 0;
					SubState++;
				}
			// If current player is player 2 and has not not been through first run
			} else if (CurrentPlayer == INDEX_PLAYER_02 && P2Start == 1) {
				// When scroll reaches bottom of screen, clear out player text, update lives display, onto next substate
				if (ScrollY >= 96) {
					// Clear out player 2 text
					ClearPlayerText();
					// Remove a life
					P2Lives -= 1;
					// Update HUD to show removal
					UpdateHudBottom();
					// Set start flag and move on to next substate
					P2Start = 0;
					SubState++;
				}
			// Current player already did first run
			} else {
				// Run game to show sprites
				RunGame();
				// When scroll reaches bottom of screen, onto next substate
				if (ScrollY >= 96) {
					// Update bottom of HUD to show any changes (Lives, current bonus level)
					UpdateHudBottom();
					SubState++;
				}
			}
		break;
		// Update entities
		case 3:
			// Run game to show sprites
			RunGame();
			// Pause a bit
			if (IncrementTimer(TIME_90) == 1) {
				// Unpause, update entity states
				Paused = 0;
				EntityState[INDEX_PLAYER_01] = ENTITY_STATE_MOVING;
				EntityState[INDEX_BLINKY] = GhostMode;
				EntityState[INDEX_PINKY] = ENTITY_STATE_LEAVING;
				EntityState[INDEX_INKY] = ENTITY_STATE_HOUSE;
				EntityState[INDEX_SUE] = ENTITY_STATE_HOUSE;
				// Refresh sprites to reflect updated states
				UpdateStageSprites();
				if (GameMode == GAME_MODE_TEAM_PLAY) {
					EntityState[INDEX_PLAYER_02] = ENTITY_STATE_MOVING;
				}
				// Clear Ready! text
				ClearReadyText();
				// Start BGM
				PlayTrack(AUDIO_BGM, 1);
				SubState++;
			}
		break;
		// Run game
		case 4:
			// Run game logic
			RunGame();
			UpdateStageTimers();
		break;
		// Player got chomped
		case 5:
			// Run game to show sprites, paused for a bit
			RunGame();
		break;
		// Stage cleared
		case 6:
			// Refresh sprites
			if (Timer <= 1) {
				RunGame();
			}
			// Pause for a bit, then flash screen
			if (IncrementTimer(TIME_60) == 1) {
				Accumulator = 0;
				SubState++;
			}
		break;
		// Flash screen for stage cleared
		case 7:
			// Flash 4 times
			FlashStage();
			if (IncrementTimer(TIME_104) == 1) {
				SubState++;
			}
		break;
		// Load next stage
		case 8:
			// Pause a bit
			if (IncrementTimer(TIME_30) == 1) {
				// Run a cut scene or run next stage
				if (Stage == 1) {
					GameState = GAME_STATE_CUTSCENE_01;
				} else if (Stage == 4) {
					GameState = GAME_STATE_CUTSCENE_02;
				} else if (Stage == 8) {
					GameState = GAME_STATE_CUTSCENE_03;
				// Increment current player's stage, set stage for next stage
				} else {
					SetPlayerNextStage();
					SetStage();
				}
			}
		break;
		// Player dead
		case 9:
			RunGame();
			// Pause a bit
			if (IncrementTimer(TIME_60) == 1) {
				// If 2 player game mode
				if (GameMode == GAME_MODE_TWO_PLAYER) {
					// If both players have no lives left, game over
					if (P1Lives < 0 && P2Lives < 0) {
						ClearSprites();
						// Show game over text
						SetGameOverText();
						// Set sub state to game over
						SubState = 10;
						break;
					}
					// Switch current player
					if (CurrentPlayer == INDEX_PLAYER_01 && P2Lives > -1) {
						CurrentPlayer = INDEX_PLAYER_02;
						// If player hasn't started yet, use set stage
						if (P2Start == 1) {
							SetStage();
							break;
						}
					} else if (CurrentPlayer == INDEX_PLAYER_02 && P1Lives > -1) {
						CurrentPlayer = INDEX_PLAYER_01;
					// Same player, soft reset stage
					} else {
						SetStageData(0, 0);
						SetReadyText();
						SubState = 1;
						break;
					}
					// Hard reset stage
					SetStageData(0, 1);
					SubState = 0;
				} else {
					// If player 1 game over
					if (P1Lives < 0) {
						ClearSprites();
						// Show game over text
						SetGameOverText();
						// Set sub state to game over
						SubState = 10;
						break;
					// Soft reset for another try
					} else {
						SetStageData(0, 0);
						SetReadyText();
						SubState = 1;
					}
				}
			}
		break;
		// Game over
		case 10:
			// Pause a bit, go to title
			if (IncrementTimer(TIME_120) == 1) {
				ResetPlayerVariables();
				GameState = GAME_STATE_TITLE;
			}
		break;
	}
}