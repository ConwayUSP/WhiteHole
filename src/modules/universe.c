#include "universe.h"
#include "assetstore.h"
#include "player.h"
#include "stack.h"

Universe init_universe() {
  Universe u = {0};

  u.context = MENU;
  u.player = init_player();
  u.asset_store = init_asset_store();
  u.projectile_slots = new_stack(MAX_PROJECTILES);
  u.enemy_slots = new_stack(MAX_ENEMIES);
  fill_zero_to_max(&u.projectile_slots);
  fill_zero_to_max(&u.enemy_slots);

  return u;
}

int get_valid_projectile_id(Universe *universe) {
  return pop(&(universe->projectile_slots));
}

int get_valid_enemy_id(Universe *universe) {
  return pop(&(universe->enemy_slots));
}

void free_projectile_slot(Universe *universe, int id) {
  push(&(universe->projectile_slots), id);
}

void free_enemy_slot(Universe *universe, int id) {
  push(&(universe->projectile_slots), id);
}
