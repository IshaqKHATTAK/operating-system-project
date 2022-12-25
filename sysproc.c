#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"




uint64
sys_mmap(void)
{
  void *address  = 0;
  int size;
  int prot;
  int flags;
  int fd;

  argaddr(0,address);
  argint(1, &size);
  argint(2,&prot);
  argint(3, &flags);
  argint(4, &fd);

  struct proc *p = 0;
  uint64 cur_max = p->max_mappings;
  uint64 startAddress = PGROUNDDOWN(cur_max - size);

  struct virtual_address *vma = 0;

  for(int i = 0 ; i<100; i++)
  {
    if(p->vma[i].valid == 0)
    {
      vma = &p->vma[i];
      break;
    }
  }

  if(vma)
  {
    vma->valid = 1;
    vma->starting_addr = startAddress;
    vma->ending_addr = cur_max;
    vma->len = size;
    vma->fd = fd;
    vma->prot = prot;
    vma->flag = flags;
    p->max_mappings = startAddress;

  }

  else
  {
    return 0xffffffffffffffff;
  }

  printf("Hello, I am mmap\n");

  return startAddress;





}

uint64
sys_munmap(void)
{
  printf("Hello, I am munmap\n");
  return 0;
}

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
