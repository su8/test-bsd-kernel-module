#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/kthread.h>

static unsigned int quit = 0U;
static struct proc *mainproc = NULL;

static void main_thread(void *arg) {
  while (1) {
    if (1U == quit) {
      break;
    }
  }
  kthread_exit();
}

static void proc_routine(void *arg) {
  struct thread *td = curthread;
  struct proc *p = td->td_proc;
  struct thread *ntd = NULL;
  kthread_add(main_thread, NULL, p, &ntd, 0, 0, "kthread");
  kproc_exit(0);
}

static int EventHandler(struct module *inModule, int inEvent, void *inArg) {
  switch (inEvent) {
    case MOD_LOAD: {
      kproc_create(proc_routine, NULL, &mainproc, 0, 0, "proc list looper");
    }
    break;
  case MOD_UNLOAD:
    quit = 1U;
    break;
  default:
    break;
  }
  return 0;
}

static moduledata_t moduleData = {
  "hello_world_kmod",     // Module Name
  EventHandler,           // Event handler function name
  NULL                    // Extra data
};

DECLARE_MODULE(hello_world_kmod, moduleData, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
