// Direction types
#define DIRECTION_RIGHT 0
#define DIRECTION_DOWN 1
#define DIRECTION_LEFT 2
#define DIRECTION_UP 3
#define DIRECTION_ALL 4
#define DIRECTION_NONE 5

// Game modes
#define GAME_MODE_ONE_PLAYER 0
#define GAME_MODE_TWO_PLAYER 1
#define GAME_MODE_TEAM_PLAY 2

// Visibility types
#define IN_VIEW 0
#define OUT_OF_VIEW_TOP 1
#define OUT_OF_VIEW_BOTTOM 2

// Game states
#define GAME_STATE_NONE 0
#define GAME_STATE_TITLE 1
#define GAME_STATE_STAGE 2
#define GAME_STATE_CUTSCENE_01 3
#define GAME_STATE_CUTSCENE_02 4
#define GAME_STATE_CUTSCENE_03 5

// Entity indexes
#define INDEX_BLINKY 0
#define INDEX_PINKY 1
#define INDEX_INKY 2
#define INDEX_SUE 3
#define INDEX_BONUS 4
#define INDEX_PLAYER_01 5
#define INDEX_PLAYER_02 6
#define INDEX_MISC 7
#define INDEX_AUTO_SCROLL 254
#define INDEX_NONE 255

// HUD Item indexes
#define HUD_BANANA 0
#define HUD_PEAR 1
#define HUD_APPLE 2
#define HUD_PRETZEL 3
#define HUD_ORANGE 4
#define HUD_STRAWBERRY 5
#define HUD_CHERRY 6
#define HUD_MS_PAC_MAN_P1 7
#define HUD_MS_PAC_MAN_P2 8
#define HUD_EMPTY 9

// Entity types
#define ENTITY_EMPTY 0
#define ENTITY_PLAYER_01 1
#define ENTITY_PLAYER_02 2
#define ENTITY_BLINKY 3
#define ENTITY_PINKY 4
#define ENTITY_INKY 5
#define ENTITY_SUE 6
#define ENTITY_CHERRY 7
#define ENTITY_STRAWBERRY 8
#define ENTITY_ORANGE 9
#define ENTITY_PRETZEL 10
#define ENTITY_APPLE 11
#define ENTITY_PEAR 12
#define ENTITY_BANANA 13
#define ENTITY_PAC_MAN 14

// Point indexes
#define POINTS_0 0
#define POINTS_10 1
#define POINTS_50 2
#define POINTS_100 3
#define POINTS_200 4
#define POINTS_400 5
#define POINTS_500 6
#define POINTS_700 7
#define POINTS_800 8
#define POINTS_1000 9
#define POINTS_1600 10
#define POINTS_2000 11
#define POINTS_5000 12

// Audio tracks
#define AUDIO_NONE 0
#define AUDIO_READY 1
#define AUDIO_BGM 2
#define AUDIO_PLAYER_CHOMPED 3
#define AUDIO_ENERGIZER 4
#define AUDIO_AFTER_GHOST_CHOMPED 5
#define AUDIO_EXTRA_LIFE 6
#define AUDIO_THEY_MEET 7
#define AUDIO_THE_CHASE 8
#define AUDIO_JUNIOR 9

// SFX
#define SFX_NONE 0
#define SFX_CONFIRM 1
#define SFX_PELLET 2
#define SFX_GHOST_CHOMPED 3
#define SFX_BONUS_BOUNCE 4
#define SFX_BONUS_CHOMPED 5

// Entity state types
#define ENTITY_STATE_NONE 0
#define ENTITY_STATE_SCENE 1
#define ENTITY_STATE_DEMO 2
#define ENTITY_STATE_IDLE 3
#define ENTITY_STATE_MOVING 4
#define ENTITY_STATE_BOUNCING 5
#define ENTITY_STATE_CHASING 6
#define ENTITY_STATE_SCATTERING 7
#define ENTITY_STATE_DYING 8
#define ENTITY_STATE_DEAD 9
#define ENTITY_STATE_ENERGIZED 10
#define ENTITY_STATE_FRIGHTENED 11
#define ENTITY_STATE_POINTS 12
#define ENTITY_STATE_HOUSE 13
#define ENTITY_STATE_CHOMPED 14
#define ENTITY_STATE_ENTERING 15
#define ENTITY_STATE_LEAVING 16

// Tiles
#define TILE_EMPTY 256
#define TILE_ENERGIZER 257
#define TILE_PELLET 258
#define TILE_NUMS 259
#define TILE_TUNNEL 307
#define TILE_SOLID 340
#define TILE_MAP_0 14336
#define TILE_MAP_32 14400

// Timings NTSC/PAL
#define TIME_NTSC

#ifdef TIME_NTSC
#define TIME_00 0
#define TIME_01 1
#define TIME_02 2
#define TIME_04 4
#define TIME_06 6
#define TIME_08 8
#define TIME_24 24
#define TIME_30 30
#define TIME_32 32
#define TIME_40 40
#define TIME_48 48
#define TIME_60 60
#define TIME_64 64
#define TIME_90 90
#define TIME_104 104
#define TIME_120 120
#define TIME_150 150
#define TIME_180 180
#define TIME_210 210
#define TIME_240 240
#define TIME_270 270
#define TIME_300 300
#define TIME_330 330
#define TIME_360 360
#define TIME_390 390
#define TIME_420 420
#define TIME_450 450
#define TIME_1080 1080
#define TIME_1680 1680
#else
#define TIME_00 0
#define TIME_01 1
#define TIME_02 2
#define TIME_04 4
#define TIME_06 6
#define TIME_08 8
#define TIME_24 24
#define TIME_30 30
#define TIME_32 32
#define TIME_48 48
#define TIME_60 60
#define TIME_64 64
#define TIME_90 90
#define TIME_104 104
#define TIME_120 120
#define TIME_150 150
#define TIME_180 180
#define TIME_210 210
#define TIME_240 240
#define TIME_270 270
#define TIME_300 300
#define TIME_330 330
#define TIME_360 360
#define TIME_390 390
#define TIME_420 420
#define TIME_450 450
#define TIME_1080 1080
#define TIME_1680 1680
#endif