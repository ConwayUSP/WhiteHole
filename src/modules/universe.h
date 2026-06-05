#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "../../include/raylib.h"
#include "assetstore.h"
#include "enemy.h"
#include "player.h"
#include "projectile.h"

#define MAX_PROJECTILES 1024
#define MAX_ENEMIES 256

// Estrutura do estado global do jogo
typedef struct universe {
  AssetStore asset_store;
  Player player;
  Projectile projectiles[MAX_PROJECTILES];
  Enemy enemies[MAX_ENEMIES];
} Universe;

// Construtor
Universe init_universe();

#endif
