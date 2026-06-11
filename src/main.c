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

void draw_fps_monitor();
void draw_menu();
void draw_game_over();
void draw_cursor();
void victory();

Universe universe;

int main(void) {
  // Dimensões da tela
  const int screenWidth = 1200;
  const int screenHeight = 1200;

  InitWindow(screenWidth, screenHeight, "WhiteHole"); // Inicializando janela
  InitAudioDevice(); // Inicializando o dispositivo de áudio
  SetTargetFPS(240); // Queremos que rode a 60 fps

  // Aleatoriedade
  srand(time(NULL));

  universe = init_universe();

  if(IsMusicValid(get_scene_audio(&(universe.asset_store)))){
    Music music = get_scene_audio(&(universe.asset_store));
    SetMusicVolume(music, 0.3);
    PlayMusicStream(music);
  }

  universe.cam.zoom = 3.2f;
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
    draw_cursor();

    EndMode2D();

    // Renderização da UI
    DrawText("WHITEHOLE", 500, 10, 40, (Color){255, 255, 255, 120});
    DrawText(TextFormat("%d pts", universe.points), 50, 950, 30, GREEN);
    draw_fps_monitor();
    draw_menu();
    draw_game_over();

    if (universe.context == PAUSE) {
      DrawRectangle(300, 300, 200, 600, (Color){255, 255, 255, 160});
      DrawRectangle(700, 300, 200, 600, (Color){255, 255, 255, 160});
    }
    if(universe.context == VICTORY){
    DrawText("VITORIA",500,400,60,GREEN);
    DrawText("voce expulsou os bilionarios da sua casa!", 600, 300,40, GREEN);
    
    }

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
    DrawText("APERTE ESPAÇO PARA JOGAR", 380, 700, 30,
             blink ? (Color){255, 221, 158, 255} : (Color){255, 240, 220, 255});
  }
}

void draw_game_over() {
  if (universe.context == GAME_OVER) {
    DrawText("VOCE FOI", 500, 100, 40, (Color){102, 122, 255, 200});
    DrawText("AMERICANIZADO", 300, 200, 100, (Color){252, 8, 32, 180});
    DrawText("aperte espaço para tentar de novo...", 400, 700, 30,
             (Color){255, 255, 255, 120});
  }
}

