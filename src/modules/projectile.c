#include "projectile.h"
#include "listcontrol.h"
#include "stdlib.h"
#include "universe.h"
#include "vector.h"
#include <stdio.h>

void new_projectile(ProjectileType type, Vector2 pos, Vector2 direction) {
  Projectile p = {0};
  p.type = type;
  p.pos = pos;
  p.direction = direction;
  p.id = get_valid_projectile_id();
  if (p.id == NULL_SLOT) {
    return;
  }
  p.state = PROJECTILE_FORMING;

  switch (type) {
  case PLAYER_ATK:
    p.damage = 5;
    p.speed = 400.0f;
    p.duration = 2.0f;
    p.weight = 1.0f;
    break;
  case ASTRONAUT_ATK:
    p.damage = 1;
    p.speed = 80.0f;
    p.duration = 3.0f;
    p.weight = 2.0f;
    break;
  case ICE_ATK:
    p.damage = 1;
    p.speed = 120.0f;
    p.duration = 1.0f;
    p.weight = 0.5f;
    break;
  case BILLIONAIRE_ATK:
    p.damage = 1;
    p.speed = 8.0f;
    p.duration = 3.0f;
    p.weight = 2.0f;
    break;
  case BLACK_HOLE:
    p.damage = 1000;
    p.speed = 100.0f;
    p.duration = 60.0f;
    p.weight = 1000000.0f;
    break;

  default:
    exit(1); // Tipo de projétil não reconhecido
  }

  insert_projectile(p);
}

void set_projectile_animation(Projectile *projectile, ProjectileState state,
                              Animation anim) {
  projectile->animations[state] = anim;
}

void update_projectiles(float dt) {
  for (int i = 0; i < MAX_PROJECTILES; i++) {
    if (!is_slot_empty(&universe.projectile_slots, i)) {
      update_projectile(&universe.projectiles[i], dt);
    }
  }
}

void update_projectile(Projectile *projectile, float dt) {
  move_projectile(projectile, dt);
  projectile->timer += dt;
}

void set_projectile_direction(Projectile *projectile, Vector2 direction) {
  projectile->direction = direction;
}

void move_projectile(Projectile *projectile, float dt) {
  Vector2 movement = {.x = projectile->direction.x * projectile->speed * dt,
                      .y = projectile->direction.y * projectile->speed * dt};
  projectile->pos = sum_vec(projectile->pos, movement);
}

void draw_projectiles() {
  for (int i = 0; i < MAX_PROJECTILES; i++) {
    if (!is_slot_empty(&universe.projectile_slots, i)) {
      draw_projectile(universe.projectiles[i]);
    }
  }
}

void draw_projectile(Projectile projectile) {
  switch (projectile.type) {
  case BLACK_HOLE:
    DrawCircle(projectile.pos.x, projectile.pos.y, 5.0f, BLACK);
    break;
  case PLAYER_ATK:
    DrawCircle(projectile.pos.x, projectile.pos.y, 2.0f, YELLOW);
    break;
  default:
    return;
  }
}
