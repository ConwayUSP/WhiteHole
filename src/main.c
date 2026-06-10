#include "../include/raylib.h"
#include "modules/enemy.h"
#include "modules/player.h"
#include "modules/projectile.h"
#include "modules/universe.h"
#include "modules/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BUILDINGS 100

void draw_fps_monitor();
void draw_menu();
void draw_cursor(Texture2D cursor_tex);

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
  Texture2D cursor = LoadTexture("assets/cursor/cursor.png");
  HideCursor();

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

    // Spawna um novo inimigo a cada 2 segundos
    if (universe.context == RUNNING) {
      timer += dt;
      if (timer >= 2.0f) {
        timer -= 2.0f;
        new_enemy(rand() % 3, (Vector2){rand() % 375, rand() % 375});
      }
    }

    update_universe(dt);

    //----------------------------------------------------------------------------------
    // Renderização do jogo
    //----------------------------------------------------------------------------------
    BeginDrawing();
    BeginMode2D(universe.cam);

    ClearBackground(BLUE);
    draw_universe();
    draw_cursor(cursor);

    EndMode2D();

    // Renderização da UI
    DrawText("WHITEHOLE", 500, 10, 40, WHITE);
    draw_fps_monitor();
    draw_menu();

    if (universe.context == PAUSE) {
      DrawRectangle(300, 300, 200, 600, (Color){255, 255, 255, 160});
      DrawRectangle(700, 300, 200, 600, (Color){255, 255, 255, 160});
    }

    EndDrawing();
  }

  // Encerrando o programa
  CloseWindow();
  return 0;
}

void draw_cursor(Texture2D cursor_tex) {
  Vector2 mouse_pos = GetMousePosition();
  mouse_pos = sub_vec(GetScreenToWorld2D(mouse_pos, universe.cam),
                      (Vector2){.x = 8, .y = 8});
  DrawTextureEx(cursor_tex, mouse_pos, 0.0f, 2.0f, WHITE);
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
void draw_menu() {
  if (universe.context == MENU) {
    DrawText("APERTE ESPAÇO PARA RODAR", 320, 288, 24, GREEN);
  }
}
