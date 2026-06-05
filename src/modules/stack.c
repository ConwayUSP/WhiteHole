#include "stack.h"
#include <stdlib.h>

#define EMPTY -999 // Tecnicamente não é o certo a se fazer, mas tá dboas

Stack new_stack(int stack_size) {
  int *s = malloc(stack_size * sizeof(int));
  Stack stack = {.stack = s, .top = 0, .max = stack_size};
  return stack;
}

void free_stack(Stack *stack) { free(stack->stack); }

void push(Stack *stack, int val) {
  if (stack->top >= stack->max)
    return;
  stack->top += 1;
  stack->stack[stack->top] = val;
}

int pop(Stack *stack) {
  if (stack->top <= 0)
    return EMPTY;
  int res = stack->stack[stack->top];
  stack->top -= 1;
  return res;
}

void fillZeroToMax(Stack *stack) {
  for (int i = 0; i < stack->max; i++)
    stack->stack[i] = i;
}
