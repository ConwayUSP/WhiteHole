#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include "../../include/raylib.h"
#include "enemy.h"
#include "player.h"
#include "projectile.h"

// Entenda "usint" como "unsigned short int" a partir de agora
typedef unsigned short int usint;

// Um gerenciador de sprites, é bom para reduzir cache misses e pa
typedef struct assetstore {
  Texture2D player_sheets[PLAYER_NUM_STATES];
  Texture2D enemy_sheets[ENEMY_NUM_TYPES][ENEMY_NUM_STATES];
  Texture2D projectile_sheets[PROJECTILE_NUM_TYPES][PROJECTILE_NUM_STATES];
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
