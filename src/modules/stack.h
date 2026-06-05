#ifndef STACK_H
#define STACK_H

// Um stack (LIFO)
typedef struct {
  int *stack;
  int top;
  int max;
} Stack;

// Funções de manipulação de stack
void push(Stack *stack, int val);
int pop(Stack *stack);
void fillZeroToMax(Stack *stack);

#endif
