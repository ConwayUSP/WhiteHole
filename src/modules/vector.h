#ifndef VECTOR_H
#define VECTOR_H

#include "../../include/raylib.h"
#include <math.h>

Vector2 sub_vec(Vector2 A, Vector2 B){
	return {.x = A.x - B.x, .y = A.y - B.y};
}

Vector2 sum_vec(Vector2 A, Vector2 B){
	return {.x = A.x + B.x, .y = A.y + B.y};
}

Vector2 normalize_vec(Vector2 V) {
	float mod = sqrt(pow(V.x, 2) + pow(V.y, 2));
	return {.x = V.x / mod, .y = V.y / mod};
}

// Encontra o vetor de direção entre um de origem e um de destino
Vector2 direction_vec(Vector2 origin, Vector2 dest){
	return normalize(sub_vec(dest, origin));
}

// Encontra o ponto em que target vai estar se andar em target_vel por um segundo
// E gera um vetor de direção saindo de origin até esse ponto
Vector2 predict_vec(Vector2 origin, Vector2 target, Vector2 target_vel){
	return vec_direction(sum_vec(target, target_vel), origin);
}

#endif