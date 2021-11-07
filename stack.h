#ifndef _STACK_H_
#define _STACK_H_
#endif
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
  int val;
  int *buffer;
  int size;
  int index;
}Stack;

extern Stack *new_stack(int size);

extern void free_stack(Stack *stack);

extern void set_stack(Stack *s,int index,int value);

extern void push(Stack *s,int value);

extern int get_stack(Stack *s,int index);

extern int pop_stack(Stack *s);


extern int size_stack(Stack *s);

void aff(Stack *s);