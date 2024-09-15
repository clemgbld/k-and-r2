#include <stdio.h>

void printHistogram(int n){
for(int i = 0; i < n;i++){
    printf("-");
    if((i + 1) == n){
    printf("\n");
    }
  } 
}

int main(){
 int c;
 int n = 0;
  while ((c = getchar()) != EOF) {
    if(c == ' ' || c == '\t' || c == '\n'){
      printHistogram(n);
      n = 0;
    }else{
      n++;
    }
  }
}
