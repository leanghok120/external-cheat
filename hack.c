#include <libmem/libmem.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
  int int_read = 0;
  int *ptr2int_read;
  int ptr2int_read2;
  lm_address_t var_int_addr;
  lm_address_t ptr2int_addr;
  lm_address_t ptr2ptr2_addr;
  lm_pid_t pid;
  lm_process_t proc;

  printf("enter the pid: ");
  scanf("%d", &pid);
  printf("enter the varint address: ");
  scanf("%lx", &var_int_addr);
  printf("enter the ptr2int address: ");
  scanf("%lx", &ptr2int_addr);
  printf("enter the ptr2ptr2 address: ");
  scanf("%lx", &ptr2ptr2_addr);
  // remove newline char after scanf
  getchar();

  if(LM_GetProcessEx(pid, &proc) != LM_TRUE) {
    fprintf(stderr, "failed to attach to pid: %d\n", pid); 
    return 1;
  }

  // var_int
  if(LM_ReadMemoryEx(&proc, var_int_addr, (lm_byte_t*)&int_read, sizeof(int_read)) == 0) {
    fprintf(stderr, "failed to read address: 0x%lx\n", var_int_addr); 
    return 1;
  }
  printf("\nint_read = %d\n", int_read);

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

  // pointer chain
  lm_address_t offsets[] = {0, 0, 0};
  lm_size_t noffsets = sizeof(offsets) / sizeof(offsets[0]);
  lm_address_t ptr2ptr2ptr = LM_DeepPointerEx(&proc, ptr2ptr2_addr, offsets, noffsets);
  int ptr2ptr2ptr_read = 0;
  if(LM_ReadMemoryEx(&proc, ptr2ptr2ptr, (lm_byte_t*)&ptr2ptr2ptr_read, sizeof(ptr2ptr2_addr)) == 0) {
    fprintf(stderr, "failed to read address: 0x%lx\n", ptr2ptr2_addr); 
    return 1;
  }
  printf("ptr2ptr2 = %d\n", ptr2ptr2ptr_read);

  printf("\npress enter to quit...\n");
  getchar();

  return 0;
}
