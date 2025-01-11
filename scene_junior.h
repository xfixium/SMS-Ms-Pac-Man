// Junior
const unsigned short scene_junior_text[] = { 286, 294, 288, 285, 289, 291 };
const unsigned char baby_pac[] = { 0, 0, 232, METASPRITE_END };

// Stork
const unsigned char stork_bag[] = { 0, 0, 234, METASPRITE_END };
const unsigned char stork_00[] = { 0, 0, 236, 8, 0, 238, 16, 0, 240, 24, 0, 242, METASPRITE_END };
const unsigned char stork_01[] = { 0, 0, 236, 8, 0, 238, 16, 0, 244, 24, 0, 246, METASPRITE_END };
const unsigned char *stork_frames[] = { stork_00, stork_01 };

// Loads scene
void SetJunior(void) {
	SMS_displayOff();
    // Clear VRAM, set all tiles to empty tile
    ClearVRAM();
    ClearScreen(TILE_EMPTY);
    // Avoid grabage on the screen
    SMS_waitForVBlank();
    // Setup scene
	ResetGlobalVariables();
	SMS_setSpriteMode (SPRITEMODE_TALL);
	SMS_useFirstHalfTilesforSprites(1);
    // Load palettes
    SMS_mapROMBank(title_bg_pal_bin_bank);
    SMS_loadBGPalette(title_bg_pal_bin);
	SMS_mapROMBank(main_spr_pal_bin_bank);
	SMS_loadSpritePalette(main_spr_pal_bin);
    // Bring in sprite tiles for sprites
	SMS_mapROMBank(sprite_tiles_bin_bank);
	SMS_loadTiles(sprite_tiles_bin, 8, sprite_tiles_bin_size);
    // Bring in cut scene tiles
	SMS_mapROMBank(cut_scene_tiles_bin_bank);
	SMS_loadTiles(cut_scene_tiles_bin, 228, cut_scene_tiles_bin_size);
    // Bring in the number 3 tile from stage tiles
	SMS_mapROMBank(stage_tiles_bin_bank);
	SMS_loadTiles(&stage_tiles_bin[192], 164, 32);
    // Bring in title tiles for text
	SMS_mapROMBank(title_tiles_bin_bank);
	SMS_loadTiles(title_tiles_bin, 279, title_tiles_bin_size);
    SMS_loadTileMapArea(15, 9, scene_junior_text, 6, 1);
    // Set pac man and ms pac man
	SetPlayer(INDEX_PLAYER_01, ENTITY_PLAYER_01, DIRECTION_RIGHT, ENTITY_STATE_SCENE, 256, 200);
    SetPlayer(INDEX_PLAYER_02, ENTITY_PAC_MAN, DIRECTION_RIGHT, ENTITY_STATE_SCENE, 256, 200);
    // Set baby pac
    EntityX[INDEX_BONUS] = 256;
    EntityY[INDEX_BONUS] = 200;
    EntitySpeed[INDEX_BONUS] = 0;
    EntitySubSpeed[INDEX_BONUS] = 192;
    EntityLutIndex[INDEX_BONUS] = 0;
    // Set stork
    EntityX[INDEX_MISC] = 256;
    EntityY[INDEX_MISC] = 200;
    EntitySpeed[INDEX_MISC] = 0;
    EntitySubSpeed[INDEX_MISC] = 192;
    // Set up act clacker
    UpdateClacker(10, 7);
	PrevGameState = GameState;
    PlayTrack(AUDIO_JUNIOR, 0);
	SMS_displayOn();
}

// Updates stork sprite
void UpdateStork(void) {
    // If stork reched end of screen, return
    if (EntityX[INDEX_MISC] == 0) {
        return;
    }
    // Draw stork sprite
    SMS_addMetaSprite(EntityX[INDEX_MISC] -= GetEntityMoveSpeed(INDEX_MISC), EntityY[INDEX_MISC], stork_frames[EntityFrame[INDEX_MISC]]);
    // If not ready to update frame, return
    if (--EntityFrameDuration[INDEX_MISC] > -1) {
        return;
    }
    // Update stork frame
    EntityFrame[INDEX_MISC] = EntityFrame[INDEX_MISC] + 1 >= 2 ? 0 : EntityFrame[INDEX_MISC] + 1;
    EntityFrameDuration[INDEX_MISC] = 6;
}

