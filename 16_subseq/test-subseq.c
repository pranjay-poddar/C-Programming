#include<stdlib.h>
#include <stdio.h>
size_t maxSeq(int * array, size_t n);

int main(){
  int test1[] = {0,0,0,10,0,0,0};
  int n1 = 2;
  int L1 = 7;

  int test2[] = {-5,0,-2,-1};
  int n2 = 2;
  int L2= 4;

  

  int test3[]= {3,2,1,0};
  int n3 = 1;
  int L3= 4;

  int test4[] = {0,1,1,2,2};
  int n4 = 2;
  int L4 =5;

  int test5[] ={-5,-4,-3,0,1,2};
  int n5 = 6;
  int L5 = 6;

  int test6[]={};
  int n6 = 0;
  int L6 =0;
 
  int test7[] = {1};
  int n7 = 1;
  int L7 = 1;
  
  int test8[] = {1,2,0,1,2,-5,10,100,150};
  int n8 = 4;
  int L8 = 9;

  int test9[] = {-4,-1,0,1,7,10,5,0,1,3,4,5,7,8};
  int n9 = 7;
  int L9 = 14;

  int test10[]={1,2,3,4,3,2,0,3,4,5,6,7,8,3,2,5,6,7};
  int n10 = 7;
  int L10 = 18;
  
  int nn[] = {n1,n2,n3,n4,n5,n6,n7,n8,n9, n10};
  int * a[] = {test1, test2, test3, test4, test5, test6, test7,test8,test9, test10};
  int L[] = {L1, L2, L3, L4, L5,L6,L7,L8,L9, L10};
  
  for (int i=0; i<10; i++){
    if (maxSeq(a[i],L[i]) != nn[i]){
      printf("problem found in\n");
      for (int ii =0; ii < L[ii]; ii++){
	int * dumArray = a[i]; 
	printf("%d ",dumArray[ii]);
      }
      printf("\n");
      printf ("the funciton output is %lu\n",maxSeq(a[i],L[i]));
      return EXIT_FAILURE;
    }
    else{
      printf("Congratulations\n");
    }
  }
  return EXIT_SUCCESS;
}
