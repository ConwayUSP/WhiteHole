#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "../../include/raylib.h"
#include "assetstore.h"
#include "enemy.h"
#include "listcontrol.h"
#include "player.h"
#include "projectile.h"

#define MAX_PROJECTILES 1024
#define MAX_ENEMIES 128

typedef enum { MENU, RUNNING, PAUSE, GAME_OVER, VICTORY } Scene;

// Estrutura do estado global do jogo
typedef struct universe {
  Scene context;          // Contexto atual do jogo
  AssetStore asset_store; // O asset store global
  Player player;
  int points; // Com quantos pontos o jogador está atualmente
  Projectile projectiles[MAX_PROJECTILES]; // Lista de todos os projéteis
  ListControl projectile_slots;            // Gerencia a lista de projectiles
  Enemy enemies[MAX_ENEMIES];              // Lista de todos os inimigos
  ListControl enemy_slots;                 // Gerencia a lista de inimigos
  Camera2D cam;
  float time_dilation;
  float point_timer;
  int kill_count;
  bool can_spawn_new_enemies;
} Universe;

extern Universe universe;

// Construtor
Universe init_universe();
int get_valid_projectile_id();     // Reserva um espaço na lista de projéteis
int get_valid_enemy_id();          // Reserva um espaço na lista de inimigos
void free_projectile_slot(int id); // Libera um espaço na lista de projéteis
void free_enemy_slot(int id);      // Libera um espaço na lista de inimigos
// Verifica se um slot está vazio
bool is_slot_empty(ListControl *control, int id);
// Insere um projétil na lista de projéteis do universo
void insert_projectile(Projectile projectile);
// Insere um projétil na lista de projéteis do universo
void insert_enemy(Enemy enemy);
// Faz o update de tudo que está contido no universo
void update_universe(float dt);
// Renderiza tudo que há no universo
void draw_universe();
// Retorna um coeficiente (0..1) que diz o quão desacelerado o universo está
float distort_time();
void universe_handle_input();
void victory();
void spawn_enemies();
#endif
