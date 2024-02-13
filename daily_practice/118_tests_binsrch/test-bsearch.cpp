#include <assert.h>
#include <cmath>
#include <cstdlib>
#include <ostream>
#include "function.h"

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): 
        remaining(n),
        f(fn),
		mesg(m) {}

  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

};
class RealFunction: public Function<int,int>{
  public:
    virtual int invoke(int arg){return arg;}
};

int binarySearchForZero(Function<int, int> * f, int low, int high);


void check(Function<int,int> * f, int low,int high,int expected_ans, const char * mesg){
  int max_count;
  if (high > low){
    max_count = log2(high-low)+1;
  }
  else{
    max_count = 1;
  }
  CountedIntFn *count_f = new CountedIntFn(max_count,f,mesg);
  int ans = binarySearchForZero(count_f,low,high);
  assert(ans == expected_ans);
}

int main(void){
  RealFunction *func = new RealFunction();
  check(func,-1,4,0,"Case 1 - regular");
  check(func,0,3,0,"Case 2 - zero");
  check(func,1,3,1,"Case 3 - all posi");
  check(func,-3,-1,-2,"Case 4 - all nega");
  check(func,1,2,1,"Case 5");
  check(func,-4,0,-1,"Case 6");
  delete func;
  return EXIT_SUCCESS;
}


