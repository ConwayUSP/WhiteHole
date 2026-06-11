#include "enemy.h"
#include "assetstore.h"
#include "colision.h"
#include "player.h"
#include "projectile.h"
#include "universe.h"
#include "vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void new_enemy(EnemyType type, Vector2 pos) {
  Enemy e = {0};
  e.entity_type = ENEMY;
  e.type = type;
  e.id = get_valid_enemy_id();
  e.state = NOT_SPAWNED;
  e.spawn_timer = 2;
  e.pos = pos;
  e.size = 10;

  // Animações
  set_enemy_animation(
      &e, ENEMY_IDLE,
      new_animation(1, true, 0, 0.2f, (Vector2){.x = 32, .y = 32}));
  set_enemy_animation(
      &e, ENEMY_MOVING_DOWN,
      new_animation(1, true, 0, 0.2f, (Vector2){.x = 32, .y = 32}));
  set_enemy_animation(
      &e, ENEMY_MOVING_LEFT,
      new_animation(1, true, 0, 0.2f, (Vector2){.x = 32, .y = 32}));
  set_enemy_animation(
      &e, ENEMY_MOVING_UP,
      new_animation(1, true, 0, 0.2f, (Vector2){.x = 32, .y = 32}));
  set_enemy_animation(
      &e, ENEMY_MOVING_RIGHT,
      new_animation(1, true, 0, 0.2f, (Vector2){.x = 32, .y = 32}));

  // Atributos que variam de inimigo para inimigo
  switch (type) {
  case ICE:
    e.hp = MAX_ICE_HP;
    e.speed = 100;
    e.ult_threshold = ICE_ULT_CAP;
    e.atk_cooldown = 4.0f;
    set_enemy_animation(
        &e, ENEMY_IDLE,
        new_animation(1, true, 0, 0.2f, (Vector2){.x = 32, .y = 32}));
    set_enemy_animation(
        &e, ENEMY_MOVING_DOWN,
        new_animation(8, true, 0, 0.15f, (Vector2){.x = 32, .y = 32}));
    set_enemy_animation(
        &e, ENEMY_MOVING_LEFT,
        new_animation(8, true, 0, 0.15f, (Vector2){.x = 32, .y = 32}));
    set_enemy_animation(
        &e, ENEMY_MOVING_UP,
        new_animation(8, true, 0, 0.15f, (Vector2){.x = 32, .y = 32}));
    set_enemy_animation(
        &e, ENEMY_MOVING_RIGHT,
        new_animation(8, true, 0, 0.15f, (Vector2){.x = 32, .y = 32}));
    break;
  case ASTRONAUT:
    e.hp = MAX_ASTRONAUT_HP;
    e.speed = 100;
    e.ult_threshold = ASTRONAUT_ULT_CAP;
    e.atk_cooldown = 0.3f;
    set_enemy_animation(
        &e, ENEMY_IDLE,
        new_animation(8, true, 0, 0.2f, (Vector2){.x = 32, .y = 32}));
    set_enemy_animation(
        &e, ENEMY_MOVING_DOWN,
        new_animation(8, true, 0, 0.15f, (Vector2){.x = 32, .y = 32}));
    set_enemy_animation(
        &e, ENEMY_MOVING_LEFT,
        new_animation(8, true, 0, 0.15f, (Vector2){.x = 32, .y = 32}));
    set_enemy_animation(
        &e, ENEMY_MOVING_UP,
        new_animation(8, true, 0, 0.15f, (Vector2){.x = 32, .y = 32}));
    set_enemy_animation(
        &e, ENEMY_MOVING_RIGHT,
        new_animation(8, true, 0, 0.15f, (Vector2){.x = 32, .y = 32}));
    break;
  case BILLIONAIRE:
    e.hp = MAX_BILLIONAIRE_HP;
    e.ult_threshold = BILLIONAIRE_ULT_CAP;
    e.move_cooldown = 5.0f;
    e.atk_cooldown = 2.5f;
    set_enemy_animation(
        &e, ENEMY_IDLE,
        new_animation(8, true, 0, 0.2f, (Vector2){.x = 32, .y = 32}));
    set_enemy_animation(
        &e, ENEMY_MOVING_DOWN,
        new_animation(8, true, 0, 0.15f, (Vector2){.x = 32, .y = 32}));
    set_enemy_animation(
        &e, ENEMY_MOVING_LEFT,
        new_animation(8, true, 0, 0.15f, (Vector2){.x = 32, .y = 32}));
    set_enemy_animation(
        &e, ENEMY_MOVING_UP,
        new_animation(8, true, 0, 0.15f, (Vector2){.x = 32, .y = 32}));
    set_enemy_animation(
        &e, ENEMY_MOVING_RIGHT,
        new_animation(8, true, 0, 0.15f, (Vector2){.x = 32, .y = 32}));
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
      Enemy *e = &universe.enemies[i];
      update_enemy(e, dt);
    }
  }
}

