#include "../include/raylib.h"
#include "modules/enemy.h"
#include "modules/player.h"
#include "modules/projectile.h"
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
  cam.zoom = 3.2f;
  cam.target = (Vector2){.x = 600, .y = 600};

  InitWindow(screenWidth, screenHeight, "WhiteHole"); // Inicializando janela
  SetTargetFPS(60); // Queremos que rode a 60 fps

  // Aleatoriedade
  srand(time(NULL));

  universe = init_universe();

  float dt; // Tempo entre frames
  float timer = 0; // Contador de um segundo para spawn

  // Loop de jogo
  while (!WindowShouldClose()) // Fecha no ESC
  {
    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    dt = GetFrameTime();
    timer += dt;

    // Spawna um novo inimigo a cada 2 segundos
    if(timer >= 2.0f){
      timer -= 2.0f;
      new_enemy(rand() % 3, (Vector2){rand() % 1200, 0});      
    }

    update_universe(dt);

    //----------------------------------------------------------------------------------
    // Renderização do jogo
    //----------------------------------------------------------------------------------
    BeginDrawing();
    BeginMode2D(cam);

    ClearBackground(WHITE);
    draw_universe();

    EndMode2D();

    // Renderização da UI
    DrawText("WHITEHOLE", 500, 10, 40, BLACK);

    EndDrawing();
  }

  // Encerrando o programa
  CloseWindow();
  return 0;
}
