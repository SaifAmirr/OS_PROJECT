#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"

uint64
extern kbd_int_count;
extern int syscall_count;
static uint64 seed = 1;

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
  seed = (1664525 * seed + 1013904223);
    return seed;
}