void update_enemy(Enemy *enemy, float dt) {
  if (enemy->state == NOT_SPAWNED) {
    enemy->spawn_timer -= dt;
    if (enemy->spawn_timer <= 0) {
      enemy->state = ENEMY_IDLE;
    } else {
      return;
    }
  }
  switch (enemy->type) {
  case ICE:
    move_ice(enemy, dt);
    break;
  case ASTRONAUT:
    move_astronaut(enemy, dt);
    break;
  case BILLIONAIRE:
    move_billionaire(enemy, dt);
    break;
  default:
    exit(1); // Tipo de inimigo não detectado
  }
  update_enemy_state(enemy);

  solve_enemy_colision(enemy);
  update_animation(&enemy->animations[enemy->state], dt);
  if (enemy->hp <= 0) {
    free_enemy_slot(enemy->id);
  }

  enemy->atk_cooldown -= dt;
  if (enemy->atk_cooldown <= 0) {
    enemy_attack(enemy);
  }
}

void update_enemy_state(Enemy *enemy) {
  if (is_null_vec(enemy->vel)) {
    enemy->state = ENEMY_IDLE;
    return;
  }
  if (pow(enemy->vel.x, 2) > pow(enemy->vel.y, 2)) {
    if (enemy->vel.x > 0) {
      enemy->state = ENEMY_MOVING_RIGHT;
    } else {
      enemy->state = ENEMY_MOVING_LEFT;
    }
  } else {
    if (enemy->vel.y > 0) {
      enemy->state = ENEMY_MOVING_DOWN;
    } else {
      enemy->state = ENEMY_MOVING_UP;
    }
  }
}

void move_ice(Enemy *enemy, float dt) {
  const float MIN_DISTANCE = 100.0f;
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
  float dist =
      distance_vec(sum_vec(enemy->pos, enemy->vel), universe.player.pos);
  if (dist < MIN_DISTANCE) {
    enemy->vel = mult_vec(enemy->vel, fmax(0, (dist - 60)) / 40);
  }
  if (distance_vec(enemy->pos, enemy->target) < 0.5) {
    enemy->vel = (Vector2){0, 0};
  }
  enemy->pos = sum_vec(enemy->pos, enemy->vel);
}

