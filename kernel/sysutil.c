#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"

uint64
extern kbd_int_count;
extern int syscall_count;
static unsigned long int next = 1;

uint64
sys_kbdint(void){
  return kbd_int_count;
}

uint64
sys_countsyscall(void){
  return syscall_count;
}

uint64
sys_random(void){
  next = next * 1103515245 + 12345;
  return (uint64)(next/65536) % 32768;
}
