#include "player.h"
#include "animation.h"
#include "vector.h"

Player init_player() {
  Player p = {0};
  p.hp = MAX_PLAYER_HP;
  p.state = PLAYER_IDLE;
  p.pos = (Vector2){.x = 600, .y = 600};
  p.vel = (Vector2){.x = 0, .y = 0};

  // Inicializando as animações
  set_player_animation(
      &p, PLAYER_IDLE,
      new_animation(8, true, 0.15F, (Vector2){.x = 32, .y = 32}));
  set_player_animation(
      &p, PLAYER_MOVING_UP,
      new_animation(8, true, 0.15F, (Vector2){.x = 32, .y = 32}));
  set_player_animation(
      &p, PLAYER_MOVING_RIGHT,
      new_animation(8, true, 0.15F, (Vector2){.x = 32, .y = 32}));
  set_player_animation(
      &p, PLAYER_MOVING_DOWN,
      new_animation(8, true, 0.15F, (Vector2){.x = 32, .y = 32}));
  set_player_animation(
      &p, PLAYER_MOVING_LEFT,
      new_animation(8, true, 0.15F, (Vector2){.x = 32, .y = 32}));

  return p;
}
void set_player_animation(Player *player, PlayerState state, Animation anim) {
  player->animations[state] = anim;
}
<<<<<<< Updated upstream
void update_player(Player *player) {
  // !TODO: implementar
=======
void update_player(Player *player, float dt) {
  move_player(player, dt);
>>>>>>> Stashed changes
}
void move_player(Player *player, float dt){
    Vector2 move = {.x = 0, .y = 0};
    if (IsKeyDown(KEY_W)) {move.y -= 1;}
    if (IsKeyDown(KEY_A)) {move.x -= 1;}
    if (IsKeyDown(KEY_S)) {move.y += 1;}
    if (IsKeyDown(KEY_D)) {move.x += 1;}
    move = normalize_vec(move);
    move.x *= 500 *dt;
    move.y *= 500 *dt;
    player->pos = sum_vec(player->pos, move);
    player->vel = move;
}