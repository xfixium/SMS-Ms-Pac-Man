// Handles current game state
void HandleGameState(void) {
	// Game state
	switch (GameState) {
		// Init
		case GAME_STATE_NONE:
			SMS_displayOff();
			ClearVRAM();
			SMS_mapROMBank(black_bg_pal_bin_bank);
			SMS_loadBGPalette(black_bg_pal_bin);
			SMS_loadSpritePalette(black_bg_pal_bin);
			SMS_displayOn();
			GameState = GAME_STATE_TITLE;
			GameMode = GAME_MODE_ONE_PLAYER;
		break;
		case GAME_STATE_TITLE: if (PrevGameState != GameState) { SetTitle(); } else { UpdateTitle(); } break;
		case GAME_STATE_STAGE: if (PrevGameState != GameState) { SetStage(); } else { UpdateStage(); } break;
		case GAME_STATE_CUTSCENE_01: if (PrevGameState != GameState) { SetTheyMeet(); } else { UpdateTheyMeet(); } break;
		case GAME_STATE_CUTSCENE_02: if (PrevGameState != GameState) { SetTheChase(); } else { UpdateTheChase(); } break;
		case GAME_STATE_CUTSCENE_03: if (PrevGameState != GameState) { SetJunior(); } else { UpdateJunior(); } break;
	}
}