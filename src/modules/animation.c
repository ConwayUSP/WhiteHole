#include "animation.h"

Animation new_animation(usint num_frames, bool loop, usint loop_frame,
                        double frame_dur, Vector2 frame_size) {
  Animation a = {0};
  a.num_frames = num_frames;
  a.loop = loop;
  a.loop_frame = loop_frame;
  a.frame_dur = frame_dur;
  a.frame_size = frame_size;

  return a;
}
void reset_animation(Animation *anim) {
  anim->frame = 0;
  anim->timer = 0;
}

void update_animation(Animation *anim, float dt) {
  anim->timer += dt;
  if (anim->timer >= anim->frame_dur) {
    anim->frame += 1;               // Avança para o próximo frame
    anim->timer -= anim->frame_dur; // E reduz o timer para quanto tempo sobrou
                                    // da passagem de frame
    if (anim->frame >= anim->num_frames) {
      // Se é animação em loop, recomeça, se não fica no último frame
      if (anim->loop) {
        anim->frame = anim->frame_dur;
      } else {
        anim->frame = anim->num_frames - 1;
      }
    }
  }
}
