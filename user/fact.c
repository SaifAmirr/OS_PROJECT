#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{

  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: factorial of a given number \n");
    exit(0);
  }

  if(argc != 2) {
    printf("Factorial can only be done on one parameter \n");
    exit(0);
  }

  char *input = argv[1];

  if(input[0] == '-')
  {
    printf("Can not do factorial on negative numbers \n");
    exit(0);
  }


  int num = atoi(argv[1]);
  int ans = 1;

  if(num != (int)num)
  {
    printf("Can not do factorial on floating numbers");
    exit(0);
  }

  if(num==0 || num==1)
  {
    ans = 1;
  }


  for(int i = 1; i<=num; i++)
  {
    ans *= i;
  }

  printf("The factorial of %d is %d \n", num, ans);
  exit(0);
}