// Updates baby pac sprite
void UpdateBabyPac(void) {
    // Follow stork
    if (SubState < 3) {
        SMS_addMetaSprite(EntityX[INDEX_MISC] - 4, EntityY[INDEX_MISC] - 2, stork_bag);
    // Falling
    } else if (SubState == 3) {
        unsigned char speed = GetEntityMoveSpeed(INDEX_BONUS);
        SMS_addMetaSprite(EntityX[INDEX_BONUS] -= speed, EntityY[INDEX_BONUS] += speed + 1, stork_bag);
    // Bounce
    } else if (SubState == 4) {
        EntityLutIndex[INDEX_BONUS] = EntityLutIndex[INDEX_BONUS] + 1 >= sizeof(Bounce) ? 0 : EntityLutIndex[INDEX_BONUS] + 1;
		unsigned char y = Bounce[EntityLutIndex[INDEX_BONUS]];
        unsigned char speed = GetEntityMoveSpeed(INDEX_BONUS);
        SMS_addMetaSprite(EntityX[INDEX_BONUS] -= speed, EntityY[INDEX_BONUS] + y, stork_bag);
    } else if (SubState == 5) {
        SMS_addMetaSprite(EntityX[INDEX_BONUS], EntityY[INDEX_BONUS], baby_pac);
    }
}

// Update scene entities
void UpdateJuniorEntities(void) {
    UNSAFE_SMS_copySpritestoSAT();
	SMS_initSprites();
    // If not ready to show sprites, return
    if (SubState == 0) {
        return;
    }
    // Update sprites
	UpdatePlayerTiles();
    // Freeze frame pac man and ms pac man
    EntityFrame[INDEX_PLAYER_01] = 0;
    EntityFrame[INDEX_PLAYER_02] = 0;
    // Update sprites
	UpdatePlayer(INDEX_PLAYER_01);
    UpdatePlayer(INDEX_PLAYER_02);
    UpdateStork();
    UpdateBabyPac();
}

// Updates junior scene
void UpdateJunior(void) {
	// Update entities
	UpdateJuniorEntities();
	switch (SubState) {
		// Clacker
		case 0:
            // Act number sprite
            UpdateActNumber(101, 79);
            // Update clacker animation every nth frame
            if (IncrementTimer(6) == 1) {
                // Update animation
                UpdateClacker(10, 7);
                // If 12th frame, next sub state
                if (ActClackerFrame == 12) {
				    SubState++;
                }
			}
		break;
        // Clear screen/sprites, setup entities
        case 1:
            // Clear screen
            ClearScreen(256);
            ClearSprites();
            // Set entity start positions
            EntityX[INDEX_PLAYER_01] = 48;
            EntityY[INDEX_PLAYER_01] = 176;
            EntityX[INDEX_PLAYER_02] = 32;
            EntityY[INDEX_PLAYER_02] = 176;
            EntityX[INDEX_MISC] = 255;
            EntityY[INDEX_MISC] = 64;
            SubState++;
        break;
        // Drop baby pac
        case 2:
            // If position where stork drops baby pac
            if (EntityX[INDEX_MISC] <= 160) {
                // Set baby position based on stork one last time
                EntityX[INDEX_BONUS] = EntityX[INDEX_MISC] - 4;
                EntityY[INDEX_BONUS] = EntityY[INDEX_MISC] - 2;
                // Speed up stork
                EntitySpeed[INDEX_MISC] = 1;
                EntitySubSpeed[INDEX_MISC] = 48;
                SubState++;
            }
        break;
        // Baby pac falling
        case 3:
            // If hit ground, on to next sub state
            if (EntityY[INDEX_BONUS] > 165) {
                EntityY[INDEX_BONUS] = 167;
                SubState++;
            }
        break;
        // Baby bouncing
        case 4:
            // If bounced twice, on to next sub state
            if (EntityX[INDEX_BONUS] < 96) {
                SubState++;
            }
        break;
        // Reveal junior then on to the next stage
        case 5:
            if (IncrementTimer(120) == 1) {
                SetPlayerNextStage();
                PrevGameState = 0;
                GameState = GAME_STATE_STAGE;
            }
        break;
	}
}