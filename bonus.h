// First bonus sprites
const unsigned char bonus_sprite_01[] = { 0, 0, 220, 8, 0, 222, METASPRITE_END };
const unsigned char bonus_points_01[] = { 0, 0, 224, 8, 0, 226, METASPRITE_END };
const unsigned char bonus_down_marker_01[] = { 0, 0, 228, 8, 0, 230, METASPRITE_END };
const unsigned char bonus_up_marker_01[] = { 0, 0, 232, 8, 0, 234, METASPRITE_END };

// Second bonus sprites
const unsigned char bonus_sprite_02[] = { 0, 0, 236, 8, 0, 238, METASPRITE_END };
const unsigned char bonus_points_02[] = { 0, 0, 240, 8, 0, 242, METASPRITE_END };
const unsigned char bonus_down_marker_02[] = { 0, 0, 244, 8, 0, 246, METASPRITE_END };
const unsigned char bonus_up_marker_02[] = { 0, 0, 248, 8, 0, 250, METASPRITE_END };

const unsigned char *bonus_sprites[] = { bonus_sprite_01, bonus_sprite_02 };
const unsigned char *bonus_points[] = { bonus_points_01, bonus_points_02 };
const unsigned char *bonus_down_markers[] = { bonus_down_marker_01, bonus_down_marker_02 };
const unsigned char *bonus_up_markers[] = { bonus_up_marker_01, bonus_up_marker_02 };

// Bonus starting areas per stage
const unsigned short bonus_stage_01_starts[] = { 670, 642, 354, 382 };
const unsigned short bonus_stage_02_starts[] = { 862, 834, 130, 158 };
const unsigned short bonus_stage_03_starts[] = { 414, 386, 386, 414 };
const unsigned short bonus_stage_04_starts[] = { 638, 610, 514, 542 };
const unsigned short bonus_stage_07_starts[] = { 510, 482, 482, 510 };

// Mid path around ghost house
const unsigned char bonus_circle_path[] = { 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2 };

