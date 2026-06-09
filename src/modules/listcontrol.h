#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define NULL_SLOT -999 // Tecnicamente não é o certo a se fazer, mas tá dboas
// Um stack (LIFO)
typedef struct {
  int *free_stack;  // índices livres da lista sendo controladas
  int top;          // topo do stack de índices livres
  int max;          // capacidade máxima do stack de índices livres
  bool *used_slots; // coloca true nos índices ocupados e false nos vazios
} ListControl;

// Funções de manipulação de list_control
ListControl new_list_control(
    int list_size); // Cria um novo ListControl com tamanho qualquer
void free_list_control(ListControl *list_control); // Libera a memória dinâmica
                                                   // do nosso ListControl (!)
void set_slot_as_empty(ListControl *list_control,
                       int idx); // Marca um slot como estando vazio
int get_empty_slot(ListControl *list_control); // Retorna o índice de um slot
                                               // vazio e marca ele como usado
void set_all_empty(
    ListControl *list_control); // Marca todos os slots da lista como vazios

#endif
