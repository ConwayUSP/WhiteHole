#include "enemy.h"
#include <stdlib.h>

Enemy new_enemy(EnemyType type, int id) {
  Enemy e = {0};
  e.type = type;
  e.id = id;
  e.state = ENEMY_IDLE;

  // Atributos que variam de inimigo para inimigo
  switch (type) {
  case ICE:
    e.hp = MAX_ICE_HP;
    e.ult_threshold = ICE_ULT_CAP;
  case ASTRONAUT:
    e.hp = MAX_ASTRONAUT_HP;
    e.ult_threshold = ASTRONAUT_ULT_CAP;
  case BILLIONAIRE:
    e.hp = MAX_BILLIONAIRE_HP;
    e.ult_threshold = BILLIONAIRE_ULT_CAP;
  default:
    exit(1); // Tipo de inimigo não detectado
  }

  // !TODO: Inicializar com posição aleatória

  return e;
}

void set_enemy_animation(Enemy *enemy, EnemyState state, Animation anim) {
  enemy->animations[state] = anim;
}

void update_enemy(Enemy *enemy) {
  // !TODO: Implementar
}
