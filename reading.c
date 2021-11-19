#ifndef READING_H_
#define READING_H_
#endif
#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#include "stack.h"
#include <ctype.h>
#include <string.h>
#define SIZE_OF_STACK 10000
#define INSTRUCTION_NUM 19

enum {
  PUSH,
  POP,
  ADD,
  SUB,
  MUL,
  DIV,
  JMP,
  LT,//<
  GT,//>
  EQ,//=
  NE,//!=
  STORE,
  LOAD,
  CALL,//JUMP TO THE FUNCTION AND PLACE IN THE STACK THE VALUE OF RETURN
  RETURN,//TAKES THE  VALUE OF RETURN AND GETTING BACK TO THE ADRESS IN THE STACK
  LABEL,
  COMMENT,
  HLT,
  JSTTOPASS,
};

const char *operating_list[INSTRUCTION_NUM]={
  [PUSH]="PUSH",
  [POP]="POP",
  [ADD]="ADD",
  [MUL]="MUL",
  [DIV]="DIV",
  [SUB]="SUB",
  [JMP]="JMP",
  [LT]="LT",
  [GT]="GT",
  [EQ]="EQ",
  [NE]="NE",
  [STORE]="STORE",
  [LOAD]="LOAD",
  [CALL]="CALL",
  [RETURN]="RETURN",
  [LABEL]="LABEL",
  [COMMENT]="@",
  [HLT]="HLT",
  
};

int isSpace(char ch){
  if (ch=='\0'|| isspace(ch)){
    return 1;
  }
  return 0;
}


char *readcode(char *line,u_int8_t *oper){
  char *ptr=line;
  
  while(isspace(*ptr)){
    ++ptr;
  }
  line=ptr;
  while(!isspace(*ptr)){
    ptr++;
  }
  *ptr='\0';
  *oper=JSTTOPASS;
  for(int i=0;i<INSTRUCTION_NUM;i++){
    if(strcmp(line,operating_list[i])==0){
       *oper=i;
      break;
    }
  }
  switch(*oper){
    case JSTTOPASS:
    case POP:
    case COMMENT:
    case RETURN:
    case HLT:
    case ADD:
    case SUB:
    case MUL:
    case DIV:
      return line;
    default: ;
  }
  ptr++;
  while (isspace(*ptr)==1){
    ptr++;
  }//space passing
  line =ptr;
  while(isSpace(*ptr)==0){
    ptr++;
  }
  *ptr='\0';
  return line;
}

u_int32_t join_8bits_to32(u_int8_t *bytes){
  u_int32_t number;
  for(u_int8_t *ptr=bytes;ptr<bytes+4;ptr++){
    number=(number<<8) | *ptr;
  }
  return number;
}
void split_32bits_to8bits(u_int32_t num,u_int8_t *bytes){
  for (int i=0;i<4;i++){
    bytes[i]=(u_int8_t)(num>>(24-i*8));
  }
}
int strnull(char *str){
  while(isSpace(*str)){
    str++;
  }
  if(*str=='\0'){
    return 1;
  }
  return 0;
}





int reading_exc(FILE *input){
  fseek(input,0,SEEK_END);
  int size=ftell(input);
  Stack *stack=new_stack(SIZE_OF_STACK);
  fseek(input,0,SEEK_SET);
  int value=0;
  u_int8_t oper;
  while(!feof(input) && ftell(input)!=size){
    fscanf(input,"%c",&oper);
    switch(oper){
      case PUSH:{
        u_int8_t bytes[4];
        fscanf(input,"%c%c%c%c",&bytes[0],&bytes[1],&bytes[2],&bytes[3]);
        u_int32_t number=join_8bits_to32(bytes);
        push(stack,number);
      }
      break;
      case POP:{
        int number =pop_stack(stack);
        value=number;
      }
      break;
      case ADD: case SUB: case MUL: case DIV:{
        int first=pop_stack(stack);
        int second=pop_stack(stack);
        switch(oper){
          case ADD:
            first+=second;
            break;
          case SUB:
              first-=second;
            break;
          case MUL:
            first*=second;
            break;
          case DIV:
            first/=second;
            break;
          default:
            printf("error of operator +-/*\n") ;
      }
      push(stack,first);
    }
    break;
    case JMP:{
        u_int8_t bytes[4];
        fscanf(input,"%c%c%c%c",&bytes[0],&bytes[1],&bytes[2],&bytes[3]);
        u_int32_t number=join_8bits_to32(bytes);
        fseek(input,number,SEEK_SET);
    }
    break;
    case LT:case GT: case EQ:case NE:{
      u_int8_t bytes[4];
      fscanf(input,"%c%c%c%c",&bytes[0],&bytes[1],&bytes[2],&bytes[3]);
      u_int32_t index=join_8bits_to32(bytes);
      int first=pop_stack(stack);
      int second=pop_stack(stack);
      switch(oper){
          case LT:
            if(first<second){
              fseek(input,index,SEEK_SET);
            }
          break;
          case GT:
              
              if(first>second){
              fseek(input,index,SEEK_SET);
            }
          
          break;
          case EQ:
            if(first==second){
              fseek(input,index,SEEK_SET);
            }
          
          break;
          case NE:
            if(first!=second){
              fseek(input,index,SEEK_SET);
            }
          break;
          default: ;
        }
      }
      break;
      case STORE:{
        u_int32_t index1,index2;
        u_int8_t bytes[8];
        fscanf(input,"%c%c%c%c%c%c%c%c",&bytes[0],&bytes[1],&bytes[2],&bytes[3],
                                        &bytes[4],&bytes[5],&bytes[6],&bytes[7]);
        index1=join_8bits_to32(bytes);
        index2=join_8bits_to32(bytes+4);
        if((int)index1<0){
          index1=size_stack(stack)+index1;
        }
        if((int)index2<0){
          index2=size_stack(stack)+index2;
        }
        set_stack(stack,index1,get_stack(stack,index2));
      }
      break;    
      case LOAD:{
        u_int8_t bytes[4];
        fscanf(input,"%c%c%c%c",&bytes[0],&bytes[1],&bytes[2],&bytes[3]);
        u_int32_t index=join_8bits_to32(bytes);
        
        if ((int)index<0){
          index=size_stack(stack)+index;
        }
        push(stack,get_stack(stack,index));
      }
      break;
      case CALL:{ 
        u_int8_t bytes[4];
        fscanf(input,"%c%c%c%c",&bytes[0],&bytes[1],&bytes[2],&bytes[3]);
        u_int32_t indexs=join_8bits_to32(bytes);
        int curr_pos=ftell(input);
        push(stack,curr_pos);
        fseek(input,indexs ,SEEK_SET);
      }
      break;
      case RETURN:{
        int index=pop_stack(stack);
        fseek(input,index,SEEK_SET);
      }
      break;
      case HLT:
        goto close;
      default:
        printf("error: the operator hasnt been recognized\n");
        
    }
  }
  close:
  free_stack(stack);
  if(value!=0){
    return value;
  }
  
  return value;
}

