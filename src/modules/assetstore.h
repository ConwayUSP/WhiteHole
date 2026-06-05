#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include "../../include/raylib.h"

// Infelizmente precisaremos manter essa contagem manual por enquanto
#define NUM_PLAYER_STATES 6
#define NUM_ENEMY_STATES 6
#define NUM_ENEMY_TYPES 3
#define NUM_PROJECTILE_STATES 3
#define NUM_PROJECTILE_TYPES 5

// Entenda "usint" como "unsigned short int" a partir de agora
typedef unsigned short int usint;

// Um gerenciador de sprites, é bom para reduzir cache misses e pa
typedef struct assetstore {
  Texture2D player_sheets[NUM_PLAYER_STATES];
  Texture2D enemy_sheets[NUM_ENEMY_TYPES][NUM_ENEMY_STATES];
  Texture2D projectile_sheets[NUM_PROJECTILE_TYPES][NUM_PROJECTILE_STATES];
} AssetStore;

// Construtor
AssetStore init_asset_store();
// Setters para as spritesheets
void set_player_sheet(int state, Texture2D sheet);
void set_enemy_sheet(int enemy_type, int state, Texture2D sheet);
void set_projectile_sheet(int projectile_type, int state, Texture2D sheet);
// Getters para as spritesheets
Texture2D get_player_sheet(int state);
Texture2D get_enemy_sheet(int enemy_type, int state);
Texture2D get_projectile_sheet(int projectile_type, int state);

#endif
