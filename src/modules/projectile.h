#ifndef PROJECTILE_H
#define PROJECTILE_H



#include "../../include/raylib.h"
#include "animation.h"
#include "player.h"

// Entenda "usint" como "unsigned short int" a partir de agora
typedef unsigned short int usint;

// Tipos de projétil
typedef enum {
  PLAYER_ATK,
  ICE_ATK,
  ASTRONAUT_ATK,
  BILLIONAIRE_ATK,
  BLACK_HOLE,
  PROJECTILE_NUM_TYPES // Variante de contagem
} ProjectileType;

// Estados nos quais o projétil pode estar
typedef enum {
  PROJECTILE_FORMING,   // Sendo criado
  PROJECTILE_IDLE,      // Se movendo
  PROJECTILE_BREAKING,  // Quebrando no fim de sua vida
  PROJECTILE_NUM_STATES // Variante de contagem
} ProjectileState;

// Tipo que representará nossos projéteis
typedef struct projectile {
  ProjectileType type;   // Tipo específico de projétil
  int id;                // Seu ID na lista de projéteis do universo
  ProjectileState state; // Estado atual (animação que está rodando)
  Vector2 pos;           // Posição no mundo
  Vector2 direction;     // Direção de movimento
  float speed;           // Velocidade de movimento
  Vector2 vel;           // Vetor de velocidade
  float timer;           // Tempo desde que foi atirado
  float duration;        // Carga atual da ult
  usint damage;          // Dano causado em impacto
  float weight;          // Peso, influencia como é afetado pelos buracos negros
  Animation animations[PROJECTILE_NUM_STATES]; // Animações para cada estado
} Projectile;

// Funções relacionadas aos inimigos
void new_projectile(ProjectileType type, Vector2 pos, Vector2 direction); // Cria um projétil
void set_projectile_animation(Projectile *projectile, ProjectileState state,
                              Animation anim); // Define uma animação
void update_projectile(Projectile *projectile, Vector2 inicial_position, Vector2 final_position,
                       float dt); // Função de update do projétil
void sai_projectile(Projectile *projectile, Vector2 inicial_position, Vector2 mira_position, float dt);
void move_projectile(Projectile *projectile, float dt); // Move o projétil de acordo com sua direção e velocidade 
void draw_projectiles();
void draw_projectile(Projectile projectile);
void set_projectile_direction(Projectile *projectile, Vector2 direction);
void new_black_hole(Vector2 pos, Vector2 direction);
void update_projectiles( float dt);
#endif
