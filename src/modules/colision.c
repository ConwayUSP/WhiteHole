#include "colision.h"
#include "universe.h"
#include "vector.h"

void solve_enemy_colision(Enemy *enemy) {
  for (int i = 0; i < MAX_PROJECTILES; i++) {
    if (!is_slot_empty(&universe.projectile_slots, i)) {
      Projectile p = universe.projectiles[i];
      bool colided =
          CheckCollisionCircles(enemy->pos, enemy->size, p.pos, p.size);
      if (colided && (p.type == BLACK_HOLE || p.type == PLAYER_ATK)) {
        enemy_take_damage(enemy, p.damage);
        if (p.type != BLACK_HOLE) {
          free_projectile_slot(p.id);
        }
      }
    }
  }
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!is_slot_empty(&universe.enemy_slots, i)) {
      Enemy e = universe.enemies[i];
      bool colided =
          CheckCollisionCircles(enemy->pos, enemy->size, e.pos, e.size);
      if (colided) {
        Vector2 correction = direction_vec(e.pos, enemy->pos);
        correction = mult_vec(correction, e.size + enemy->size + 1);
        enemy->pos = sum_vec(e.pos, correction);
      }
    }
  }
}

void solve_player_colision(Player *player) {
  for (int i = 0; i < MAX_PROJECTILES; i++) {
    if (!is_slot_empty(&universe.projectile_slots, i)) {
      Projectile p = universe.projectiles[i];
      bool colided =
          CheckCollisionCircles(player->pos, player->size, p.pos, p.size);
      if (colided) {
        player_take_damage(player, p.damage);
        if (p.type != BLACK_HOLE && p.type != PLAYER_ATK) {
          free_projectile_slot(p.id);
        }
      }
    }
  }
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!is_slot_empty(&universe.enemy_slots, i)) {
      Enemy e = universe.enemies[i];
      bool colided =
          CheckCollisionCircles(player->pos, player->size, e.pos, e.size);
      if (colided) {
        Vector2 correction = direction_vec(e.pos, player->pos);
        correction = mult_vec(correction, e.size + player->size + 1);
        player->pos = sum_vec(e.pos, correction);
      }
    }
  }
    
}
