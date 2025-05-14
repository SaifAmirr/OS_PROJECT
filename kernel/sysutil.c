#include "types.h"
#include "riscv.h"
#include "defs.h"

uint64
extern kbd_int_count;
extern int syscall_count;

uint64
sys_kbdint(void){
  return kbd_int_count;
}

uint64
sys_countsyscall(void){
  return syscall_count;
}
