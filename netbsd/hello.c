#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: hello.c, v 1.1 2018/10/05 su8 Exp $");
#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/kthread.h>
#include <sys/time.h>

static unsigned int quit = 0U;

MODULE(MODULE_CLASS_MISC, hello, NULL);

static void main_thread(void *dummy) {
  while (1) {
    if (1U == quit) {
      break;
    }
  }
  kthread_exit(0);
}

static int hello_modcmd(modcmd_t cmd, void *arg __unused) {
  struct cpu_info *sc;
  switch(cmd) {
    case MODULE_CMD_INIT:
      kthread_create(PRI_SOFTCLOCK, KTHREAD_MPSAFE, NULL, main_thread, sc, NULL, NULL, NULL);
      break;
    case MODULE_CMD_FINI:
      quit = 1U;
      break;
    default:
      break;
  }
  return 0;
}
