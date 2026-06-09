#include "../include/raylib.h"
#include "modules/player.h"
#include "modules/projectile.h"

#define MAX_BUILDINGS 100

Camera2D cam = {0};

int main(void) {
  // Dimensões da tela
  const int screenWidth = 1200;
  const int screenHeight = 1200;

  InitWindow(screenWidth, screenHeight, "WhiteHole"); // Inicializando janela
  SetTargetFPS(60); // Queremos que rode a 60 fps

  Vector2 mira_position = { 0.0f, 0.0f };

  float dt; // Tempo entre frames
  int id;
  Vector2 inicial_position; // Posição inicial do projectile
  Vector2 mira_position; // Posição da mira do projectile

  Player player = init_player(); // Inicializa o player
  Projectile projectile = new_projectile(PLAYER_ATK, id);

  // Loop de jogo
  while (!WindowShouldClose()) // Fecha no ESC
  {
    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    dt = GetFrameTime();
    inicial_position = player.pos;
    mira_position = GetMousePosition();

    update_player(&player, dt); // Atualiza o moviento do player
    

    //----------------------------------------------------------------------------------
    // Renderização do jogo
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);
    
    DrawCircleV(mira_position, 40, DARKBLUE);
    DrawCircle(player.pos.x, player.pos.y, 50.0f, RED);
    DrawLineEx((Vector2){0,0}, (Vector2){1200,1200}, 5.0f, BLACK);


    BeginMode2D(cam);

    EndMode2D();

    //----------------------------------------------------------------------------------
    // Renderização da UI
    //----------------------------------------------------------------------------------
    DrawText("WHITEHOLE", 600, 10, 40, BLACK);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // Encerrando o programa
  CloseWindow();
  return 0;
}
