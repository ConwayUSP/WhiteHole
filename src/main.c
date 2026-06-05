#include "../include/raylib.h"

#define MAX_BUILDINGS 100

Camera2D cam = {0};

int main(void) {
  // Dimensões da tela
  const int screenWidth = 1200;
  const int screenHeight = 1200;

  InitWindow(screenWidth, screenHeight, "WhiteHole"); // Inicializando janela
  SetTargetFPS(60); // Queremos que rode a 60 fps

  float dt; // Tempo entre frames

  // Loop de jogo
  while (!WindowShouldClose()) // Fecha no ESC
  {
    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    dt = GetFrameTime();

    //----------------------------------------------------------------------------------
    // Renderização do jogo
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

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
