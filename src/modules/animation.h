#ifndef ANIMATION_H
#define ANIMATION_H

#include "../../include/raylib.h"
#include <stdbool.h>

// Entenda "usint" como "unsigned short int" a partir de agora
typedef unsigned short int usint;

// Tipo que representa o estado de uma animação
typedef struct anim {
  usint frame;        // Frame atual da animação
  usint num_frames;   // Quantos frames tem a animação
  usint loop_frame;   // Para qual frame a animação loopa ao chegar no final
  bool loop;          // Se a animação loopa ou não
  double timer;       // Tempo decorrido desde a última troca de frames
  double frame_dur;   // Duração de um frame da animação
  Vector2 frame_size; // Altura e largura de cada frame
} Animation;

// Funções relacionadas a animações
Animation new_animation(usint num_frames, bool loop, usint loop_frame,
                        double frame_dur, Vector2 frame_size);
void reset_animation(Animation *anim);
void update_animation(Animation *anim, float dt);

#endif
