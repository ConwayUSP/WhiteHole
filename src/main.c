#include "../include/raylib.h"
#include "modules/assetstore.h"
#include "modules/enemy.h"
#include "modules/universe.h"
#include "modules/vector.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BUILDINGS 100

void draw_ui();
void draw_pause();
void draw_fps_monitor();
void draw_menu();
void draw_game_over();
void draw_cursor();
void draw_victory();
void victory();
void draw_blackhole_charge();
void sua_pontuação();

Universe universe;

int main(void) {
  // Dimensões da tela
  const int screenWidth = 1200;
  const int screenHeight = 1200;

  InitWindow(screenWidth, screenHeight, "WhiteHole"); // Inicializando janela
  InitAudioDevice(); // Inicializando o dispositivo de áudio
  SetTargetFPS(240); // Queremos que rode a 60 fps

  // Aleatoriedade
  srand(time(NULL) + 67);

  universe = init_universe();

  if (IsMusicValid(get_scene_audio(&(universe.asset_store)))) {
    Music music = get_scene_audio(&(universe.asset_store));
    SetMusicVolume(music, 0.3);
    PlayMusicStream(music);
  }

  universe.cam.zoom = 3.2f;
  HideCursor();

  float dt; // Tempo entre frames

  // Loop de jogo
  while (!WindowShouldClose()) // Fecha no ESC
  {
    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    dt = GetFrameTime();
    dt *= distort_time();

    update_universe(dt);

    //----------------------------------------------------------------------------------
    // Renderização do jogo
    //----------------------------------------------------------------------------------
    BeginDrawing();
    BeginMode2D(universe.cam);

    ClearBackground(BLUE);
    draw_universe();
    draw_cursor();

    EndMode2D();

    // Renderização da UI
    DrawText("WHITEHOLE", 473, 10, 40, (Color){255, 255, 255, 120});
    DrawText(TextFormat("%d pts", universe.points), 20, 100, 30,
             (Color){100, 255, 200, 255});
    draw_ui();

    EndDrawing();
  }

  // Encerrando o programa
  unload_textures(&universe.asset_store);
  CloseWindow();
  return 0;
}

void draw_cursor() {
  Vector2 mouse_pos = GetMousePosition();
  mouse_pos = sub_vec(GetScreenToWorld2D(mouse_pos, universe.cam),
                      (Vector2){.x = 8, .y = 8});
  DrawTextureEx(universe.asset_store.cursor_sprite, mouse_pos, 0.0f, 2.0f,
                WHITE);
}

void draw_ui() {
  draw_fps_monitor();
  draw_menu();
  draw_game_over();
  draw_blackhole_charge();
  draw_victory();
  draw_pause();
}

void draw_fps_monitor() {
  int FPS = GetFPS();
  Color fps_color = (Color){.r = 100, .g = 255, .b = 150, .a = 200};
  if (FPS < 50) {
    fps_color = (Color){.r = 255, .g = 255, .b = 150, .a = 200};
  } else if (FPS < 30) {
    fps_color = (Color){.r = 255, .g = 100, .b = 100, .a = 200};
  }
  char fps_text[8];
  sprintf(fps_text, "%d fps", FPS);
  DrawText(fps_text, 1100, 10, 20, fps_color);
}

void draw_menu() {
  if (universe.context == MENU) {
    bool blink = (int)(GetTime() * 2) % 2;
    DrawText("APERTE ESPAÇO PARA JOGAR", 360, 700, 30,
             blink ? (Color){255, 221, 158, 255} : (Color){255, 240, 220, 255});
  }
}

void draw_game_over() {
  if (universe.context == GAME_OVER) {
    DrawText("VOCE FOI", 500, 213, 40, (Color){102, 182, 255, 200});
    DrawText("AMERICANIZADO", 174, 300, 100, (Color){252, 8, 32, 180});
    sua_pontuação();
    DrawText("aperte espaço para tentar de novo...", 313, 700, 30,
             (Color){255, 255, 255, 120});
  }
}

void draw_blackhole_charge() {
  Rectangle bg = {20, 20, 265, 60};
  DrawRectangleLinesEx(bg, 3, (Color){255, 255, 255, 255});
  for (int i = 0; i < fmin(universe.player.black_hole_charge, 10); i++) {
    int x = 30 + 25 * i;
    int y = 30;
    int width = 20;
    int height = 40;
    Color color = {225 + 3 * i, 245 - 22 * i, 50 + 10 * i, 255};
    DrawRectangle(x, y, width, height, color);
  }
  if (universe.player.black_hole_charge > 10) {
    DrawRectangle(307, 30, 15, 39, (Color){255, 70, 100, 255}); // Vertical
    DrawRectangle(295, 42, 39, 15, (Color){255, 70, 100, 255}); // Horizontal
  }
}
void sua_pontuação() {
  DrawText(TextFormat("SUA PONTUAÇÃO: %d pts", universe.points), 414, 560, 30,
           (Color){100, 255, 200, 255});
}

void draw_victory() {
  if (universe.context == VICTORY) {
    DrawText("VITORIA", 461, 400, 60, GREEN);
    DrawText("voce expulsou os bilionarios da sua casa!", 167, 300, 40, GREEN);
    sua_pontuação();
    bool blink = (int)(GetTime() * 2) % 2;
    DrawText("APERTE ESPAÇO PARA JOGAR", 360, 700, 30,
             blink ? (Color){255, 221, 158, 255} : (Color){255, 240, 220, 255});
  }
}

void draw_pause() {
  if (universe.context == PAUSE) {
    DrawRectangle(300, 300, 200, 600, (Color){255, 255, 255, 160});
    DrawRectangle(700, 300, 200, 600, (Color){255, 255, 255, 160});
  }
}
