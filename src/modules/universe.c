#include "universe.h"
#include "assetstore.h"
#include "listcontrol.h"
#include "player.h"
#include "projectile.h"
#include "vector.h"
#include <stdio.h>

Universe init_universe() {
  Universe u = {0};

  u.context = MENU;
  u.player = init_player();
  u.asset_store = init_asset_store();
  u.projectile_slots = new_list_control(MAX_PROJECTILES);
  u.enemy_slots = new_list_control(MAX_ENEMIES);
  set_all_empty(&(u.projectile_slots));
  set_all_empty(&(u.enemy_slots));

  return u;
}

void update_universe(float dt) {
  universe_handle_input();
  if (universe.context == PAUSE) {
    return;
  }

  update_player(&(universe.player), dt);
  if (universe.context == RUNNING) {
    update_enemies(dt);
  }
  update_projectiles(dt);
  if (universe.player.hp == 0) {
    universe.context = MENU;
    universe.player.hp = MAX_PLAYER_HP;
    set_all_empty(&universe.projectile_slots);
    set_all_empty(&universe.enemy_slots);
  }
}

void universe_handle_input() {
  if (universe.context == MENU && IsKeyPressed(KEY_SPACE)) {
    universe.context = RUNNING;
    return;
  }
  if (IsKeyPressed(KEY_SPACE) && universe.context == RUNNING) {
    universe.context = PAUSE;
  } else if (IsKeyPressed(KEY_SPACE) && universe.context == PAUSE) {
    universe.context = RUNNING;
  }
}

int get_valid_projectile_id() {
  return get_empty_slot(&(universe.projectile_slots));
}

int get_valid_enemy_id() { return get_empty_slot(&(universe.enemy_slots)); }

void free_projectile_slot(int id) {
  set_slot_as_empty(&(universe.projectile_slots), id);
}

void free_enemy_slot(int id) { set_slot_as_empty(&(universe.enemy_slots), id); }

void insert_projectile(Projectile projectile) {
  universe.projectiles[projectile.id] = projectile;
}

void insert_enemy(Enemy enemy) { universe.enemies[enemy.id] = enemy; }

bool is_slot_empty(ListControl *control, int id) {
  return !control->used_slots[id];
}

float distort_time() {
  const float EFFECT_RADIUS = 70;
  float min_dist = 1000.0f;
  for (int i = 0; i < MAX_PROJECTILES; i++) {
    if (!is_slot_empty(&universe.projectile_slots, i)) {
      Projectile p = universe.projectiles[i];
      if (p.type == BLACK_HOLE &&
          distance_vec(universe.player.pos, p.pos) < min_dist) {
        min_dist = distance_vec(universe.player.pos, p.pos);
      }
    }
  }
  if (min_dist > EFFECT_RADIUS) {
    return 1.0f;
  }
  float res = min_dist / EFFECT_RADIUS;
  return res < 0.25 ? 0.25 : res;
}

void draw_universe() {
  Rectangle source_rec = {0.0f, 0.0f, 256.0f, 256.0f};
  Rectangle dest_rec = {0.0f, 0.0f, 375.0f, 375.0f};
  Vector2 origin = {0.0f, 0.0f};
  DrawTexturePro(universe.asset_store.floor_sprite, source_rec, dest_rec,
                 origin, 0.0f, WHITE);
  draw_player(&universe.player);
  draw_projectiles();
  draw_enemies();
}
