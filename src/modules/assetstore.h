#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include "../../include/raylib.h"
#include "audio.h"
#include "enemy.h"
#include "player.h"
#include "projectile.h"

// Entenda "usint" como "unsigned short int" a partir de agora
typedef unsigned short int usint;

// Um gerenciador de sprites, é bom para reduzir cache misses e pa
typedef struct assetstore {
  Texture player_atlas;
  Vector2 player_offsets[PLAYER_NUM_STATES];
  Texture enemy_atlas[ENEMY_NUM_TYPES];
  Vector2 enemy_offsets[ENEMY_NUM_TYPES][ENEMY_NUM_STATES];
  Texture player_projectile_atlas;
  Vector2 player_projectile_offsets[PROJECTILE_NUM_STATES];
  Texture blackhole_atlas;
  Vector2 blackhole_offsets[PROJECTILE_NUM_STATES];
  Texture enemy_projectile_atlas;
  Vector2 enemy_projectile_offsets[PROJECTILE_NUM_STATES];
  Texture floor_sprite;
  Texture cursor_sprite;

  Music scene_audio[5];
  Sound shot_audio[SHOT_NUM_TYPES];
} AssetStore;

// Construtor
AssetStore init_asset_store();
// Getters para as spritesheets
Texture get_player_sheet(AssetStore *store);
Texture get_enemy_sheet(AssetStore *store, EnemyType enemy_type);
Texture get_projectile_sheet(AssetStore *store, ProjectileType projectile_type);
// Getters para as os offsets
Vector2 get_player_offset(AssetStore *store, PlayerState state);
Vector2 get_enemy_offset(AssetStore *store, EnemyType enemy_type,
                         EnemyState state);
Vector2 get_projectile_offset(AssetStore *store, ProjectileType projectile_type,
                              ProjectileState state);
void unload_textures(AssetStore *store);

// Getters para os áudios
Music get_scene_audio(AssetStore *store);
Sound get_shot_audio(AssetStore *store, ShotType shot_type);

#endif
