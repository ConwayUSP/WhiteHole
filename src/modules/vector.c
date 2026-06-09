#include "vector.h"
#include <math.h>

Vector2 sub_vec(Vector2 A, Vector2 B) {
  return (Vector2){.x = A.x - B.x, .y = A.y - B.y};
}

Vector2 sum_vec(Vector2 A, Vector2 B) {
  return (Vector2){.x = A.x + B.x, .y = A.y + B.y};
}

Vector2 mult_vec(Vector2 V, float a) {
  return (Vector2){.x = V.x * a, .y = V.y * a};
}

Vector2 normalize_vec(Vector2 V) {
  if (is_null_vec(V)) {
    return V;
  }
  float mod = sqrt(pow(V.x, 2) + pow(V.y, 2));
  return (Vector2){.x = V.x / mod, .y = V.y / mod};
}

float mod_vec(Vector2 V) { return sqrt(pow(V.x, 2) + pow(V.y, 2)); }

bool is_null_vec(Vector2 V) { return V.x == 0 && V.y == 0; }

// Encontra o vetor de direção entre um de origem e um de destino
Vector2 direction_vec(Vector2 origin, Vector2 dest) {
  return normalize_vec(sub_vec(dest, origin));
}

// Encontra o ponto em que target vai estar se andar target_move
// E gera um vetor de direção saindo de origin até esse ponto
Vector2 predict_vec(Vector2 origin, Vector2 target, Vector2 target_move) {
  return direction_vec(origin, sum_vec(target, target_move));
}

// Encontra a distância euclidiana entre dois vetores
float distance_vec(Vector2 origin, Vector2 dest) {
  return mod_vec(sub_vec(origin, dest));
}
