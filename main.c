#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "reading.h"

int run_exc(const char *filename){
  FILE *input=fopen(filename,"r");
  if (input==NULL){
    perror("ERROR in opening file\n");
    exit(0);
  }
  int res= reading_exc(input);
  fclose(input);
  return res;

}

int compiling_src(const char *output_file,const char *input_file){
  FILE *input=fopen(input_file,"r");
  if (input==NULL){
    perror("ERROR in opening input file\n");
    exit(0);
  }
  FILE *output=fopen(output_file,"wb");
  if (output==NULL){
    perror("ERROR in opening output file\n");
    exit(0);
  }
  int res=reading_src(output,input);
  fclose(input);
  fclose(output);
  return res;

}



int main(int argc,char **argv){
  printf("First argument is ARM code ,second argument is machine code\n");
  if(argc<2){
    printf("The rights havent been respected ,so programm will use main.vm as 1 arg and main.vme as 2 arg\n");
    compiling_src("main.vme","main.vm");//virtual machine executable/source
    printf("%d\n",run_exc("main.vme"));//resultat
  }
  else{
    compiling_src(argv[2],argv[1]);//virtual machine executable/source
    printf("%d\n",run_exc(argv[2]));//resultat
  }
  return 0;
}
