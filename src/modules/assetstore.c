#include "assetstore.h"
#include "../../include/raylib.h"
#include "audio.h"
#include "enemy.h"
#include "player.h"
#include "projectile.h"
#include "universe.h"

AssetStore init_asset_store() {
  AssetStore as = {0};

  //----------------------------------------------------------------------------------
  //  SPRITESHEETS
  //----------------------------------------------------------------------------------
  // Chão
  as.floor_sprite = LoadTexture("assets/floor/marte.png");

  // Cursor
  as.cursor_sprite = LoadTexture("assets/cursor/cursor.png");

  // Player
  as.player_atlas = LoadTexture("assets/player/player_atlas.png");
  as.player_offsets[PLAYER_IDLE] = (Vector2){0, 0};
  as.player_offsets[PLAYER_MOVING_DOWN] = (Vector2){96, 0};
  as.player_offsets[PLAYER_MOVING_UP] = (Vector2){0, 96};
  as.player_offsets[PLAYER_MOVING_LEFT] = (Vector2){0, 192};
  as.player_offsets[PLAYER_MOVING_RIGHT] = (Vector2){0, 288};

  // ICE
  as.enemy_atlas[ICE] = LoadTexture("assets/ice/ice_atlas.png");
  as.enemy_offsets[ICE][ENEMY_IDLE] = (Vector2){0, 192};
  as.enemy_offsets[ICE][ENEMY_MOVING_UP] = (Vector2){96, 0};
  as.enemy_offsets[ICE][ENEMY_MOVING_DOWN] = (Vector2){96, 96};
  as.enemy_offsets[ICE][ENEMY_MOVING_LEFT] = (Vector2){0, 96};
  as.enemy_offsets[ICE][ENEMY_MOVING_RIGHT] = (Vector2){0, 0};
  // Bilionário
  as.enemy_atlas[BILLIONAIRE] =
      LoadTexture("assets/billionaire/billionaire_atlas.png");
  as.enemy_offsets[BILLIONAIRE][ENEMY_IDLE] = (Vector2){96, 0};
  as.enemy_offsets[BILLIONAIRE][ENEMY_MOVING_UP] = (Vector2){0, 288};
  as.enemy_offsets[BILLIONAIRE][ENEMY_MOVING_DOWN] = (Vector2){0, 0};
  as.enemy_offsets[BILLIONAIRE][ENEMY_MOVING_LEFT] = (Vector2){0, 192};
  as.enemy_offsets[BILLIONAIRE][ENEMY_MOVING_RIGHT] = (Vector2){0, 96};
  // Astronauta
  as.enemy_atlas[ASTRONAUT] =
      LoadTexture("assets/astronaut/astronaut_atlas.png");
  as.enemy_offsets[ASTRONAUT][ENEMY_IDLE] = (Vector2){0, 0};
  as.enemy_offsets[ASTRONAUT][ENEMY_MOVING_UP] = (Vector2){0, 96};
  as.enemy_offsets[ASTRONAUT][ENEMY_MOVING_DOWN] = (Vector2){0, 192};
  as.enemy_offsets[ASTRONAUT][ENEMY_MOVING_LEFT] = (Vector2){0, 288};
  as.enemy_offsets[ASTRONAUT][ENEMY_MOVING_RIGHT] = (Vector2){96, 0};

  // PROJÉTEIS
  as.blackhole_atlas = LoadTexture("assets/projectiles/blackhole_atlas.png");
  as.blackhole_offsets[PROJECTILE_IDLE] = (Vector2){0, 0};

  as.enemy_projectile_atlas =
      LoadTexture("assets/projectiles/enemy_shot_atlas.png");
  as.enemy_projectile_offsets[PROJECTILE_IDLE] = (Vector2){0, 0};

  as.player_projectile_atlas =
      LoadTexture("assets/projectiles/player_shot_atlas.png");
  as.player_projectile_offsets[PROJECTILE_IDLE] = (Vector2){0, 0};

  //----------------------------------------------------------------------------------
  //  SOUND EFFECTS (SFX)
  //----------------------------------------------------------------------------------
  // Cenas
  // TODO: talvez implementar MENU
  as.scene_audio[GAME_OVER] =
      LoadMusicStream("assets/audio/scene/game_over.mp3"); // Gameover
  as.scene_audio[GAME_OVER].looping = false;
  as.scene_audio[RUNNING] =
      LoadMusicStream("assets/audio/scene/running.mp3"); // Running
  as.scene_audio[VICTORY] =
      LoadMusicStream("assets/audio/scene/victory.mp3"); // Victory
  as.scene_audio[VICTORY].looping = false;

  // Tiros (+1)
  as.shot_audio[SHOT_ICE] = LoadSound("assets/audio/shot/ice.mp3"); // Tiros ICE
  as.shot_audio[SHOT_ASTRONAUT] =
      LoadSound("assets/audio/shot/astronaut.mp3"); // Tiros ASTRONAUT
  as.shot_audio[SHOT_BILLIONAIRE] =
      LoadSound("assets/audio/shot/billionaire.mp3"); // Tiros BILLIONAIRE
  as.shot_audio[SHOT_PLAYER] =
      LoadSound("assets/audio/shot/player.mp3"); // Tiros PLAYER
  as.shot_audio[SHOT_BLACKHOLE] =
      LoadSound("assets/audio/shot/blackhole.mp3"); // Tiros BLACKHOLE
  as.shot_audio[WALK] =
      LoadSound("assets/audio/shot/walk.mp3"); // Alien andando

  return as;
}

