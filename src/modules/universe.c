#include "universe.h"
#include "assetstore.h"
#include "listcontrol.h"
#include "player.h"

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
  update_player(&(universe.player), dt);
  update_enemies(dt);
  update_projectiles(dt);
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

void draw_universe() {
  Rectangle source_rec = {150.0f, 0.0f, 900.0f, 900.0f};
  Rectangle dest_rec = {0.0f, 0.0f, 400.0f, 400.0f};
  Vector2 origin = {0.0f, 0.0f};
  DrawTexturePro(universe.asset_store.floor_sprite, source_rec, dest_rec,
                 origin, 0.0f, WHITE);
  draw_player(&universe.player);
  draw_projectiles();
  draw_enemies();
}