int reading_src(FILE *output,FILE *input){
  ht_t *ht=ht_create();
  char buffer[BUFSIZ]={0};
  int line_index=0;
  int error_catcher=0;
  int current_position=0;
  char str[256];
  char *line;
  u_int8_t oper;
  while(fgets(buffer,BUFSIZ,input)!=NULL){
    line_index++;
    line=readcode(buffer,&oper);
    if (((oper==JSTTOPASS)&&strnull(line))|| oper==COMMENT){
      continue;
    }
    if (oper==JSTTOPASS){
      error_catcher=1;
      fprintf(stderr,"syntax error : line %d\n",line_index);
      continue;
    }//oper value is  1 byte and it`s argument value is 4 bytes in the machine code of 32bits
    switch(oper){
      case PUSH:
      case JMP:
      case LT:
      case GT:
      case EQ:
      case NE:
      case LOAD:
      case CALL:
        current_position+=5;
        break;
      case POP:
      case ADD:
      case SUB:
      case MUL:
      case DIV:
      case RETURN:
      case HLT://oper w/o argumets
        current_position+=1;
        break;
      case STORE://oper with 2 arguments by 4 bytes and  the its value 1 byte
        current_position+=9;
        break;
      case LABEL:
        sprintf(str,"%d",current_position);
        ht_set(ht,line,str);
        break;
      default:;
    }
  }
  
  if(error_catcher==1){
    ht_delete(ht);
    return 1;
  } 
  //take postion back to 0
  fseek(input,0,SEEK_SET);
  //re reading
  while (fgets(buffer,BUFSIZ,input)!=NULL){
    line=readcode(buffer,&oper);
    printf("line is %s\n",line);
    switch(oper){
      case PUSH:{
        u_int32_t number=atoi(line);
        // write bytes
        u_int8_t bytes[4];
        split_32bits_to8bits(number,bytes);
        fprintf(output,"%c%c%c%c%c",oper,bytes[0],bytes[1],bytes[2],bytes[3]);}
        break;
      case ADD:case SUB:case MUL:case DIV:case POP: case RETURN: case HLT:
        fprintf(output,"%c",oper);
        break;
      case JMP: case CALL:case LT:
      case GT:
      case NE:
      case EQ:{
        u_int32_t index;
        int cellule_index=ht_get(ht,line);
        index=(u_int32_t) cellule_index;
        u_int8_t bytes[4];
        split_32bits_to8bits(index,bytes);
        fprintf(output,"%c%c%c%c%c",oper,bytes[0],bytes[1],bytes[2],bytes[3]);
        /*
          store $0 $1 ->store in position 0 the value of position 1
          store $-1 $-2 ->store in position -1 the value of position -2
        
        */}
        break;
      case STORE:{
        char *arg= line +strlen(line)+1;//ignoring the symbole
        
        while(isspace(*arg)==1){
          arg++;
        }
        char *ptr=arg;
        while(!isspace(*ptr)==0){
          ptr++;
        }
        *ptr='\0';
        u_int32_t index1=0;
        if(line[1]=='-'){
          index1=-atoi(line+2);
        }
        else{
          index1=atoi(line+1);
        }
        u_int32_t index2=0;
        if(arg[1]=='-'){
          index2 =-(atoi(arg+2));
        }
        else{
          index2=atoi(arg+1);
        }
        u_int8_t bytes[8];
        split_32bits_to8bits(index1,bytes);
        split_32bits_to8bits(index2,bytes+4);
        fprintf(output,"%c%c%c%c%c%c%c%c%c",oper,bytes[0],bytes[1],bytes[2],bytes[3],bytes[4],bytes[5],bytes[6],bytes[7]);
        break;}
      /*
      load $0 ->load the value in position $0 (in stack)
      load $-1 ->load the value in position $-1 (in stack)
      */
      case LOAD:{
        u_int32_t index1=0;
        if(line[1]=='-'){
          index1=-atoi(line+2);
        }
        else{
          index1=atoi(line+1);
        }
        u_int8_t bytes[4];
        split_32bits_to8bits(index1,bytes);
        fprintf(output,"%c%c%c%c%c",oper,bytes[0],bytes[1],bytes[2],bytes[3]);
      }  
    }
  }
  ht_delete(ht);
  return 0;
}


