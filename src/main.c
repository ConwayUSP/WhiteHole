#include "../include/raylib.h"
#include "modules/enemy.h"
#include "modules/player.h"
#include "modules/projectile.h"
#include "modules/universe.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BUILDINGS 100

void draw_fps_monitor();

Universe universe;

int main(void) {
  // Dimensões da tela
  const int screenWidth = 1200;
  const int screenHeight = 1200;

  InitWindow(screenWidth, screenHeight, "WhiteHole"); // Inicializando janela
  SetTargetFPS(240); // Queremos que rode a 60 fps

  // Aleatoriedade
  srand(time(NULL));

  universe = init_universe();
  universe.cam.zoom = 3.2f;

  float dt;        // Tempo entre frames
  float timer = 0; // Contador de um segundo para spawn

  // Loop de jogo
  while (!WindowShouldClose()) // Fecha no ESC
  {
    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    dt = GetFrameTime();
    dt *= distort_time();
    timer += dt;

    // Spawna um novo inimigo a cada 2 segundos
    if (timer >= 2.0f) {
      timer -= 2.0f;
      new_enemy(rand() % 3, (Vector2){rand() % 400, 0});
    }

    update_universe(dt);

    //----------------------------------------------------------------------------------
    // Renderização do jogo
    //----------------------------------------------------------------------------------
    BeginDrawing();
    BeginMode2D(universe.cam);

    ClearBackground(WHITE);
    draw_universe();

    EndMode2D();

    // Renderização da UI
    DrawText("WHITEHOLE", 500, 10, 40, WHITE);
    draw_fps_monitor();

    EndDrawing();
  }

  // Encerrando o programa
  CloseWindow();
  return 0;
}

void draw_fps_monitor() {
  int FPS = GetFPS();
  Color fps_color = (Color){.r = 100, .g = 255, .b = 150, .a = 255};
  if (FPS < 50) {
    fps_color = (Color){.r = 255, .g = 255, .b = 150, .a = 255};
  } else if (FPS < 30) {
    fps_color = (Color){.r = 255, .g = 100, .b = 100, .a = 255};
  }
  char fps_text[8];
  sprintf(fps_text, "%d fps", FPS);
  DrawText(fps_text, 1100, 10, 20, fps_color);
}
