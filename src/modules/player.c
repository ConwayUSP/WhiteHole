#include "player.h"
#include "animation.h"
#include "assetstore.h"
#include "projectile.h"
#include "universe.h"
#include "vector.h"
#include <math.h>

Player init_player() {
  Player p = {0};
  p.hp = MAX_PLAYER_HP;
  p.state = PLAYER_IDLE;
  p.pos = (Vector2){.x = 800, .y = 800};
  p.vel = (Vector2){.x = 0, .y = 0};
  p.speed = 120;

  // Inicializando as animações
  set_player_animation(
      &p, PLAYER_IDLE,
      new_animation(8, true, 0, 0.25f, (Vector2){.x = 32, .y = 32}));
  set_player_animation(
      &p, PLAYER_MOVING_UP,
      new_animation(8, true, 0, 0.1f, (Vector2){.x = 32, .y = 32}));
  set_player_animation(
      &p, PLAYER_MOVING_RIGHT,
      new_animation(8, true, 0, 0.1f, (Vector2){.x = 32, .y = 32}));
  set_player_animation(
      &p, PLAYER_MOVING_DOWN,
      new_animation(8, true, 0, 0.1f, (Vector2){.x = 32, .y = 32}));
  set_player_animation(
      &p, PLAYER_MOVING_LEFT,
      new_animation(8, true, 0, 0.1f, (Vector2){.x = 32, .y = 32}));

  return p;
}
void set_player_animation(Player *player, PlayerState state, Animation anim) {
  player->animations[state] = anim;
}
void update_player(Player *player, float dt) {
  read_mouse_inputs(player, dt);
  move_player(player, dt);
  update_player_state(player);
  update_animation(&player->animations[player->state], dt);
}

void update_player_state(Player *player) {
  if (is_null_vec(player->vel)) {
    player->state = PLAYER_IDLE;
    return;
  }
  if (pow(player->vel.x, 2) > pow(player->vel.y, 2)) {
    if (player->vel.x > 0) {
      player->state = PLAYER_MOVING_RIGHT;
    } else {
      player->state = PLAYER_MOVING_LEFT;
    }
  } else {
    if (player->vel.y > 0) {
      player->state = PLAYER_MOVING_DOWN;
    } else {
      player->state = PLAYER_MOVING_UP;
    }
  }
}

void move_player(Player *player, float dt) {
  Vector2 move = {.x = 0, .y = 0};
  if (IsKeyDown(KEY_W)) {
    move.y -= 1;
  }
  if (IsKeyDown(KEY_A)) {
    move.x -= 1;
  }
  if (IsKeyDown(KEY_S)) {
    move.y += 1;
  }
  if (IsKeyDown(KEY_D)) {
    move.x += 1;
  }
  move = normalize_vec(move);
  move.x *= player->speed * dt;
  move.y *= player->speed * dt;
  player->pos = sum_vec(player->pos, move);
  player->vel = move;
}
void shoot_blackhole(Player *player) {
  int mouse_x = GetMouseX();
  int mouse_y = GetMouseY();
  Vector2 mouse_pos = {.x = mouse_x, .y = mouse_y};
  Vector2 mouse_2d = GetScreenToWorld2D(mouse_pos, universe.cam);
  Vector2 direction = direction_vec(player->pos, mouse_2d);
  new_black_hole(player->pos, direction);
}
void read_mouse_inputs(Player *player, float dt) {
  if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
    shoot_blackhole(player);
  }
  else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    int mouse_x = GetMouseX();
    int mouse_y = GetMouseY();
    Vector2 mouse = {mouse_x, mouse_y};
    Vector2 mouse_2d = GetScreenToWorld2D(mouse, universe.cam);
    Vector2 direction = direction_vec(player->pos, mouse_2d);
    new_player_projectile(player->pos, direction);
  }
}

void draw_player(Player *player) {
  Animation animation = player->animations[player->state];
  Texture2D spritesheet =
      get_player_sheet(&universe.asset_store, player->state);
  draw_frame(animation, spritesheet, player->pos);
}
