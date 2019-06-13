#include<stdlib.h>
#include <stdio.h>
size_t maxSeq(int * array, size_t n);

int main(){
  int test1[] = {1,5,7,8,9,6,3,2,4,5,6,3,2};
  int n1 = 5;
  int L1 = 13;

  int test2[] = {1,2,3,4};
  int n2 = 4;
  int L2= 4;

  int test3[]= {3,2,1};
  int n3 = 0;
  int L3=3;

  int test4[] = {1,1,2,2};
  int n4 = 2;
  int L4 =4;

  int test5[] ={-5,-4,-3};
  int n5 = 3;
  int L5 = 5;

  int test6[]={};
  int n6 = 0;
  int L6 =0;

  int test7[] = {100000000};
  int n7 = 1;
  int L7 = 1;
  
  int nn[] = {n1,n2,n3,n4,n5,n6,n7};
  int * a[] = {test1, test2, test3, test4, test5, test6, test7};
  int L[] = {L1, L2, L3, L4, L5,L6,L7};
  for (int i=0; i<5; i++){
    if (maxSeq(a[i],L[i]) != nn[i]){
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
