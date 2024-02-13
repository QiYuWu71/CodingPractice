#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


kvarray_t * readKVs(const char * fname) {
    size_t sz = 0;
    ssize_t len=0;
    char *line = NULL;

    FILE * f = fopen(fname,"r");
    if (f== NULL){
      fprintf(stderr,"Could not open file\n");
      exit(EXIT_FAILURE);
    }

    kvarray_t *kvarray = malloc(sizeof(*kvarray));
    kvarray->pairsize = 0;
    kvarray->pairs = NULL;

    while((len = getline(&line,&sz,f))>=0){
      // leave space for each expansion;
      const char *p = strchr(line,'=');
      const char *end = strchr(line,'\n');

      if (p==NULL||end==NULL){
        fprintf(stderr,"The Line format is not correct\n");
        exit(EXIT_FAILURE);
      }

      // Assign information into the different pairs
      kvpair_t *pair = malloc(sizeof(*pair));
      size_t keysize = p-line+1;
      pair->key = malloc(keysize * sizeof(*pair->key));
      strncpy(pair->key,line,keysize-1);
      pair->key[keysize-1] = '\0';

      size_t valuesize =end-p;
      pair->value = malloc(valuesize * sizeof(*pair->value));
      strncpy(pair->value,p+1,valuesize-1);
      pair->value[valuesize-1] = '\0';

      kvarray->pairs = realloc(kvarray->pairs,(kvarray->pairsize+1)*sizeof(*kvarray->pairs));
      kvarray->pairs[kvarray->pairsize] = pair;
      kvarray->pairsize ++;

      free(line);
      line = NULL;
    }
    free(line);

    if (fclose(f) != 0){
      fprintf(stderr,"Failed to close the input file");
      exit(EXIT_FAILURE);
    }

  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i=0;i<pairs->pairsize;i++){
    free(pairs->pairs[i]->value);
    free(pairs->pairs[i]->key);
    free(pairs->pairs[i]);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (size_t i=0;i<pairs->pairsize;i++){
    printf("key = '%s' value = '%s'\n",pairs->pairs[i]->key,pairs->pairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i<pairs->pairsize;i++){
    if (strcmp(key,pairs->pairs[i]->key)==0){
      return pairs->pairs[i]->value;
    }
  }
  return NULL;
}
