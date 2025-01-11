// Score amounts
const unsigned short hud_points[] = { 0, 10, 50, 100, 200, 400, 500, 700, 800, 1000, 1600, 2000, 5000 };
const unsigned char hud_amount_0[] = { 0, 0, 0, 0, 0, 0 };
const unsigned char hud_amount_10[] = { 0, 0, 0, 0, 1, 0 };
const unsigned char hud_amount_50[] = { 0, 0, 0, 0, 5, 0 };
const unsigned char hud_amount_100[] = { 0, 0, 0, 1, 0, 0 };
const unsigned char hud_amount_200[] = { 0, 0, 0, 2, 0, 0 };
const unsigned char hud_amount_400[] = { 0, 0, 0, 4, 0, 0 };
const unsigned char hud_amount_500[] = { 0, 0, 0, 5, 0, 0 };
const unsigned char hud_amount_700[] = { 0, 0, 0, 7, 0, 0 };
const unsigned char hud_amount_800[] = { 0, 0, 0, 8, 0, 0 };
const unsigned char hud_amount_1000[] = { 0, 0, 1, 0, 0, 0 };
const unsigned char hud_amount_1600[] = { 0, 0, 1, 6, 0, 0 };
const unsigned char hud_amount_2000[] = { 0, 0, 2, 0, 0, 0 };
const unsigned char hud_amount_5000[] = { 0, 0, 5, 0, 0, 0 };
const unsigned char *hud_amounts[] = { hud_amount_0, hud_amount_10, hud_amount_50, hud_amount_100, hud_amount_200, hud_amount_400, hud_amount_500, hud_amount_700, 
	hud_amount_800, hud_amount_1000, hud_amount_1600, hud_amount_2000, hud_amount_5000 };

// HUD slots
const unsigned short hud_slot_00[] = { 1092, 1093, 1124, 1125 };
const unsigned short hud_slot_01[] = { 1094, 1095, 1126, 1127 };
const unsigned short hud_slot_02[] = { 1096, 1097, 1128, 1129 };
const unsigned short hud_slot_03[] = { 1098, 1099, 1130, 1131 };
const unsigned short hud_slot_04[] = { 1100, 1101, 1132, 1133 };
const unsigned short hud_slot_05[] = { 1102, 1103, 1134, 1135 };
const unsigned short hud_slot_06[] = { 1104, 1105, 1136, 1137 };
const unsigned short hud_slot_07[] = { 1106, 1107, 1138, 1139 };
const unsigned short hud_slot_08[] = { 1108, 1109, 1140, 1141 };
const unsigned short hud_slot_09[] = { 1110, 1111, 1142, 1143 };
const unsigned short hud_slot_10[] = { 1112, 1113, 1144, 1145 };
const unsigned short hud_slot_11[] = { 1114, 1115, 1146, 1147 };
const unsigned short *slots[] = { hud_slot_00, hud_slot_01, hud_slot_02, hud_slot_03, hud_slot_04, hud_slot_05, hud_slot_06, hud_slot_07, hud_slot_08, 
	hud_slot_09, hud_slot_10, hud_slot_11 };

// HUD items
const unsigned short hud_banana[] = { 256, 324, 339, 340 };
const unsigned short hud_pear[] = { 322, 323, 337, 338 };
const unsigned short hud_apple[] = { 320, 321, 335, 336 };
const unsigned short hud_pretzel[] = { 318, 319, 333, 334 };
const unsigned short hud_orange[] = { 316, 317, 332, 332 | TILE_FLIPPED_X };
const unsigned short hud_strawberry[] = { 314, 315, 330, 331 };
const unsigned short hud_cherry[] = { 312, 313, 328, 329 };
const unsigned short hud_ms_pac_man_p1[] = { 308, 309, 325, 326 };
const unsigned short hud_ms_pac_man_p2[] = { 310, 311, 325, 327 };
const unsigned short hud_empty[] = { 256, 256, 256, 256 };
const unsigned short *hud_items[] = { hud_banana, hud_pear, hud_apple, hud_pretzel, hud_orange, hud_strawberry, hud_cherry, hud_ms_pac_man_p1, hud_ms_pac_man_p2, hud_empty };

// Set the given HUD slot with given HUD item
void SetHudSlot(unsigned char slot, unsigned char item) {
	// Iterate through 4 tiles
	for (unsigned char i = 0; i < 4; i++) {
		// If player 1 map, set tile index with tile id
		if (CurrentPlayer == INDEX_PLAYER_01) {
			P1Map[slots[slot][i]] = hud_items[item][i];
		// Player 2 map, set tile index with tile id
		} else {
			P2Map[slots[slot][i]] = hud_items[item][i];
		}
	}
}

// Sets lives on HUD
void SetHudLives(unsigned char lives, unsigned char item) {
	// Iterate to maximum lives display value (5)
	for (unsigned char i = 0; i < 5; i++) {
		// Slot in a life
		if (lives > i) {
			SetHudSlot(i, item);
		// Slot in an empty
		} else {
			SetHudSlot(i, HUD_EMPTY);
		}
	}
}

