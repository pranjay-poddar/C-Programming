#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  //WRITE ME!
  int count = 0;
  while (*str != '\0'){
    str++;
    count++;
  }
  str -= count;
  if (count > 1){
  char dum_str[count+1];
  //char * dum = str
  for (int j=0; j < count; j++){
    dum_str[count-j-1]= str[j];
  }
  dum_str[count]='\0';
  for (int cc = 0; cc < count ; cc++){
    str[cc] = dum_str[cc];
  }
  //  str = dum_str;
  //  printf("\n%d\n",count);
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
