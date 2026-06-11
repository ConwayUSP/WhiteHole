#include "player.h"
#include "animation.h"
#include "assetstore.h"
#include "colision.h"
#include "listcontrol.h"
#include "projectile.h"
#include "universe.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

Player init_player() {
  Player p = {0};
  p.entity_type = PLAYER;
  p.hp = MAX_PLAYER_HP;
  p.state = PLAYER_IDLE;
  p.pos = (Vector2){.x = 187.5, .y = 187.5};
  p.vel = (Vector2){.x = 0, .y = 0};
  p.speed = 120;
  p.size = 10;
  p.black_hole_threshold = 10;
  p.black_hole_charge = 10;

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
  player->atk_cooldown -= dt;
  read_mouse_inputs(player, dt);
  move_player(player, dt);
  update_player_state(player);
  update_animation(&player->animations[player->state], dt);
}

void update_player_state(Player *player) {
  if (is_null_vec(player->vel)) {
    player->state = PLAYER_IDLE;
    solve_player_colision(player);
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
  solve_player_colision(player);
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
  player->pos.x = player->pos.x < 0 ? 0 : player->pos.x;
  player->pos.x = player->pos.x > 375 ? 375 : player->pos.x;
  player->pos.y = player->pos.y < 0 ? 0 : player->pos.y;
  player->pos.y = player->pos.y > 375 ? 375 : player->pos.y;
  player->vel = move;
}

void read_mouse_inputs(Player *player, float dt) {
  float bhp = player->black_hole_pull;
  // Calcular a direção do tiro
  int mouse_x = GetMouseX();
  int mouse_y = GetMouseY();
  Vector2 mouse_pos = {.x = mouse_x, .y = mouse_y};
  Vector2 mouse_2d = GetScreenToWorld2D(mouse_pos, universe.cam);
  Vector2 direction = direction_vec(player->pos, mouse_2d);

  if (player->atk_cooldown < 0) {
    // Atirar
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      new_projectile(PLAYER_ATK, sum_vec(player->pos, mult_vec(direction, 10)),
                     direction);
    }
    player->atk_cooldown = ATK_COOLDOWN;
  }

  // Atirar Buracos Negros (ult)
  if (player->black_hole_charge >= player->black_hole_threshold) {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      bhp += dt;
      player->black_hole_pull = bhp > 2 ? 2 : bhp;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
      int bh_id = new_projectile(
          BLACK_HOLE,
          sum_vec(player->pos, sum_vec(mult_vec(direction, 20), player->vel)),
          direction);
      if (bh_id == NULL_SLOT) {
        return;
      }
      universe.projectiles[bh_id].speed = 100 + bhp * 175;
      player->black_hole_pull = 0;
      player->black_hole_charge -= player->black_hole_threshold;
    }
  }
}

void draw_player(Player *player) {
  Animation anim = player->animations[player->state];
  Texture2D spritesheet = get_player_sheet(&universe.asset_store);
  Vector2 offset = get_player_offset(&universe.asset_store, player->state);
  int spritesheet_columns = (spritesheet.width / anim.frame_size.x) / 2;
  int frameX = (anim.frame % spritesheet_columns) * anim.frame_size.x;
  int frameY =
      floor((float)anim.frame / spritesheet_columns) * anim.frame_size.y;
  frameX += offset.x;
  frameY += offset.y;
  Rectangle frame_rect = {frameX, frameY, anim.frame_size.x, anim.frame_size.y};
  Vector2 good_pos =
      sub_vec(player->pos, (Vector2){.x = anim.frame_size.x / 2,
                                     .y = anim.frame_size.y / 2});
  DrawTextureRec(spritesheet, frame_rect, good_pos, WHITE);
}

void player_take_damage(Player *player, int damage) {
  if (damage > player->hp) {
    player->hp = 0;
  } else {
    player->hp -= damage;
  }
}