// Sets bonus items on HUD
void SetBonusItems(void) {
	// Iterate through bonus item slots, starting at the right most slot
	for (unsigned char i = 11; i > 4; i--) {
		// Populate slots based on current level
		if (11 - i <= Stage) {
			SetHudSlot(i, i - 5);
		}
	}
}

// Adds given amount to given array
void AddAmount(unsigned char amountIndex, unsigned char offset) {
	// Local vars
	unsigned char carry = 0;
	unsigned char sum;
	// 6th digit
	sum = ((Scores[offset + 5] - TILE_NUMS) + hud_amounts[amountIndex][5]) + carry;
	carry = (sum > 9) ? 1 : 0;
	Scores[offset + 5] = ((sum > 9) ? sum - 10 : sum) + TILE_NUMS;
	// 5th digit
	sum = ((Scores[offset + 4] - TILE_NUMS) + hud_amounts[amountIndex][4]) + carry;
	carry = (sum > 9) ? 1 : 0;
	Scores[offset + 4] = ((sum > 9) ? sum - 10 : sum) + TILE_NUMS;
	// 4th digit
	sum = ((Scores[offset + 3] - TILE_NUMS) + hud_amounts[amountIndex][3]) + carry;
	carry = (sum > 9) ? 1 : 0;
	Scores[offset + 3] = ((sum > 9) ? sum - 10 : sum) + TILE_NUMS;
	// 3rd digit
	sum = ((Scores[offset + 2] - TILE_NUMS) + hud_amounts[amountIndex][2]) + carry;
	carry = (sum > 9) ? 1 : 0;
	Scores[offset + 2] = ((sum > 9) ? sum - 10 : sum) + TILE_NUMS;
	// 2nd digit
	sum = ((Scores[offset + 1] - TILE_NUMS) + hud_amounts[amountIndex][1]) + carry;
	carry = (sum > 9) ? 1 : 0;
	Scores[offset + 1] = ((sum > 9) ? sum - 10 : sum) + TILE_NUMS;
	// 1st digit
	sum = ((Scores[offset] - TILE_NUMS) + hud_amounts[amountIndex][0]) + carry;
	Scores[offset] = ((sum > 9) ? sum - 10 : sum) + TILE_NUMS;
}

// Updates top partion of the HUD in VRAM using UNSAFE method
void UpdateHudTop(void) {
	// Update top of HUD, if visible
	if (ScrollY <= 16) {
		UNSAFE_SMS_VRAMmemcpy64(TILE_MAP_32, Scores);
	}
}

// Updates top partion of the HUD in VRAM using safe method
void UpdateHudTopSafe(void) {
	// Update top of HUD, if visible
	if (ScrollY <= 16) {
		SMS_loadTileMapArea(0, 1, Scores, 32, 1);
	}
}

// Updates bottom partion of the HUD in VRAM
void UpdateHudBottom(void) {
	// Update bottom of HUD
	if (CurrentPlayer == INDEX_PLAYER_01) {
		SetHudLives(P1Lives, HUD_MS_PAC_MAN_P1);
		// Update display if visible
		if (ScrollY >= 80) {
			SMS_loadTileMapArea(0, GetRow(34), &P1Map[1088], 32, 2);
		}
	} else {
		SetHudLives(P2Lives, HUD_MS_PAC_MAN_P2);
		// Update display if visible
		if (ScrollY >= 80) {
			SMS_loadTileMapArea(0, GetRow(34), &P2Map[1088], 32, 2);
		}
	}
}

// Updates the score with the given points constant eg. POINTS_10
void AddScore(unsigned char index, unsigned char amountIndex) {
	// Update player amount
	if (index == INDEX_PLAYER_01) {
		// If under the extra life score, but will earn an extra life with points added
		if (P1Score < ExtraLife && P1Score + hud_points[amountIndex] >= ExtraLife) {
			P1Lives++;
			UpdateHudBottom();
			PlayTrack(AUDIO_EXTRA_LIFE, 0);
		}
		P1Score += hud_points[amountIndex];
		AddAmount(amountIndex, 3);
	} else {
		// If under the extra life score, but will earn an extra life with points added
		if (P2Score < ExtraLife && P2Score + hud_points[amountIndex] >= ExtraLife) {
			P2Lives++;
			UpdateHudBottom();
			PlayTrack(AUDIO_EXTRA_LIFE, 0);
		}
		P2Score += hud_points[amountIndex];
		AddAmount(amountIndex, 23);
	}
	// If player 1 score is the highest score, set high score to player 1
	if (P1Score > P2Score && P1Score > HighScore) {
		HighScore = P1Score;
		memcpy(&Scores[13], &Scores[3], 12);
	// If player 2 score is the highest score, set high score to player 2
	} else if (P2Score > P1Score && P2Score > HighScore) {
		HighScore = P2Score;
		memcpy(&Scores[13], &Scores[23], 12);
	}
}

// Sets HUD
void SetHud(void) {
	SetBonusItems();
	UpdateHudTopSafe();
	UpdateHudBottom();
}