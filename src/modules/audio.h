#ifndef AUDIO_H
#define AUDIO_H

#include <raylib.h>

// Tipos de áudio
typedef enum {
  SCENE,
  SHOT,
  AUDIO_NUM_TYPES // Variante de contagem
} AudioType;

// Tipos de shot
typedef enum{
  SHOT_ICE,
  SHOT_ASTRONAUT,
  SHOT_BILLIONAIRE,
  SHOT_PLAYER,
  SHOT_BLACKHOLE,
  WALK,
  SHOT_NUM_TYPES // Variante de contagem
} ShotType;

void change_music(Music next_music);
void distort_sound_time(ShotType shot_type);
void distort_music_time(Music music);

#endif