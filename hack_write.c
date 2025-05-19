#include <libmem/libmem.h>
#include <stdio.h>

int main() {
  int int_to_write;
  lm_pid_t pid;
  lm_process_t proc;
  lm_address_t varint_addr;

  printf("enter the pid: ");
  scanf("%d", &pid);
  printf("enter the varint address: ");
  scanf("%lx", &varint_addr);
  printf("enter the value: ");
  scanf("%d", &int_to_write);

  // get process
  if(LM_GetProcessEx(pid, &proc) != LM_TRUE) {
    fprintf(stderr, "failed to attach to pid: %d\n", pid);
    return 1;
  }

  // write to varint
  LM_WriteMemoryEx(&proc, varint_addr, (lm_bytearray_t)&int_to_write, sizeof(int_to_write));

  printf("\noverwritten successfully!\n");

  return 0;
}
