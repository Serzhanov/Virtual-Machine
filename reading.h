#ifndef READING_H_
#define READING_H_
#endif
#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"


int isSpace(char ch);

u_int32_t join_8bits_to32(u_int8_t *bytes);

char *readcode(char *line,u_int8_t *oper);

void split_32bits_to8bits(u_int32_t num,u_int8_t *bytes);

int strnull(char *str);

int run_exc(const char *filename);

int compiling_src(const char *output,const char *input);

extern int reading_src(FILE *output,FILE *input);

int reading_exc(FILE *input);