// Stage 1 enter paths
const unsigned char bonus_enter_path_01[] = { 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3 };
const unsigned char bonus_enter_path_02[] = { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 2, 2, 2, 3, 3, 3 };
const unsigned char bonus_enter_path_03[] = { 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
const unsigned char bonus_enter_path_04[] = { 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 2, 2, 2, 1, 1, 1, 2, 2, 2 };
const unsigned char *stage_01_bonus_enter_paths[] = { bonus_enter_path_01, bonus_enter_path_02, bonus_enter_path_03, bonus_enter_path_04 };
const unsigned char stage_01_bonus_enter_path_sizes[] = { sizeof(bonus_enter_path_01), sizeof(bonus_enter_path_02), sizeof(bonus_enter_path_03), sizeof(bonus_enter_path_04) };

// Stage 2 enter paths
const unsigned char bonus_enter_path_05[] = { 2, 2, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 2 };
const unsigned char bonus_enter_path_06[] = { 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 2 };
const unsigned char bonus_enter_path_07[] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
const unsigned char bonus_enter_path_08[] = { 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
const unsigned char *stage_02_bonus_enter_paths[] = { bonus_enter_path_05, bonus_enter_path_06, bonus_enter_path_07, bonus_enter_path_08 };
const unsigned char stage_02_bonus_enter_path_sizes[] = { sizeof(bonus_enter_path_05), sizeof(bonus_enter_path_06), sizeof(bonus_enter_path_07), sizeof(bonus_enter_path_08) };

// Stage 3 enter paths
const unsigned char bonus_enter_path_09[] = { 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
const unsigned char bonus_enter_path_10[] = { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
const unsigned char bonus_enter_path_11[] = { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
const unsigned char bonus_enter_path_12[] = { 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2 };
const unsigned char *stage_03_bonus_enter_paths[] = { bonus_enter_path_09, bonus_enter_path_10, bonus_enter_path_11, bonus_enter_path_12 };
const unsigned char stage_03_bonus_enter_path_sizes[] = { sizeof(bonus_enter_path_09), sizeof(bonus_enter_path_10), sizeof(bonus_enter_path_11), sizeof(bonus_enter_path_12) };

// Stage 4 enter paths
const unsigned char bonus_enter_path_13[] = { 2, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3 };
const unsigned char bonus_enter_path_14[] = { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 3, 3, 3, 3, 3, 3 };
const unsigned char bonus_enter_path_15[] = { 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
const unsigned char bonus_enter_path_16[] = { 2, 2, 2, 2, 3, 3, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2 };
const unsigned char *stage_04_bonus_enter_paths[] = { bonus_enter_path_13, bonus_enter_path_14, bonus_enter_path_15, bonus_enter_path_16 };
const unsigned char stage_04_bonus_enter_path_sizes[] = { sizeof(bonus_enter_path_13), sizeof(bonus_enter_path_14), sizeof(bonus_enter_path_15), sizeof(bonus_enter_path_16) };

// Stage 7 enter paths
const unsigned char bonus_enter_path_17[] = { 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2 };
const unsigned char bonus_enter_path_18[] = { 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
const unsigned char bonus_enter_path_19[] = { 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
const unsigned char bonus_enter_path_20[] = { 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2 };
const unsigned char *stage_07_bonus_enter_paths[] = { bonus_enter_path_17, bonus_enter_path_18, bonus_enter_path_19, bonus_enter_path_20 };
const unsigned char stage_07_bonus_enter_path_sizes[] = { sizeof(bonus_enter_path_17), sizeof(bonus_enter_path_18), sizeof(bonus_enter_path_19), sizeof(bonus_enter_path_20) };

// Stage 1 exit paths
const unsigned char bonus_exit_path_01[] = { 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0 };
const unsigned char bonus_exit_path_02[] = { 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 2, 2, 2, 2 };
const unsigned char bonus_exit_path_03[] = { 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 3, 3, 3, 2, 2, 2, 2 };
const unsigned char bonus_exit_path_04[] = { 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0 };
const unsigned char *stage_01_bonus_exit_paths[] = { bonus_exit_path_01, bonus_exit_path_02, bonus_exit_path_03, bonus_exit_path_04 };
const unsigned char stage_01_bonus_exit_path_sizes[] = { sizeof(bonus_exit_path_01), sizeof(bonus_exit_path_02), sizeof(bonus_exit_path_03), sizeof(bonus_exit_path_04) };

// Stage 2 exit paths
const unsigned char bonus_exit_path_05[] = { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 };
const unsigned char bonus_exit_path_06[] = { 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2 };
const unsigned char bonus_exit_path_07[] = { 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2 };
const unsigned char bonus_exit_path_08[] = { 1, 1, 1, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0 };
const unsigned char *stage_02_bonus_exit_paths[] = { bonus_exit_path_05, bonus_exit_path_06, bonus_exit_path_07, bonus_exit_path_08 };
const unsigned char stage_02_bonus_exit_path_sizes[] = { sizeof(bonus_exit_path_05), sizeof(bonus_exit_path_06), sizeof(bonus_exit_path_07), sizeof(bonus_exit_path_08) };

// Stage 3 exit paths
const unsigned char bonus_exit_path_09[] = { 2, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0 };
const unsigned char bonus_exit_path_10[] = { 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2 };
const unsigned char bonus_exit_path_11[] = { 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2 };
const unsigned char bonus_exit_path_12[] = { 2, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 3, 3, 3, 3, 3, 3, 2, 2, 2, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0 };
const unsigned char *stage_03_bonus_exit_paths[] = { bonus_exit_path_09, bonus_exit_path_10, bonus_exit_path_11, bonus_exit_path_12 };
const unsigned char stage_03_bonus_exit_path_sizes[] = { sizeof(bonus_exit_path_09), sizeof(bonus_exit_path_10), sizeof(bonus_exit_path_11), sizeof(bonus_exit_path_12) };

// Stage 4 exit paths
const unsigned char bonus_exit_path_13[] = { 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 3, 3, 0, 0, 0, 0 };
const unsigned char bonus_exit_path_14[] = { 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 2, 3, 3, 2, 2, 2, 2 };
const unsigned char bonus_exit_path_15[] = { 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 2, 2, 2, 3, 3, 3, 2, 2, 2, 1, 1, 2, 2, 2, 2 };
const unsigned char bonus_exit_path_16[] = { 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 1, 1, 0, 0, 0, 0 };
const unsigned char *stage_04_bonus_exit_paths[] = { bonus_exit_path_13, bonus_exit_path_14, bonus_exit_path_15, bonus_exit_path_16 };
const unsigned char stage_04_bonus_exit_path_sizes[] = { sizeof(bonus_exit_path_13), sizeof(bonus_exit_path_14), sizeof(bonus_exit_path_15), sizeof(bonus_exit_path_16) };

// Stage 7 exit paths
const unsigned char bonus_exit_path_17[] = { 2, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2 };
const unsigned char bonus_exit_path_18[] = { 2, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2 };
const unsigned char bonus_exit_path_19[] = { 2, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2 };
const unsigned char bonus_exit_path_20[] = { 2, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2 };
const unsigned char *stage_07_bonus_exit_paths[] = { bonus_exit_path_17, bonus_exit_path_18, bonus_exit_path_19, bonus_exit_path_20 };
const unsigned char stage_07_bonus_exit_path_sizes[] = { sizeof(bonus_exit_path_17), sizeof(bonus_exit_path_18), sizeof(bonus_exit_path_19), sizeof(bonus_exit_path_20) };

// Sets the path based on the entity state
void SetBonusPath(void) {
	// If path already set, return
	if (BonusPathSize > 0) {
		return;
	}
	// Reset path variables
	BonusPathIndex = 0;
	BonusPathSize = 0;
	// Get random number 0 - 3
	unsigned char path = GetRng(6, INDEX_BONUS);
	// Set path based on state
	switch (EntityState[INDEX_BONUS]) {
		// Entering stage
		case ENTITY_STATE_ENTERING:
			switch (StageMap) {
				case 0:
					EntityTile[INDEX_BONUS] = bonus_stage_01_starts[path];
					BonusPath = stage_01_bonus_enter_paths[path];
					BonusPathSize = stage_01_bonus_enter_path_sizes[path];
				break;
				case 1:
					EntityTile[INDEX_BONUS] = bonus_stage_02_starts[path];
					BonusPath = stage_02_bonus_enter_paths[path];
					BonusPathSize = stage_02_bonus_enter_path_sizes[path];
				break;
				case 2:
				case 4:
					EntityTile[INDEX_BONUS] = bonus_stage_03_starts[path];
					BonusPath = stage_03_bonus_enter_paths[path];
					BonusPathSize = stage_03_bonus_enter_path_sizes[path];
				break;
				case 3:
				case 5:
					EntityTile[INDEX_BONUS] = bonus_stage_04_starts[path];
					BonusPath = stage_04_bonus_enter_paths[path];
					BonusPathSize = stage_04_bonus_enter_path_sizes[path];
				break;
				case 6:
					EntityTile[INDEX_BONUS] = bonus_stage_07_starts[path];
					BonusPath = stage_07_bonus_enter_paths[path];
					BonusPathSize = stage_07_bonus_enter_path_sizes[path];
				break;
				default: return;
			}
			// Set X and Y positions based on tile index
			SetEntityPositionByTileIndex(INDEX_BONUS, EntityTile[INDEX_BONUS]);
			// Offset to center of tile
			EntityY[INDEX_BONUS] += 4;
		break;
		// Circling ghost house
		case ENTITY_STATE_HOUSE: 
			BonusPath = bonus_circle_path; 
			BonusPathSize = sizeof(bonus_circle_path);
		break;
		// Leaving stage
		case ENTITY_STATE_LEAVING:
			switch (StageMap) {
				case 0:
					BonusPath = stage_01_bonus_exit_paths[path];
					BonusPathSize = stage_01_bonus_exit_path_sizes[path];
				break;
				case 1:
					BonusPath = stage_02_bonus_exit_paths[path];
					BonusPathSize = stage_02_bonus_exit_path_sizes[path];
				break;
				case 2:
				case 4:
					BonusPath = stage_03_bonus_exit_paths[path];
					BonusPathSize = stage_03_bonus_exit_path_sizes[path];
				break;
				case 3:
				case 5:
					BonusPath = stage_04_bonus_exit_paths[path];
					BonusPathSize = stage_04_bonus_exit_path_sizes[path];
				break;
				case 6:
					BonusPath = stage_07_bonus_exit_paths[path];
					BonusPathSize = stage_07_bonus_exit_path_sizes[path];
				break;
				default: return;
			}
		break;
	}
	// Set initial direction
	EntityDir[INDEX_BONUS] = BonusPath[0];
	EntityPrevTile[INDEX_BONUS] = EntityTile[INDEX_BONUS];
}

// Resets bonus variables, set to given state
void ResetBonus(unsigned char state) {
	EntityState[INDEX_BONUS] = state;
	EntityX[INDEX_BONUS] = 0;
	EntityY[INDEX_BONUS] = 208;
	EntityTile[INDEX_BONUS] = 0;
	EntityPrevTile[INDEX_BONUS] = 0;
	EntityLutIndex[INDEX_BONUS] = 0;
	BonusPathIndex = 0;
	BonusPathSize = 0;
}

// Loads bonus data
void SetBonus(unsigned char state) {
	EntityState[INDEX_BONUS] = state;
	EntitySpeed[INDEX_BONUS] = 0;
	EntitySubSpeed[INDEX_BONUS] = 128;
	EntityTimer[INDEX_BONUS] = 0;
	ResetBonus(state);
	if (state == ENTITY_STATE_ENTERING) {
		SetBonusPath();
	}
}

// Streams bonus tiles
void UpdateBonusTiles(unsigned char slot) {
	// After stage 7, fruit is random
	unsigned char type = (Stage < 7 ? Stage : Bonuses[GetRng(3, slot << 5)]) + ENTITY_CHERRY;
	BonusTypes[slot] = type;
	// Get bonus type graphics index eg. cherry, strawberry, orange
	unsigned short index = (type - ENTITY_CHERRY) << 9; // 512
	// Destination position, based on slot
	unsigned short dst = slot == 0 ? 220 : 236;
	// Blit tile data to VRAM
	SMS_mapROMBank(bonus_tiles_bin_bank);
	// Copy over bonus sprite, points, up and down marker graphics
	SMS_loadTiles(&bonus_tiles_bin[index], dst, 512);
}

// Updates bonus sprites
void UpdateBonusSprites(void) {
	// Set visibility
	SetEntityVisibility(INDEX_BONUS);
    // Offset coordinates from origin and vertical hardware scroll
    unsigned char x = EntityX[INDEX_BONUS] - 8;
	unsigned char y = EntityY[INDEX_BONUS] - 8 - ScrollY + ScrollYAmount;
	// If chomped
	if (EntityState[INDEX_BONUS] == ENTITY_STATE_CHOMPED) {
		// Points sprite
		if (EntityVisibility[INDEX_BONUS] == IN_VIEW) {
			SMS_addMetaSprite(x, y, bonus_points[BonusTypeIndex]);
		}
	// Other states
	} else {
		// Add lut offset (Bouncing)
		if (Paused <= 0) {
			EntityLutIndex[INDEX_BONUS] = EntityLutIndex[INDEX_BONUS] + 1 >= sizeof(Bounce) ? 0 : EntityLutIndex[INDEX_BONUS] + 1;
		}
		// Add bounce to sprite
		if (EntityVisibility[INDEX_BONUS] == IN_VIEW) {
			y += Bounce[EntityLutIndex[INDEX_BONUS]];
		// Set bounce to marker
		} else {
			y = Bounce[EntityLutIndex[INDEX_BONUS]];
		}
		switch (EntityVisibility[INDEX_BONUS]) {
			case OUT_OF_VIEW_TOP: SMS_addMetaSprite(x, y + 4, bonus_up_markers[BonusTypeIndex]); break;
			case OUT_OF_VIEW_BOTTOM: SMS_addMetaSprite(x, 172 - y, bonus_down_markers[BonusTypeIndex]); break;
			default: SMS_addMetaSprite(x, y, bonus_sprites[BonusTypeIndex]); break;
		}
	}
}

// Checks for player collisions
unsigned char BonusCheckCollision(void) {
	// Player credited to chomp
	unsigned char index = CheckEntityCollision(INDEX_BONUS);
	// If no collision occurred, return 0
	if (index == 0) {
		return 0;
	}
	// Bonus has been chomped
	EntityState[INDEX_BONUS] = ENTITY_STATE_CHOMPED;
	// Add score
	switch (BonusTypes[BonusTypeIndex]) {
		case ENTITY_CHERRY: AddScore(index, POINTS_100); break;
		case ENTITY_STRAWBERRY: AddScore(index, POINTS_200); break;
		case ENTITY_ORANGE: AddScore(index, POINTS_500); break;
		case ENTITY_PRETZEL: AddScore(index, POINTS_700); break;
		case ENTITY_APPLE: AddScore(index, POINTS_1000); break;
		case ENTITY_PEAR: AddScore(index, POINTS_2000); break;
		case ENTITY_BANANA: AddScore(index, POINTS_5000); break;
	}
	// Play sound effect
	PlaySFX(SFX_BONUS_CHOMPED, SFX_CHANNEL2);
	// Collision occurred
	return 1;
}

// Moves the bonus upon it's set path, next stae when complete
void BonusFollowPath(unsigned char nextState) {
	// Check collision
	if (BonusCheckCollision() == 1) {
		return;
	}
	// Set the path, if it has not yet been done
	// If tile changed, time to update path index
	if (EntityPrevTile[INDEX_BONUS] != EntityTile[INDEX_BONUS]) {
		BonusPathIndex++;
		EntityPrevTile[INDEX_BONUS] = EntityTile[INDEX_BONUS];
		// Play sound effect
		PlaySFX(SFX_BONUS_BOUNCE, SFX_CHANNEL2);
		// If index out of bounds, set next state
		if (BonusPathIndex >= BonusPathSize) {
			// Set next state
			EntityState[INDEX_BONUS] = nextState;
			// Reset path
			BonusPathSize = 0;
			BonusPathIndex = 0;
			// If next state is none, reset / disable bonus
			if (nextState == ENTITY_STATE_NONE) {
				ResetBonus(ENTITY_STATE_NONE);
				return;
			}
			// Set new path based on state
			SetBonusPath();
		} else {
			EntityDir[INDEX_BONUS] = BonusPath[BonusPathIndex];
		}
	}
	// Move bonus
	MoveEntity(INDEX_BONUS, EntityDir[INDEX_BONUS]);
	EntityTile[INDEX_BONUS] = PositionToTileOffset(INDEX_BONUS);
}

// Updates bonus state
void UpdateBonusState(void) {
	// If paused, return
	if (Paused > 0) {
		return;
	}
	// Set path to follow based on state
	switch (EntityState[INDEX_BONUS]) {
		// Bonus eaten
		case ENTITY_STATE_CHOMPED:
			// Show points sprite for a bit
			if (EntityIncrementTimer(INDEX_BONUS, TIME_120) == 1) {
				ResetBonus(ENTITY_STATE_NONE);
			}
		break;
		// Entering the stage
		case ENTITY_STATE_ENTERING:
			BonusFollowPath(ENTITY_STATE_HOUSE);
		break;
		// Circling around the ghost house
		case ENTITY_STATE_HOUSE:
			BonusFollowPath(ENTITY_STATE_LEAVING);
		break;
		// Leaving the stage
		case ENTITY_STATE_LEAVING:
			BonusFollowPath(ENTITY_STATE_NONE);
		break;
	}
}

// Updates bonus
void UpdateBonus(void) {
	// If state is none, return. 
	// Player sets state when pellet count reaches 70 or 170
	if (EntityState[INDEX_BONUS] == ENTITY_STATE_NONE) {
		return;
	}
	UpdateBonusState();
	UpdateBonusSprites();
}