void move_astronaut(Enemy *e, float dt) {
  const float MIN_DISTANCE = 120.0f;
  e->target = universe.player.pos;
  Vector2 bhtar = e->pos; // Posição do buraco negro mais próximo
  bool found_blackhole =
      true; // Verifica se esse é o primeiro buraco negro encontrado

  for (int i = 0; i < MAX_PROJECTILES; i++) {
    Projectile p = universe.projectiles[i];
    float orb = p.size + 30;
    if (!is_slot_empty(&universe.projectile_slots, i) &&
        distance_vec(sum_vec(e->pos, e->vel), p.pos) < orb &&
        p.type == BLACK_HOLE) {
      if (found_blackhole) {
        bhtar = p.pos;
        found_blackhole = false;
      } else if (distance_vec(e->pos, bhtar) > distance_vec(e->pos, p.pos)) {
        bhtar = p.pos;
      }
      Vector2 new_direction = direction_vec(bhtar, sum_vec(e->pos, e->vel));
      e->target = sum_vec(bhtar, mult_vec(new_direction, orb));
    }
  }
  e->vel = mult_vec(direction_vec(e->pos, e->target), e->speed * dt);
  float dist = distance_vec(sum_vec(e->pos, e->vel), e->target);
  if (dist < MIN_DISTANCE) {
    e->vel = mult_vec(e->vel, fmax(0, (dist - 80)) / 40);
  }
  e->pos = sum_vec(e->pos, e->vel);
}

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
  } else if (old_cooldown > -1 && cd < -1) {
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
  } else if (cd < 0 && cd >= -1) {
    enemy->target = sum_vec(enemy->pos, mult_vec(enemy->vel, 10));
  }

  enemy->vel =
      mult_vec(direction_vec(enemy->pos, enemy->target), enemy->speed * dt);
  if (distance_vec(enemy->pos, enemy->target) < 1) {
    enemy->vel = (Vector2){0, 0};
  }
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
  if (enemy.state == NOT_SPAWNED) {
    if (((int)(GetTime() * 2.5) % 2)) {
      DrawPolyLinesEx(enemy.pos, 3, 11, 30, 2.5f, (Color){255, 255, 255, 220});
      DrawText("!", enemy.pos.x - 0.02, enemy.pos.y - 5, 8,
               (Color){255, 255, 255, 220});
    }
    return;
  }
  Animation anim = enemy.animations[enemy.state];
  Texture2D spritesheet = get_enemy_sheet(&universe.asset_store, enemy.type);
  Vector2 offset =
      get_enemy_offset(&universe.asset_store, enemy.type, enemy.state);
  int spritesheet_columns = (spritesheet.width / anim.frame_size.x) / 2;
  int frameX = (anim.frame % spritesheet_columns) * anim.frame_size.x;
  int frameY =
      floor((float)anim.frame / spritesheet_columns) * anim.frame_size.y;
  frameX += offset.x;
  frameY += offset.y;
  Rectangle frame_rect = {frameX, frameY, anim.frame_size.x, anim.frame_size.y};
  Vector2 good_pos = sub_vec(enemy.pos, (Vector2){.x = anim.frame_size.x / 2,
                                                  .y = anim.frame_size.y / 2});
  DrawTextureRec(spritesheet, frame_rect, good_pos, WHITE);
}

void enemy_take_damage(Enemy *enemy, int damage) {

  if (damage > enemy->hp) {
    enemy->hp = 0;

  } else {
    enemy->hp -= damage;
  }
  if (enemy->hp == 0) {
    if (universe.player.black_hole_charge < 20) {
      universe.player.black_hole_charge += 1;
    }
    universe.kill_count++;
    universe.can_spawn_new_enemies = true;

    switch (enemy->type) {
    case ICE:
      universe.points += ICE_POINTS;
      break;
    case ASTRONAUT:
      universe.points += ASTRONAUT_POINTS;
      break;
    case BILLIONAIRE:
      universe.points += BILLIONAIRE_POINTS;
      break;
    default:
      break;
    }
  }
}

void enemy_attack(Enemy *enemy) {
  Vector2 main_direction = (Vector2){0, -1};
  float angle = 0.3;

  switch (enemy->type) {
  case ICE:
    main_direction = direction_vec(enemy->pos, universe.player.pos);
    for (int i = -1; i <= 1; i++) {
      new_projectile(ICE_ATK, enemy->pos,
                     rotate_vec(main_direction, i * angle));
    }
    enemy->atk_cooldown = 4.0f;
    break;

  case ASTRONAUT:
    new_projectile(ASTRONAUT_ATK, enemy->pos,
                   direction_vec(enemy->pos, universe.player.pos));
    enemy->atk_cooldown = 0.3f;
    break;

  case BILLIONAIRE:
    angle = 0.785375;
    for (int i = 0; i < 8; i++) {
      new_projectile(BILLIONAIRE_ATK, enemy->pos,
                     rotate_vec(main_direction, i * angle));
    }
    enemy->atk_cooldown = 6.0f;
    break;

  default:
    return;
  }
}
