#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int var_int = 123456;
  char arr_char[] = "Long char array right there ->";
  int *ptr2int = &var_int;
  int **ptr2ptr = &ptr2int;
  int ***ptr2ptr2 = &ptr2ptr;
  pid_t pid = getpid();

  while (1) {
    printf("PID: %d\n\n", pid);
    printf("varint %p = %d\n", &var_int, var_int);
    printf("varchar %p = %s\n", &arr_char, arr_char);
    printf("\nptr2int %p = %p\n", &ptr2int, ptr2int);
    printf("ptr2ptr %p = %p\n", &ptr2ptr, ptr2ptr);
    printf("ptr2ptr2 %p = %p\n", &ptr2ptr2, ptr2ptr2);
    printf("\npress enter to print again...\n");
    printf("\n-------------------------------\n");

    getchar();
  }

  return 0;
}
