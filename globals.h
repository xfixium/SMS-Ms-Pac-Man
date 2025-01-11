// Test array, for debugging
unsigned short Tests[8];

// Indexes: 0 = blinky, 1 = pinky, 2 = inky, 3 = sue, 4 = bonus, 5 = player 1, 6 = player 2, 7 = misc. eg. INDEX_PLAYER_01
static unsigned char EntityType[8];             // The type of entity constant eg. ENTITY_BONUS_CHERRY
static unsigned short EntityTile[8];            // The tile index based on position
static unsigned short EntityPrevTile[8];        // The previous tile index based on position
static unsigned short EntityX[8];               // Current horizontal position in pixels
static unsigned short EntityY[8];               // Current vertical position in pixels
static signed char EntityPixelX[8];             // Horizontal tile pixel amount
static signed char EntityPixelY[8];             // Vertical tile pixel amount
static signed char EntityDistX[8];              // Horizontal distance to mid tile in pixels
static signed char EntityDistY[8];              // Vertical distance to mid tile in pixels
static unsigned char EntityDir[8];              // Direction constant eg. DIRECTION_RIGHT
static unsigned char EntityState[8];            // Entity state constant eg. ENTITY_STATE_IDLE
static unsigned char EntitySubState[8];         // Entity sub state constant eg. ENTITY_STATE_ENERGIZED
static unsigned char EntitySpeed[8];            // Entity speed in pixels
static unsigned char EntitySubSpeed[8];         // Max sub speed to be applied to accumulative sub speed
static unsigned char EntityAccSubSpeed[8];      // Current accumulative sub pixel speed
static unsigned char EntityFrame[8];            // Current animation frame index
static signed char EntityFrameDuration[8];      // The amount of time to show the current frame of animation
static unsigned short EntityTimer[8];           // Entity general use timer
static unsigned char EntityLutIndex[8];         // Look up table index
static unsigned char EntityTarget[8];           // Target entity
static unsigned short EntityTargetTile[8];      // Tile the entity is moving towards
static unsigned char EntityVisibility[8];       // Entity visibility type 0 = in view, 1 = offscreen top, 2 = offscreen bottom

// Streaming tiles for players
static unsigned short PlayerFrame[2];

// General
static signed char Paused;          	        // If game paused
static unsigned char GameState;         	    // Current game state
static unsigned char PrevGameState;     	    // Previous game state
static unsigned char SubState;          	    // Sub state to the game state
static unsigned char AudioBank;		            // Current audio track's bank
static unsigned char Track;                     // Current BGM
static unsigned char PrevTrack;                 // Previous BGM
static unsigned char SfxBank;		            // Current sound effect's bank
static unsigned char Sfx;		                // Current sound effect
static unsigned char ScrollY;				    // Hardware vertical scroll position
static signed char ScrollYAmount;				// Vertical scroll amount per frame applied to entities
static unsigned char ScrollLock;				// Vertical scroll amount per frame applied to entities
static unsigned char Scroller;                  // Entity scrolling the map 255 = auto, entity index for everything else
static unsigned char AutoScrollDir;             // Auto scroll direction eg. DIRECTION_UP
static unsigned char FrameCounter;			    // Vertical blank frame counter
static unsigned short Timer;				    // General use timer
static unsigned char Rng;					    // General use random number
static unsigned short Accumulator;			    // 16 bit Accumulator
static unsigned short KeysPressed;			    // Input keys pressed
static unsigned short KeysHeld;				    // Input keys held
static unsigned char EnergizerColor;            // Current stage energizer palette index for blinking
static unsigned char GameMode;                  // Game mode eg. GAME_MODE_ONE_PLAYER
static unsigned char PacBoost;                  // If using pac boost
static unsigned char CurrentPlayer;             // Current player eg. INDEX_PLAYER_01
static unsigned char DefaultLives;              // The default amount of lives the player starts with (3 - 5)
static unsigned char Stage;                     // Current stage
static unsigned char StageMap;                  // Current stage map
static unsigned char StagePaletteBank;          // Current player stage palette bank number
static const unsigned char *StagePaletteBin;    // Current player stage BG palette data
static unsigned char PelletCount;               // Current player consumed pellets
static unsigned char GhostMode;                 // Current player ghost mode for stages
static unsigned short GhostModeTimer;           // Current player ghost mode timer
static unsigned short GhostPointAcc;            // Ghost chomp point accumulation: 200, 400, 800, 1600
static signed short EnergizerTimer;             // Energizer timer amount
static unsigned short EnergizerTimerHalf;       // Energizer timer half way amount

