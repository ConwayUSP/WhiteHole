#include "listcontrol.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

ListControl new_list_control(int list_size) {
  int *s = malloc(list_size * sizeof(int));
  bool *l = malloc(list_size * sizeof(bool));
  ListControl list_control = {
      .free_stack = s, .top = 0, .max = list_size, .used_slots = l};
  return list_control;
}

void free_list_control(ListControl *list_control) {
  free(list_control->free_stack);
  free(list_control->used_slots);
}

void set_slot_as_empty(ListControl *list_control, int idx) {
  if (list_control->top >= list_control->max && !list_control->used_slots[idx])
    return;
  list_control->top += 1;
  list_control->free_stack[list_control->top] = idx;
  list_control->used_slots[idx] = false;
}

int get_empty_slot(ListControl *list_control) {
  if (list_control->top <= 0)
    return NULL_SLOT;
  int res = list_control->free_stack[list_control->top];
  list_control->top -= 1;
  list_control->used_slots[res] = true;
  return res;
}

void set_all_empty(ListControl *list_control) {
  memset(list_control->free_stack, 0, list_control->max * sizeof(int));
  memset(list_control->used_slots, 1, list_control->max * sizeof(bool));
  list_control->top = 0;
  for (int i = list_control->max - 1; i >= 0; i--)
    set_slot_as_empty(list_control, i);
}