// Getters para as spritesheets
Texture get_player_sheet(AssetStore *store) { return store->player_atlas; }

Texture get_enemy_sheet(AssetStore *store, EnemyType enemy_type) {
  return store->enemy_atlas[enemy_type];
}

Texture get_projectile_sheet(AssetStore *store,
                             ProjectileType projectile_type) {
  switch (projectile_type) {
  case BLACK_HOLE:
    return store->blackhole_atlas;
    break;
  case PLAYER_ATK:
    return store->player_projectile_atlas;
    break;
  default:
    return store->enemy_projectile_atlas;
  }
}

Vector2 get_player_offset(AssetStore *store, PlayerState state) {
  return store->player_offsets[state];
}
Vector2 get_enemy_offset(AssetStore *store, EnemyType enemy_type,
                         EnemyState state) {
  return store->enemy_offsets[enemy_type][state];
}
Vector2 get_projectile_offset(AssetStore *store, ProjectileType projectile_type,
                              ProjectileState state) {
  switch (projectile_type) {
  case BLACK_HOLE:
    return store->blackhole_offsets[state];
    break;
  case PLAYER_ATK:
    return store->player_projectile_offsets[state];
    break;
  default:
    return store->enemy_projectile_offsets[state];
  }
}

void unload_textures(AssetStore *store) {
  UnloadTexture(store->player_atlas);
  UnloadTexture(store->enemy_atlas[ICE]);
  UnloadTexture(store->enemy_atlas[BILLIONAIRE]);
  UnloadTexture(store->enemy_atlas[ASTRONAUT]);
  UnloadTexture(store->blackhole_atlas);
  UnloadTexture(store->player_projectile_atlas);
  UnloadTexture(store->enemy_projectile_atlas);
  UnloadTexture(store->floor_sprite);
  UnloadTexture(store->cursor_sprite);
}

// Getters para os áudios
Music get_scene_audio(AssetStore *store) {
  Music music = store->scene_audio[universe.context];
  SetMusicVolume(music, 0.3);
  return music;
}

Sound get_shot_audio(AssetStore *store, ShotType shot_type) {
  Sound sound = store->shot_audio[shot_type];
  if (shot_type != WALK) {
    SetSoundVolume(sound, 0.3);
  } else {
    SetSoundVolume(sound, 0.3);
  }
  return sound;
}
