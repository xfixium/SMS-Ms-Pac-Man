// Plays the given track
void PlayTrack(unsigned char track, unsigned char repeat) {
	// If current track playing is extra life audio, return
	if (Track == AUDIO_EXTRA_LIFE) {
		return;
	}
	// Set audio to desired track
	const unsigned char *psg = 0;
	// Remember previous track
	PrevTrack = Track;
	// Set current track
	Track = track;
	// Set up track data based on given track
	switch (track) {
		case AUDIO_BGM: AudioBank = audio_bgm_psg_bank; psg = audio_bgm_psg; break;
		case AUDIO_READY: AudioBank = audio_ready_psg_bank; psg = audio_ready_psg; break;
		case AUDIO_PLAYER_CHOMPED: AudioBank = audio_player_chomped_psg_bank; psg = audio_player_chomped_psg; break;
		case AUDIO_ENERGIZER: AudioBank = audio_energizer_psg_bank; psg = audio_energizer_psg; break;
		case AUDIO_AFTER_GHOST_CHOMPED: AudioBank = audio_after_ghost_chomped_psg_bank; psg = audio_after_ghost_chomped_psg; break;
		case AUDIO_EXTRA_LIFE: AudioBank = audio_extra_life_psg_bank; psg = audio_extra_life_psg; break;
		case AUDIO_THEY_MEET: AudioBank = audio_they_meet_psg_bank; psg = audio_they_meet_psg; break;
		case AUDIO_THE_CHASE: AudioBank = audio_the_chase_psg_bank; psg = audio_the_chase_psg; break;
		case AUDIO_JUNIOR: AudioBank = audio_junior_psg_bank; psg = audio_junior_psg; break;
	}
	// Stop any existing audio
	PSGStop();
	// Play desired audio
	if (repeat == 1) {
		PSGPlay(psg);
	} else {
		PSGPlayNoRepeat(psg);
	}
}

// Plays the given sfx
void PlaySFX(unsigned char sfx, unsigned char channel) {
	const unsigned char *psg = 0;
	switch (sfx) {
		case SFX_CONFIRM: SfxBank = sfx_confirm_psg_bank; psg = sfx_confirm_psg; break;
		case SFX_PELLET: SfxBank = sfx_pellet_psg_bank; psg = sfx_pellet_psg; break;
		case SFX_GHOST_CHOMPED: SfxBank = sfx_ghost_chomped_psg_bank; psg = sfx_ghost_chomped_psg; break;
		case SFX_BONUS_BOUNCE: SfxBank = sfx_bonus_bounce_psg_bank; psg = sfx_bonus_bounce_psg; break;
		case SFX_BONUS_CHOMPED: SfxBank = sfx_bonus_chomped_psg_bank; psg = sfx_bonus_chomped_psg; break;
	}
	// Prioritize all SFX over pellet
	if (PSGSFXGetStatus() == PSG_PLAYING && Sfx != SFX_PELLET && sfx == SFX_PELLET) {
		return;
	}
	// Set current SFX
	Sfx = sfx;
	PSGSFXPlay(psg, channel);
}

// Plays banked audio
void PlayAudio(void) {
	// Play any SFX
	SMS_mapROMBank(SfxBank);
	PSGSFXFrame();
	// Play BGM audio
	SMS_mapROMBank(AudioBank);
	PSGFrame();
	// Resume previous track after extra life plays
	if (Track == AUDIO_EXTRA_LIFE && PSGGetStatus() == PSG_STOPPED && SubState < 6) {
		Track = PrevTrack;
		PlayTrack(Track, 1);
	}
}