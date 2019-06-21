# include <stdlib.h>
# include <stdio.h>
unsigned power (unsigned x, unsigned y);

int main(){
  int n=9;
  unsigned x[]={0, 1, 2, 0, -1, 1.1, 1, 4, -1};
  unsigned y[]={0 ,0 ,1 ,5 , 2, 0, 1.5, 0.5, 3};
  unsigned exp[]={1 , 1, 2, 0, 1, 1, 1, 1, -1};
  for (int i=0; i<n; i++){
    if (power(x[i],y[i]) == exp[i]){
      printf("success\n");
    }
    else{
      printf("Failed at x= %d , y=%d , i =%d\n",x[i],y[i],i);
      exit(EXIT_FAILURE);
    }
  }
  return EXIT_SUCCESS;
}
