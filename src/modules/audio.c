#include "audio.h"
#include "universe.h"

void change_music(Music next_music){
	StopMusicStream(universe.scene_music);
    universe.scene_music = next_music;
    if(IsMusicValid(next_music)) {
        PlayMusicStream(next_music);
    }
}