// Players
static unsigned char P1Start;                   // Player 1 start flag (Show player 1 text, and play start music, happens only once)
static unsigned char P2Start;                   // Player 2 start flag (Show player 2 text, and play start music, happens only once)
static unsigned char P1PelletCount;             // Player 1 consumed pellets
static unsigned char P2PelletCount;             // Player 2 consumed pellets
static signed char P1Lives;                     // Player 1 lives
static signed char P2Lives;                     // Player 2 lives
static unsigned char P1Stage;                   // Player 1 current stage
static unsigned char P2Stage;                   // Player 2 current stage
static unsigned char P1GhostMode;               // Player 1 ghost mode for stages
static unsigned char P2GhostMode;               // Player 2 ghost mode for stages
static unsigned short P1GhostModeTimer;         // Player 1 ghost mode timer
static unsigned short P2GhostModeTimer;         // Player 2 ghost mode timer
static unsigned short P1Map[1152];              // Player 1 tilemap data
static unsigned short P2Map[1152];              // Player 2 tilemap data

// Bonuses
static unsigned char BonusPathIndex;            // Index that travels along a set path
static const unsigned char *BonusPath;          // Current bonus path taken
static unsigned char BonusPathSize;             // Size of the current path
static unsigned char BonusTypeIndex;            // Current bonus type index
static unsigned char BonusTypes[2];             // Current bonus types

// Bounce offset values
static const signed char Bounce[] = { -1, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, -1, 0, 0 };

// Scores
static unsigned long P1Score;                   // Player 1 high score
static unsigned long P2Score;                   // Player 2 high score
static unsigned long HighScore;                 // Current high score
static unsigned short ExtraLife = 10000;        // Score needed to get an extra life, left as variable that can be adjusted
// Score characters
static unsigned short Scores[] = {
    256, 256, 256, 259, 259, 259, 259, 259, 259, 256, 256, 256, 256, 259, 259, 259, 259, 259, 259, 256, 256, 256, 256, 259, 259, 259, 259, 259, 259, 256, 256, 256
};

// Ghosts
static unsigned char GhostProcessing;                                   // If a ghost is processing a target
static unsigned char GhostDirs[5];                                      // Available directions of movement for a ghost
static const unsigned char GhostOffsets[] = { 0, 64, 128, 192 };        // Ghost rng offsets
static const unsigned short ScatterTargets[] = { 29, 2, 1117, 1090 };   // Ghost corner targets
// 6, 5, 4, 3, 2, 5, 2, 2, 1, 5, 2, 1, 1, 3, 1, 1, 0, 1, 0, 0, 0, 6, 6, 6, 6
static const unsigned short GhostFrightenedDurations[] = {
    TIME_420, TIME_360, TIME_300, TIME_240, TIME_180, TIME_180, TIME_120, TIME_360, 
    TIME_240, TIME_120, TIME_120, TIME_240, TIME_120, TIME_120, TIME_00, TIME_120, 
    TIME_00, TIME_120, TIME_00, TIME_00, TIME_00, TIME_420, TIME_420, TIME_420, TIME_420
};

// Number of pellets to consume each stage
static const unsigned char PelletCounts[] = { 
    224, 224, 244, 244, 244, 242, 242, 242, 242, 238, 238, 238, 238, 242, 242, 242, 242, 238, 238, 238, 238, 186, 186, 186, 186
};

// Stage map used for each stage, there are 7 of them (4 actual maps, 7 different palettes)
static const unsigned char StageMaps[] = { 0, 0, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6 };

// Bonus items table of 32 values, for random bonus after stage 7
static const unsigned char Bonuses[] = { 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3 };

// Scene constants
static unsigned char ActClackerFrame;
static const unsigned short ActBottom[] = { 413, 414, 415, 416, 426, 427, 428, 429 };
static const unsigned short ActTop_00[] = { 279, 407, 408, 409, 417, 418, 419, 279 };
static const unsigned short ActTop_01[] = { 279, 410, 411, 412, 420, 421, 422, 410 | TILE_FLIPPED_X | TILE_FLIPPED_Y };
static const unsigned short ActTop_02[] = { 279, 279, 279, 279, 423, 424, 424, 425 };