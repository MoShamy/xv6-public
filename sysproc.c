#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#ifndef HZ
#define HZ 100
#endif

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

//My new system call, so 
int
sys_getppid(void)
{
  return myproc()->parent ? myproc()->parent->pid : 0;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_gettimeofday(void)
{
  struct timeval {
    long tv_sec;
    long tv_usec;
  } tv;
  
  extern uint ticks;
  tv.tv_sec = ticks / HZ;
  tv.tv_usec = (ticks % HZ) * (1000000 / HZ);

  int addr;
  if(argint(0, &addr) < 0)
    return -1;
  
  if(copyout(myproc()->pgdir, (uint)addr, (char *)&tv, sizeof(tv)) < 0)
    return -1;
  
  return 0;
}

int
sys_printptable(void)
{
  return printptable();
}

int
sys_setpriority(void)
{
  
  int pid, priority;
  if(argint(0, &pid) < 0) //adding validation on the inputs before sending them to the function
    return -1;
  if(argint(1, &priority) < 0)
    return -1;

  return setpriority(pid, priority);
}