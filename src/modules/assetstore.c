#include "assetstore.h"
#include "../../include/raylib.h"
#include "enemy.h"
#include "player.h"
#include "projectile.h"

AssetStore init_asset_store() {
  AssetStore as = {0};

  // Chão
  as.floor_sprite = LoadTexture("assets/floor/marte.png");

  // Player
  as.player_sheets[PLAYER_IDLE] = LoadTexture("assets/player/alien_idle.png");
  as.player_sheets[PLAYER_MOVING_DOWN] =
      LoadTexture("assets/player/alien_walk_down.png");
  as.player_sheets[PLAYER_MOVING_RIGHT] =
      LoadTexture("assets/player/alien_walk_right.png");
  as.player_sheets[PLAYER_MOVING_UP] =
      LoadTexture("assets/player/alien_walk_up.png");
  as.player_sheets[PLAYER_MOVING_LEFT] =
      LoadTexture("assets/player/alien_walk_left.png");

  // ICE
  as.enemy_sheets[ICE][ENEMY_IDLE] = LoadTexture("assets/ice/idle.png");
  // Bilionário
  as.enemy_sheets[BILLIONAIRE][ENEMY_IDLE] =
      LoadTexture("assets/billionaire/idle.png");
  // Astronauta
  as.enemy_sheets[ASTRONAUT][ENEMY_IDLE] =
      LoadTexture("assets/astronaut/idle.png");

  // PROJÉTEIS
  as.projectile_sheets[BLACK_HOLE][PROJECTILE_IDLE] =
      LoadTexture("assets/projectiles/blackhole.png");
  as.projectile_sheets[PLAYER_ATK][PROJECTILE_IDLE] =
      LoadTexture("assets/projectiles/player_shot.png");
  as.projectile_sheets[BILLIONAIRE_ATK][PROJECTILE_IDLE] =
      LoadTexture("assets/projectiles/enemy_shot.png");
  as.projectile_sheets[ICE_ATK][PROJECTILE_IDLE] =
      LoadTexture("assets/projectiles/enemy_shot.png");
  as.projectile_sheets[ASTRONAUT_ATK][PROJECTILE_IDLE] =
      LoadTexture("assets/projectiles/enemy_shot.png");

  return as;
}

// Getters para as spritesheets
Texture2D get_player_sheet(AssetStore *store, PlayerState state) {
  return store->player_sheets[state];
}

Texture2D get_enemy_sheet(AssetStore *store, EnemyType enemy_type,
                          EnemyState state) {
  return store->enemy_sheets[enemy_type][state];
}

Texture2D get_projectile_sheet(AssetStore *store,
                               ProjectileType projectile_type,
                               ProjectileState state) {
  return store->projectile_sheets[projectile_type][state];
}
