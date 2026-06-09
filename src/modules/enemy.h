#ifndef ENEMY_H
#define ENEMY_H

#include "../../include/raylib.h"
#include "animation.h"

// Vida máxima de cada tipo de inimigo
#define MAX_ICE_HP 30
#define MAX_ASTRONAUT_HP 50
#define MAX_BILLIONAIRE_HP 80
// Threshold de ult de cada inimigo
#define ICE_ULT_CAP 10.0
#define ASTRONAUT_ULT_CAP 15.0
#define BILLIONAIRE_ULT_CAP 20.0

// Entenda "usint" como "unsigned short int" a partir de agora
typedef unsigned short int usint;

// Tipos de inimigo
typedef enum {
  ICE,
  ASTRONAUT,
  BILLIONAIRE,
  ENEMY_NUM_TYPES // Variante de contagem
} EnemyType;

// Estados nos quais o inimigo pode estar
typedef enum {
  ENEMY_IDLE, // Parado
  ENEMY_MOVING_UP,
  ENEMY_MOVING_DOWN,
  ENEMY_MOVING_LEFT,
  ENEMY_MOVING_RIGHT,
  ENEMY_ULTING,
  ENEMY_NUM_STATES // Variante de contagem
} EnemyState;

// Tipo que representará nossos inimigos
typedef struct enemy {
  EnemyType type;      // Tipo específico de inimigo
  int id;              // Seu índice na lista de inimigos do universo
  usint hp;            // Vida restante ao inimigo
  EnemyState state;    // Estado atual (animação que está rodando)
  Vector2 pos;         // Posição no mundo
  Vector2 vel;         // Vetor de velocidade
  Vector2 target;      // Ponto para o qual o inimigo quer se mover
  float speed;         // Velocidade base de movimento
  float ult_charge;    // Carga atual da ult
  float ult_threshold; // Quanta carga precisa acumular para ultar
  float atk_cooldown;  // Quanto tempo desde o último tiro
  float move_cooldown; // Quanto tempo para o bilionário dar seu dash
  float size;
  Animation animations[ENEMY_NUM_STATES]; // Animações para cada estado
} Enemy;

// Funções relacionadas aos inimigos
void new_enemy(EnemyType type, Vector2 pos); // Cria um inimigo
void set_enemy_animation(Enemy *enemy, EnemyState state,
                         Animation anim); // Define uma animação
void update_enemies(float dt);
void update_enemy(Enemy *enemy, float dt); // Função de update do inimigo
void move_ice(Enemy *enemy,
              float dt); // Função de movimentação inimigos tipo ICE
void move_astronaut(Enemy *enemy,
                    float dt); // Função de movimentação inimigos tipo ASTRONAUT
void move_billionaire(
    Enemy *enemy, float dt); // Função de movimentação inimigos tipo BILLIONAIRE
void draw_enemies();
void draw_enemy(Enemy enemy);
void enemy_take_damage(Enemy *enemy, int damage);
void enemy_attack(Enemy *enemy);

#endif
