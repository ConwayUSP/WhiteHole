#ifndef STACK_H
#define STACK_H

// Um stack (LIFO)
typedef struct {
  int *stack;
  int top;
  int max;
} Stack;

// Funções de manipulação de stack
Stack new_stack(int stack_size);  // Cria um novo stack com tamanho qualquer
void free_stack(Stack *stack);    // Libera o stack do nosso stack (!)
void push(Stack *stack, int val); // Adiciona um elemento ao topo do stack
int pop(Stack *stack); // Retorna e remove o elemento no topo do stack
void fill_zero_to_max(Stack *stack); // Preenche o stack com valores [0..max]

#endif
