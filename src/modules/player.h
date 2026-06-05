#ifndef PLAYER_H
#define PLAYER_H

#include "../../include/raylib.h"
#include "animation.h"

#define MAX_PLAYER_HP 3
#define BLACK_HOLE_COST 20

// Entenda "usint" como "unsigned short int" a partir de agora
typedef unsigned short int usint;

// Estados nos quais o Player pode estar
typedef enum {
  PLAYER_IDLE, // Parado
  PLAYER_MOVING_UP,
  PLAYER_MOVING_DOWN,
  PLAYER_MOVING_LEFT,
  PLAYER_MOVING_RIGHT,
  PLAYER_BLACK_HOLING, // Ult
  PLAYER_NUM_STATES    // Variante de contagem
} PlayerState;

// Tipo que representará nosso jogador
typedef struct player {
  usint hp;          // Vida restante ao player
  PlayerState state; // Estado atual (animação que está rodando)
  Vector2 pos;       // Posição no mundo
  Vector2 vel;       // Vetor de velocidade
  usint crazyness;   // Nível de loucura, quanto maior, mais forte ele fica
  usint black_hole_charge; // Número de recargas para o buraco negro (ult)
  double atk_cooldown;     // Quanto tempo desde o último tiro
  Animation animations[PLAYER_NUM_STATES]; // Animações para cada estado
} Player;

// Funções relacionadas ao Player
Player init_player(); // Cria um jogador
void set_player_animation(Player *player, PlayerState state,
                          Animation anim); // Define uma animação
void update_player(Player *player);        // Função de update do Player

#endif
