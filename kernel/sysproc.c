#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "datetime.h"
#include "memlayout.h"

extern struct proc proc[NPROC];

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_getppid(void)
{
  if(myproc()->parent!=0){
    return myproc()->parent->pid;
  }
  printf("no parent found\n");
  return -1;
}

uint64
sys_getptable(void)
{
  int n;
  uint64 buf;

  argint(0, &n);      // get the first argument (nproc)
  argaddr(1, &buf);   // get the second argument (char *buffer)

  return getptable(n, (char *)buf);
}

uint64
read_mtime(void) {
  return *(volatile uint64 *)CLINT_MTIME_VADDR;
}


// Helper: days in a month considering leap years
static int days_in_month(int year, int month) {
  static const int days_per_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  if (month != 2)
    return days_per_month[month - 1];
  // Leap year check
  if ((year % 400) == 0 || ((year % 4) == 0 && (year % 100) != 0))
    return 29;
  return 28;
}




void unix_to_rtc(uint64 unix_time, struct datetime *r) {
  int days = unix_time / 86400;
  int seconds = unix_time % 86400;

  int year = 1970;
  while (1) {
    int days_this_year = (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) ? 366 : 365;
    if (days < days_this_year)
      break;
    days -= days_this_year;
    year++;
  }

  int month = 1;
  while (1) {
    int dim = days_in_month(year, month);
    if (days < dim)
      break;
    days -= dim;
    month++;
  }

  r->year = year;
  r->month = month;
  r->day = days + 1;

  r->hour = seconds / 3600;
  r->minute = (seconds % 3600) / 60;
  r->second = seconds % 60;
}

extern uint ticks;

uint64
sys_datetime(void)
{
  uint64 user_dst;  // pointer to user struct
  argaddr(0, &user_dst);

  uint curr = BOOT_EPOCH + (ticks / 100);




  struct datetime dt;
  unix_to_rtc(curr, &dt);

  printf("Kernel datetime: %d-%d-%d %d:%d:%d\n",
         dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);

  if (copyout(myproc()->pagetable, user_dst, (char *)&dt, sizeof(dt)) < 0) {
    printf("copyout failed\n");
    return -1;
  }

  return 0;
}

extern void print_averages(void);

uint64
sys_print_averages(void)
{
  print_averages();
  return 0;
}

uint64
sys_setpriority(void)
{
  int pid, new_prio;
  argint(0, &pid);
  argint(1, &new_prio);

  struct proc *p;
  for(p = proc; p < &proc[NPROC]; p++) {
    if(p->pid == pid) {
      acquire(&p->lock);
      p->priority = new_prio;
      release(&p->lock);
      return 0;
    }
  }
  return -1; // PID not found
}
