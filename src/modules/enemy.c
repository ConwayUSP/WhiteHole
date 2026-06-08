#include <stdlib.h>
#include "enemy.h"
#include "universe.h"
#include "vector.h"

Enemy new_enemy(EnemyType type, int id) {
  Enemy e = {0};
  e.type = type;
  e.id = id;
  e.state = ENEMY_IDLE;
  // !TODO: Inicializar com posição aleatória de preferencia fora da tela e ir entrando
  e.pos = (Vector2){.x = 0,.y = 0};

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

  return e;
}

void set_enemy_animation(Enemy *enemy, EnemyState state, Animation anim) {
  enemy->animations[state] = anim;
}

/*
void move_ice(Enemy *enemy, float dt){

}

void move_astronaut(Enemy *enemy, float dt){
  
}
*/

void move_billionaire(Enemy *enemy, float dt){
  float cd = 5; // Cooldown do movimento a cada 5 segundos
  if(cd < 0 && cd >= -2){ // Anda por 2 segundos
    Vector2 dest = predict_vec(enemy->pos, universe.player.pos, mult_vec(universe.player.vel, 950*dt));
    enemy->vel = mult_vec(dest, 3);
    enemy->speed = 1200;
  } else if(cd < -2){ // Pós-dash, diminui MUITO a velocidade e reseta o cooldown
    enemy->speed = 50;
    cd = 5;
  }
  cd -= dt;
}
  // !TODO: Implementar (switch case para ver o tipo e chama a função de movimento do tipo)
  // renderizar como circulos, já que ainda não tem sprite
  // fazer o loop main spawnar a cada segundo um inimigo aleatório em posição aleatória para testar
  // renderizar cada um de uma cor diferente
  // renderizar o "player" e os "buracos negros" numa posição constante para testar o movimento

void update_enemy(Enemy *enemy, float dt) {
  switch(enemy->type) {
  case ICE:
    //move_ice(enemy, dt);
  case ASTRONAUT:
    //move_astronaut(enemy, dt);
  case BILLIONAIRE:
    move_billionaire(enemy, dt);
  default:
    exit(1); // Tipo de inimigo não detectado
  }
}
