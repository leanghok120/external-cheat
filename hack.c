#include <libmem/libmem.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
  int int_read = 0;
  int *ptr2int_read;
  int ptr2int_read2;
  // dont forget to change the addr and pid to the ones u get in the dummy program
  lm_address_t var_int_addr = 0x7fff916b4d60;
  lm_address_t ptr2int_addr = 0x7fff916b4d68;
  lm_pid_t pid = 15391;
  lm_process_t proc;

  if(LM_GetProcessEx(pid, &proc) != LM_TRUE) {
    fprintf(stderr, "failed to attach to pid: %d\n", pid); 
    return 1;
  }

  // var_int
  if(LM_ReadMemoryEx(&proc, var_int_addr, (lm_byte_t*)&int_read, sizeof(int_read)) == 0) {
    fprintf(stderr, "failed to read address: 0x%lx\n", var_int_addr); 
    return 1;
  }
  printf("int_read = %d\n", int_read);

  // ptr2int
  if(LM_ReadMemoryEx(&proc, ptr2int_addr, (lm_byte_t*)&ptr2int_read, sizeof(ptr2int_addr)) == 0) {
    fprintf(stderr, "failed to read address: 0x%lx\n", ptr2int_addr); 
    return 1;
  }
  if(LM_ReadMemoryEx(&proc, (lm_address_t)ptr2int_read, (lm_byte_t*)&ptr2int_read2, sizeof(ptr2int_read)) == 0) {
    fprintf(stderr, "failed to read address: 0x%lx\n", ptr2int_addr); 
    return 1;
  }
  printf("ptr2int = %d\n", ptr2int_read2);

  printf("press enter to quit...\n");
  getchar();

  return 0;
}
