#include "../include/raylib.h"
#include "modules/enemy.h"
#include "modules/player.h"
#include "modules/universe.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BUILDINGS 100

Camera2D cam = {0};
Universe universe;

int main(void) {
  // Dimensões da tela
  const int screenWidth = 1200;
  const int screenHeight = 1200;

  InitWindow(screenWidth, screenHeight, "WhiteHole"); // Inicializando janela
  SetTargetFPS(60); // Queremos que rode a 60 fps

  // Aleatoriedade
  srand(time(NULL));

  universe = init_universe();

  new_enemy(BILLIONAIRE, (Vector2){0,0});
  new_enemy(BILLIONAIRE, (Vector2){0,600});

  float dt; // Tempo entre frames

  // Loop de jogo
  while (!WindowShouldClose()) // Fecha no ESC
  {
    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    dt = GetFrameTime();

    update_player(&universe.player, dt);
    update_projectiles(dt);
    update_enemies(dt);

    //----------------------------------------------------------------------------------
    // Renderização do jogo
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawCircle(universe.player.pos.x, universe.player.pos.y, 50.0f, RED);
    draw_projectiles();
    draw_enemies();


    BeginMode2D(cam);

    EndMode2D();

    //----------------------------------------------------------------------------------
    // Renderização da UI
    //----------------------------------------------------------------------------------
    DrawText("WHITEHOLE", 500, 10, 40, BLACK);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // Encerrando o programa
  CloseWindow();
  return 0;
}
