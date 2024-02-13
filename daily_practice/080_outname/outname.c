#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  const char * filefix =".counts";
  size_t namesize = strlen(inputName)+strlen(filefix)+2; 
  char * outputname = malloc(namesize*sizeof(*outputname));
// question
  strncpy(outputname,inputName,strlen(inputName)+1);
  strncat(outputname,filefix,strlen(filefix));

  return outputname;

}
