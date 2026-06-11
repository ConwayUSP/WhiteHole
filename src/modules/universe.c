#include "universe.h"
#include "assetstore.h"
#include "enemy.h"
#include "audio.h"
#include "listcontrol.h"
#include "player.h"
#include "projectile.h"
#include "vector.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

Universe init_universe() {

  Universe u = {0};

  u.context = MENU;
  u.player = init_player();
  u.asset_store = init_asset_store();
  u.projectile_slots = new_list_control(MAX_PROJECTILES);
  u.enemy_slots = new_list_control(MAX_ENEMIES);
  u.points = 100;
  u.point_timer = 0.0f;
  u.can_spawn_new_enemies = true;
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
    spawn_enemies();
    universe.point_timer += dt;
    if (universe.point_timer >= 1.0f) {
      universe.point_timer -= 1.0f;
      universe.points -= 1.0f;
    }
    update_enemies(dt);
    victory();
  }
  update_projectiles(dt);
  if (universe.player.hp == 0) {
    universe.points = 100;
    universe.context = GAME_OVER;
    change_music(get_scene_audio(&(universe.asset_store)));
    universe.player.hp = MAX_PLAYER_HP;
    universe.player.black_hole_charge = 10;
    set_all_empty(&universe.projectile_slots);
    set_all_empty(&universe.enemy_slots);
  }

  // Música
  universe.scene_music = get_scene_audio(&(universe.asset_store));
  UpdateMusicStream(universe.scene_music);
}

void universe_handle_input() {
  if ((universe.context == MENU || universe.context == GAME_OVER ||
       universe.context == VICTORY) &&
      IsKeyPressed(KEY_SPACE)) {
    universe.context = RUNNING;
    change_music(get_scene_audio(&(universe.asset_store)));
    return;
  }
  if (IsKeyPressed(KEY_SPACE) && universe.context == RUNNING) {
    universe.context = PAUSE;
    change_music(get_scene_audio(&(universe.asset_store)));
  } else if (IsKeyPressed(KEY_SPACE) && universe.context == PAUSE) {
    universe.context = RUNNING;
    change_music(get_scene_audio(&(universe.asset_store)));
  }
}

void spawn_enemies() {
  if (!universe.can_spawn_new_enemies) {
    return;
  }

  Vector2 position = {rand() % 375, rand() % 375};
  if (distance_vec(position, universe.player.pos) < 50) {
    position = mult_vec(direction_vec(position, universe.player.pos), 50);
  }
  EnemyType type = rand() % ENEMY_NUM_TYPES;
  if (type == ICE) {
    new_enemy(type, sum_vec(position, (Vector2){0, -30}));
    new_enemy(type, sum_vec(position, (Vector2){20, 10}));
    new_enemy(type, sum_vec(position, (Vector2){-20, 10}));
  } else {
    new_enemy(type, position);
  }

  universe.can_spawn_new_enemies = false;
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
  Texture2D floor_tex = universe.asset_store.floor_sprite;
  DrawTexturePro(floor_tex, source_rec, dest_rec, origin, 0.0f, WHITE);
  draw_player(&universe.player);
  draw_projectiles();
  draw_enemies();
}
void victory(){
  if (universe.kill_count == 5){
    universe.context = VICTORY; 
    change_music(get_scene_audio(&(universe.asset_store)));
  }
}
