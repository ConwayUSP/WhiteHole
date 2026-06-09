#ifndef VECTOR_H
#define VECTOR_H

#include "../../include/raylib.h"
#include <math.h>

Vector2 sub_vec(Vector2 A, Vector2 B);
Vector2 sum_vec(Vector2 A, Vector2 B);
Vector2 mult_vec(Vector2 V, float a);
Vector2 normalize_vec(Vector2 V);
float mod_vec(Vector2 V);
bool is_null_vec(Vector2 V);

// Encontra o vetor de direção entre um de origem e um de destino
Vector2 direction_vec(Vector2 origin, Vector2 dest);

// Encontra o ponto em que target vai estar se andar em target_vel por um
// segundo E gera um vetor de direção saindo de origin até esse ponto
Vector2 predict_vec(Vector2 origin, Vector2 target, Vector2 target_vel);

// Encontra a distância euclidiana entre dois vetores
float distance_vec(Vector2 origin, Vector2 dest);

#endif
