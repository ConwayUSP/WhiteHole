#include "../include/raylib.h"
#include "modules/player.h"
#include "modules/universe.h"

#define MAX_BUILDINGS 100

Camera2D cam = {0};
Universe universe;

int main(void) {
  // Dimensões da tela
  const int screenWidth = 1200;
  const int screenHeight = 1200;

  InitWindow(screenWidth, screenHeight, "WhiteHole"); // Inicializando janela
  SetTargetFPS(60); // Queremos que rode a 60 fps

  universe = init_universe();
  float dt; // Tempo entre frames

  Player player = init_player();

  // Loop de jogo
  while (!WindowShouldClose()) // Fecha no ESC
  {
    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    dt = GetFrameTime();

    update_player(&player, dt);
    update_projectiles(dt);
    //----------------------------------------------------------------------------------
    // Renderização do jogo
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawCircle(player.pos.x, player.pos.y, 50.0f, RED);
    DrawLineEx((Vector2){0,0}, (Vector2){1200,1200}, 5.0f, BLACK);
    draw_projectiles();
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
