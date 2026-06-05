#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "../../include/raylib.h"
#include "assetstore.h"
#include "enemy.h"
#include "player.h"
#include "projectile.h"
#include "stack.h"

#define MAX_PROJECTILES 1024
#define MAX_ENEMIES 256

typedef enum { MENU, RUNNING, GAME_OVER, VICTORY } Scene;

// Estrutura do estado global do jogo
typedef struct universe {
  Scene context;          // Contexto atual do jogo
  AssetStore asset_store; // O asset store global
  Player player;
  Projectile projectiles[MAX_PROJECTILES]; // Lista de todos os projéteis
  Stack projectile_slots;     // Stack de posições livres na lista projectiles
  Enemy enemies[MAX_ENEMIES]; // Lista de todos os inimigos
  Stack enemy_slots;          // Stack de posições livres na lista enemies
} Universe;

// Construtor
Universe init_universe();
int get_valid_projectile_id(Universe *universe);
int get_valid_enemy_id(Universe *universe);

#endif
