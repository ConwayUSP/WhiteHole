#include "projectile.h"
#include "animation.h"
#include "assetstore.h"
#include "entity.h"
#include "listcontrol.h"
#include "stdlib.h"
#include "universe.h"
#include "vector.h"
#include <stdio.h>

int new_projectile(ProjectileType type, Vector2 pos, Vector2 direction) {
  Projectile p = {0};
  p.entity_type = PROJECTILE;
  p.type = type;
  p.pos = pos;
  p.direction = direction;
  p.id = get_valid_projectile_id();
  p.size = 2.0f;
  if (p.id == NULL_SLOT) {
    return NULL_SLOT;
  }
  p.state = PROJECTILE_IDLE;

  switch (type) {
  case PLAYER_ATK:
    set_projectile_animation(&p, PROJECTILE_IDLE,
                             new_animation(1, true, 0, 1, (Vector2){8, 8}));
    p.damage = 5;
    p.speed = 400.0f;
    p.duration = 2.0f;
    p.weight = 1.0f;
    break;
  case ASTRONAUT_ATK:
    set_projectile_animation(&p, PROJECTILE_IDLE,
                             new_animation(1, true, 0, 1, (Vector2){8, 8}));
    p.damage = 1;
    p.speed = 200.0f;
    p.duration = 3.0f;
    p.weight = 2.0f;
    break;
  case ICE_ATK:
    set_projectile_animation(&p, PROJECTILE_IDLE,
                             new_animation(1, true, 0, 1, (Vector2){8, 8}));
    p.damage = 1;
    p.speed = 120.0f;
    p.duration = 2.0f;
    p.weight = 0.5f;
    break;
  case BILLIONAIRE_ATK:
    set_projectile_animation(&p, PROJECTILE_IDLE,
                             new_animation(1, true, 0, 1, (Vector2){8, 8}));
    p.damage = 1;
    p.speed = 150.0f;
    p.duration = 3.0f;
    p.weight = 2.0f;
    break;
  case BLACK_HOLE:
    set_projectile_animation(
        &p, PROJECTILE_IDLE,
        new_animation(16, true, 0, 0.05, (Vector2){32, 32}));
    p.damage = 1000;
    p.speed = 100.0f;
    p.duration = 10.0f;
    p.weight = 1000000.0f;
    p.size = 5.0f;
    break;

  default:
    exit(1); // Tipo de projétil não reconhecido
  }

  insert_projectile(p);
  return p.id;
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
  update_animation(&projectile->animations[projectile->state], dt);
  projectile->timer += dt;
  if (projectile->timer > projectile->duration) {
    free_projectile_slot(projectile->id);
  }
}

void set_projectile_direction(Projectile *projectile, Vector2 direction) {
  projectile->direction = direction;
}

void move_projectile(Projectile *projectile, float dt) {
  Vector2 movement = {.x = projectile->direction.x * projectile->speed * dt,
                      .y = projectile->direction.y * projectile->speed * dt};
  projectile->pos = sum_vec(projectile->pos, movement);

  if (projectile->type == BLACK_HOLE) {
    float slow_amount = 300 * dt;
    projectile->speed = projectile->speed - slow_amount < 0
                            ? 0
                            : projectile->speed - slow_amount;
  }
}

void draw_projectiles() {
  for (int i = 0; i < MAX_PROJECTILES; i++) {
    if (!is_slot_empty(&universe.projectile_slots, i)) {
      draw_projectile(universe.projectiles[i]);
    }
  }
}

void draw_projectile(Projectile projectile) {
  Animation anim = projectile.animations[projectile.state];
  Texture2D sheet =
      get_projectile_sheet(&universe.asset_store, projectile.type);
  Vector2 offset = get_projectile_offset(&universe.asset_store, projectile.type,
                                         projectile.state);
  draw_frame(anim, sheet, offset, projectile.pos, projectile.entity_type);
}
