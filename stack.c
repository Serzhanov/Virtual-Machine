#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

static void insert_stack(Stack *s,int index,int value);

extern Stack *new_stack(int size){
  Stack *s=(Stack*)malloc(sizeof(Stack));
  s->buffer=(int*)malloc(sizeof(Stack)*size);
  s->size=size;
  s->index=0;
  return s;
}

extern void free_stack(Stack *stack){
  free(stack->buffer);
  free(stack);
}

extern void set_stack(Stack *s,int index,int value){
  insert_stack(s,index,value);
}

extern void push(Stack *s,int value){
    insert_stack(s,s->index,value);
    s->index+=1;
  

}

extern int get_stack(Stack *s,int index){
  if (index>=s->size){
    fprintf(stderr,"%s\n","error : index >= stack size");
    return 0;
  }
  return s->buffer[index];
}

extern int pop_stack(Stack *s){
  if (s->index==0){
    fprintf(stderr,"%s\n","error : stack.index ==0");
    return 0;
  }
  s->index-=1;
  return s->buffer[s->index];
}


void aff(Stack *s){
  for(int i=0;i<s->index;i++){
    printf("%d\n",s->buffer[i]);
  
  }

}

static void insert_stack(Stack *s,int index,int value){
  if (index>=s->size){
    fprintf(stderr,"%s\n","error : insert_stack");
    exit(0);
  }
  s->buffer[index]=value;
}
 
int size_stack(Stack *s){
  return s->index;
}