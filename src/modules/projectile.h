
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../../include/raylib.h"
#include "animation.h"

#define MAX_ICE_HP 30
#define MAX_ASTRONAUT_HP 50
#define MAX_BILLIONAIRE_HP 80

// Entenda "usint" como "unsigned short int" a partir de agora
typedef unsigned short int usint;

// Tipos de projétil
typedef enum {
  PLAYER_ATK,
  ICE_ATK,
  ASTRONAUT_ATK,
  BILLIONAIRE_ATK,
  BLACK_HOLE
} ProjectileType;

// Estados nos quais o projétil pode estar
typedef enum {
  FORMING,   // Sendo criado
  IDLE,      // Se movendo
  BREAKING,  // Quebrando no fim de sua vida
  NUM_STATES // Variante de contagem
} ProjectileState;

// Tipo que representará nossos projéteis
typedef struct projectile {
  ProjectileType type;   // Tipo específico de projétil
  ProjectileState state; // Estado atual (animação que está rodando)
  Vector2 pos;           // Posição no mundo
  Vector2 direction;     // Direção de movimento
  float vel;             // Velocidade de movimento
  double timer;          // Tempo desde que foi atirado
  double duration;       // Carga atual da ult
  usint damange;         // Dano causado em impacto
  float weight;          // Peso, influencia como é afetado pelos buracos negros
  Texture2D spritesheets[NUM_STATES]; // Spritesheets para cada estado
  Animation animations[NUM_STATES];   // Animações para cada estado
} Projectile;

// Funções relacionadas aos inimigos
Projectile new_projectile(ProjectileType type); // Cria um projétil
void set_projectile_spritesheet(
    Projectile projectile, ProjectileState state,
    Texture2D spritesheet);                    // Define uma spritesheet
void update_projectile(Projectile projectile); // Função de update do projétil

#endif
