#include "player.h"
#include "animation.h"

Player init_player() {
  Player p = {0};
  p.hp = MAX_PLAYER_HP;
  p.state = PLAYER_IDLE;
  p.pos = (Vector2){.x = 500, .y = 500};
  p.vel = (Vector2){.x = 0, .y = 0};

  // Inicializando as animações
  set_player_animation(
      &p, PLAYER_IDLE,
      new_animation(8, true, 0, 0.15F, (Vector2){.x = 32, .y = 32}));
  set_player_animation(
      &p, PLAYER_MOVING_UP,
      new_animation(8, true, 0, 0.15F, (Vector2){.x = 32, .y = 32}));
  set_player_animation(
      &p, PLAYER_MOVING_RIGHT,
      new_animation(8, true, 0, 0.15F, (Vector2){.x = 32, .y = 32}));
  set_player_animation(
      &p, PLAYER_MOVING_DOWN,
      new_animation(8, true, 0, 0.15F, (Vector2){.x = 32, .y = 32}));
  set_player_animation(
      &p, PLAYER_MOVING_LEFT,
      new_animation(8, true, 0, 0.15F, (Vector2){.x = 32, .y = 32}));

  return p;
}
void set_player_animation(Player *player, PlayerState state, Animation anim) {
  player->animations[state] = anim;
}
void update_player(Player *player) {
  // !TODO: implementar
}
