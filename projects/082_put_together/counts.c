#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  counts_t *counts = malloc(sizeof(*counts));
  counts->sizeunkn = 0;
  counts->sizestr = 0;
  counts->str_array = NULL;
  return counts;
}
void addCount(counts_t * c, const char * name) {

  int inout_identifier = 1;
  if (name == NULL){
    c->sizeunkn++;
    }
  else{
      for (size_t i=0;i<c->sizestr;i++){
      if (strcmp(c->str_array[i]->string,name)==0){
        c->str_array[i]->count_str++ ;
        inout_identifier = 0;
        break;
    }
    }

    if (inout_identifier==1){
      c->str_array = realloc(c->str_array,(1+c->sizestr)*sizeof(*c->str_array));
      
      c->str_array[c->sizestr] = malloc(sizeof(*c->str_array[c->sizestr]));
      c->str_array[c->sizestr]->string = malloc((strlen(name)+1)*sizeof(*c->str_array[c->sizestr]->string));
      strcpy(c->str_array[c->sizestr]->string,name);
      c->str_array[c->sizestr]->count_str = 1;
      c->sizestr++ ;
    }
  }

}

void printCounts(counts_t * c, FILE * outFile) {
  for(size_t i = 0;i<c->sizestr;i++){
    fprintf(outFile,"%s: %d\n",c->str_array[i]->string,c->str_array[i]->count_str);
  }
  if (c->sizeunkn != 0){
    fprintf(outFile,"<unknown>: %d\n",c->sizeunkn);
  }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0;i<c->sizestr;i++){
    free(c->str_array[i]->string);
    free(c->str_array[i]);
  }
  free(c->str_array);
  free(c);
}

