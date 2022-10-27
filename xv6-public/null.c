//####################################################
//Mary and Ollie
//This function dereferences a null variable
//####################################################
#include <stdio.h>
#include <stdlib.h>

int main(){
  int *variable = NULL;
  int new = *variable;
  printf("%d", new);
  return new;
}
//###################################################
//End of null program
//###################################################
