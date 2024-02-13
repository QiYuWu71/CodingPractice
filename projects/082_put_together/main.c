#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t *counts = createCounts();
  char *line = NULL;
  size_t sz;
  ssize_t len = 0;

  FILE *f = fopen(filename,"r");
  while ((len=getline(&line,&sz,f))>=0){
    char *key = malloc((strlen(line))*sizeof(*key));
    strncpy(key,line,strlen(line)-1);
    key[strlen(line)-1] = '\0';
    addCount(counts,lookupValue(kvPairs,key));
    free(key);
    free(line);
    line = NULL;
  }
  free(line);
  if (fclose(f)!=0){
    fprintf(stderr,"File can not close.\n");
    exit(EXIT_FAILURE);
  }
  return counts;
}

int main(int argc, char ** argv) {
  if (argc<3){
    fprintf(stderr,"Usage: count_values kvs list\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t *kvarray = readKVs(argv[1]);
  for (int i=2;i<argc;i++){
    counts_t *counts = countFile(argv[i],kvarray);
    char *outputname = computeOutputFileName(argv[i]);
    FILE *f = fopen(outputname,"w");
    if (f!=NULL){
      printCounts(counts,f);
    }
    free(outputname);
    freeCounts(counts);
    if (fclose(f)!=0){
      fprintf(stderr,"File can not close.\n");
      exit(EXIT_FAILURE);
    }
}
freeKVs(kvarray);
return EXIT_SUCCESS;
}

  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
 //count from 2 to argc (call the number you count i)

    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)


    //open the file named by outName (call that f)

    //print the counts from c into the FILE f

    //close f

    //free the memory for outName and c
  //free the memory for kv

