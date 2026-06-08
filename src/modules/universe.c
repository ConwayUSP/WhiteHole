#include "universe.h"
#include "assetstore.h"
#include "listcontrol.h"
#include "player.h"
#include "stack.h"

Universe init_universe() {
  Universe u = {0};

  u.context = MENU;
  u.player = init_player();
  u.asset_store = init_asset_store();
  u.projectile_slots = new_list_control(MAX_PROJECTILES);
  u.enemy_slots = new_list_control(MAX_ENEMIES);
  set_all_empty(&u.projectile_slots);
  set_all_empty(&u.enemy_slots);

  return u;
}

int get_valid_projectile_id(Universe *universe) {
  return get_empty_slot(&(universe->projectile_slots));
}

int get_valid_enemy_id(Universe *universe) {
  return get_empty_slot(&(universe->enemy_slots));
}

void free_projectile_slot(Universe *universe, int id) {
  set_slot_as_empty(&(universe->projectile_slots), id);
}

void free_enemy_slot(Universe *universe, int id) {
  set_slot_as_empty(&(universe->projectile_slots), id);
}
