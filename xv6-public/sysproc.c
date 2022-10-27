#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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


int //added by Mary and Ollie
sys_mprotect(void){
  void *addr;
  int len;
   
  //char *a = (char*)PGROUNDDOWN((uint)addr);
  if (argptr(0, (char**)&addr, sizeof(void*)) || (argint(1, &len) <= 0)){//get args
    return -1;
  }
  else if ((uint) addr % PGSIZE != 0 || len <= 0)
	  return -1;
  int success = protect(addr, len);
  return success;
}

int //added by Mary and Ollie
sys_munprotect(void){
  void *addr;
  int len;

  //char *a = (char*)PGROUNDDOWN((uint)addr);
  if (argptr(0, (char**)&addr, sizeof(void*)) || (argint(1, &len) <= 0)){//get args
    return -1;
  }
  else if ((uint) addr % PGSIZE != 0 || len <= 0)
          return -1;
  int success = unprotect(addr, len);
  return success;
}
