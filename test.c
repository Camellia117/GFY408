#include <stdio.h>

void printBin(int number) {
  if (number == 0) return;
  int temp = number;

  int highestBit = 0;
  for(int i = 31;i >= 0;i--) {
    if((temp >> i) & 1) {
      highestBit = i;
      break;
    }
  }

  for(int i = highestBit;i >= 0;i--){
    printf("%d",(number >> i) & 1);
  }
  printf("\n");
}

int main(){
  int num = -3;
  printBin(num);
}
