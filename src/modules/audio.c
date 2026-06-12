#include "audio.h"
#include "universe.h"
#include <math.h>

void change_music(Music next_music){
	StopMusicStream(universe.scene_music);
    universe.scene_music = next_music;
    if(IsMusicValid(next_music)) {
        PlayMusicStream(next_music);
    }
}

void distort_sound_time(ShotType shot_type){
    Sound sound = get_shot_audio(&universe.asset_store, shot_type);
    if (shot_type == SHOT_BLACKHOLE){
        SetSoundPitch(sound, fmin(1, sqrt(distort_time()) + 0.5));
    } else {
        SetSoundPitch(sound, fmin(1, sqrt(distort_time()) + 0.2));
    }
    
    PlaySound(sound);
}

void distort_music_time(Music music){
    SetMusicPitch(music, fmin(1, sqrt(distort_time()) + 0.2));
}