#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(){

  printf("range unsigned char 0 to %d\n",UCHAR_MAX);
  printf("range unsigned int 0 to %d\n",UINT_MAX);
  printf("range unsigned short 0 to %d\n",USHRT_MAX);
  printf("range unsigned long 0 to %lu\n",ULONG_MAX);

printf("range signed char %d to %d\n", SCHAR_MIN,SCHAR_MAX);
  printf("range signed int %d to %d\n", INT_MIN,INT_MAX);
  printf("range signed short %d to %d\n",SHRT_MIN,SHRT_MAX);
  printf("range signed long %ld to %ld\n",LONG_MIN,LONG_MAX);


  printf("range float %f to %f\n",FLT_MIN,FLT_MAX);
  printf("range float exp %f to %f\n",FLT_MIN_EXP,FLT_MAX_EXP);

  printf("range double %f to %f\n",DBL_MIN,DBL_MAX);
  printf("range double exp %f to %f\n",DBL_MIN_EXP,DBL_MAX_EXP);

  return 0;
}
