#include "types.h"


uint64
extern kbd_int_count;

uint64
sys_kbdint(void){
  return kbd_int_count;
}
