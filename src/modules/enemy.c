#include "enemy.h"
#include "player.h"
#include "universe.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include "colision.h"

void new_enemy(EnemyType type, Vector2 pos) {
  Enemy e = {0};
  e.type = type;
  e.id = get_valid_enemy_id();
  e.state = ENEMY_IDLE;
  e.pos = pos;
  e.size = 10;

  // Atributos que variam de inimigo para inimigo
  switch (type) {
  case ICE:
    e.hp = MAX_ICE_HP;
    e.speed = 100;
    e.ult_threshold = ICE_ULT_CAP;
    break;
  case ASTRONAUT:
    e.hp = MAX_ASTRONAUT_HP;
    e.ult_threshold = ASTRONAUT_ULT_CAP;
    break;
  case BILLIONAIRE:
    e.hp = MAX_BILLIONAIRE_HP;
    e.ult_threshold = BILLIONAIRE_ULT_CAP;
    e.move_cooldown = 5.0f;
    break;
  default:
    exit(1); // Tipo de inimigo não detectado
  }

  insert_enemy(e);
}

void set_enemy_animation(Enemy *enemy, EnemyState state, Animation anim) {
  enemy->animations[state] = anim;
}

void update_enemies(float dt) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!is_slot_empty(&(universe.enemy_slots), i)) {
      update_enemy(&universe.enemies[i], dt);
    }
  }
}

void update_enemy(Enemy *enemy, float dt) {
  switch (enemy->type) {
  case ICE:
    move_ice(enemy, dt);
    break;
  case ASTRONAUT:
    // move_astronaut(enemy, dt);
    break;
  case BILLIONAIRE:
    move_billionaire(enemy, dt);
    break;
  default:
    exit(1); // Tipo de inimigo não detectado
  }
  solve_enemy_colision(enemy);
  if (enemy->hp <= 0){
    free_enemy_slot(enemy->id);
  }
}

void move_ice(Enemy *enemy, float dt) {
  Vector2 itar = enemy->pos; // Posição do ICE mais próximo
  bool found_other_ice =
      true; // Verifica se esse é o primeiro ICE da lista de inimigos

  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!is_slot_empty(&universe.enemy_slots, i) &&
        enemy->id != universe.enemies[i].id &&
        universe.enemies[i].type == ICE) {
      if (found_other_ice) {
        itar = universe.enemies[i].pos;
        found_other_ice = false;
      } else {
        itar = distance_vec(enemy->pos, itar) >
                       distance_vec(enemy->pos, universe.enemies[i].pos)
                   ? universe.enemies[i].pos
                   : itar;
      }
    }
  }

  enemy->target = mult_vec(sum_vec(universe.player.pos, itar), 0.5);
  enemy->vel =
      mult_vec(direction_vec(enemy->pos, enemy->target), enemy->speed * dt);
  enemy->pos = sum_vec(enemy->pos, enemy->vel);
}

/*
void move_astronaut(Enemy *enemy, float dt){

}
*/

void move_billionaire(Enemy *enemy, float dt) {
  const float DASH_SPEED = 400;
  const float MIN_SPEED = 50;

  float old_cooldown = enemy->move_cooldown;
  enemy->move_cooldown -= dt;
  float cd = enemy->move_cooldown;

  if (old_cooldown > 0 && cd < 0) {
    enemy->target =
        sum_vec(universe.player.pos, mult_vec(universe.player.vel, 1000 * dt));
    enemy->speed = DASH_SPEED;
  } else if (old_cooldown > -2 && cd < -2) {
    enemy->target = (Vector2){.x = rand() % 400, .y = rand() % 400};
    enemy->speed = MIN_SPEED;
    enemy->move_cooldown = 5;
  }

  if (cd < 0.2 && cd > 0) {
    float charge = (0.2f - cd) * 5;
    enemy->target =
        sum_vec(universe.player.pos, mult_vec(universe.player.vel, 300 * dt));
    enemy->speed = (charge * charge) * (DASH_SPEED - MIN_SPEED) + MIN_SPEED;
  } else if (cd > 4.8 && cd < 5) {
    float charge = (cd - 4.8) * 5;
    enemy->speed = (charge * charge) * (DASH_SPEED - MIN_SPEED) + MIN_SPEED;
    enemy->target =
        sum_vec(universe.player.pos, mult_vec(universe.player.vel, 300 * dt));
  } else if (cd < 0 && cd >= -2) {
    enemy->target = sum_vec(enemy->pos, enemy->vel);
  }

  enemy->vel =
      mult_vec(direction_vec(enemy->pos, enemy->target), enemy->speed * dt);
  enemy->pos = sum_vec(enemy->pos, enemy->vel);
}

void draw_enemies() {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!is_slot_empty(&universe.enemy_slots, i)) {
      draw_enemy(universe.enemies[i]);
    }
  }
}

void draw_enemy(Enemy enemy) {
  switch (enemy.type) {
  case ICE:
    DrawCircle(enemy.pos.x, enemy.pos.y, 10.0f, WHITE);
    break;
  case ASTRONAUT:
    DrawCircle(enemy.pos.x, enemy.pos.y, 10.0f, PINK);
    break;
  case BILLIONAIRE:
    DrawCircle(enemy.pos.x, enemy.pos.y, 10.0f, PURPLE);
    break;
  default:
    exit(1); // Tipo de inimigo não detectado
  }
}

void enemy_take_damage(Enemy*enemy, int damage) {
  if (damage > enemy->hp) {
    enemy->hp = 0;
  }
  else {
    enemy->hp -= damage;
  }
}