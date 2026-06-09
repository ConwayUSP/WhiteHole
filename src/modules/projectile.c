#include "projectile.h"
#include "stdlib.h"
#include "vector.h"

Projectile new_projectile(ProjectileType type, int id) {
  Projectile p = {0};
  p.id = id;
  p.state = PROJECTILE_FORMING;

  switch (type) {
  case PLAYER_ATK:
    p.damage = 5;
    p.speed = 100.0f;
    p.duration = 2.0f;
    p.weight = 1.0f;
  case ASTRONAUT_ATK:
    p.damage = 1;
    p.speed = 80.0f;
    p.duration = 3.0f;
    p.weight = 2.0f;
  case ICE_ATK:
    p.damage = 1;
    p.speed = 120.0f;
    p.duration = 1.0f;
    p.weight = 0.5f;
  case BILLIONAIRE_ATK:
    p.damage = 1;
    p.speed = 8.0f;
    p.duration = 3.0f;
    p.weight = 2.0f;
  case BLACK_HOLE:
    p.damage = 1000;
    p.speed = 100.0f;
    p.duration = 60.0f;
    p.weight = 1000000.0f;
  default:
    exit(1); // Tipo de projétil não reconhecido
  }

  return p;
}

void set_projectile_animation(Projectile *projectile, ProjectileState state,
                              Animation anim) {
  projectile->animations[state] = anim;
}
void update_projectile(Projectile *projectile, Vector2 inicial_position, Vector2 final_position, float dt) {
  sai_projectile(projectile, inicial_position, final_position, dt);
}
void sai_projectile(Projectile *projectile, Vector2 inicial_position, Vector2 mira_position, float dt) {
  Vector2 sai = inicial_position;
  Vector2 dir = direction_vec(mira_position, inicial_position);
  projectile->pos = sai;
  projectile->direction = dir;
  projectile->vel = (Vector2){100.0f, 100.0f};
  dir.x *= projectile->vel.x * dt;
  dir.y *= projectile->vel.y * dt;
  projectile->pos = sum_vec(sai, dir);
  
}
