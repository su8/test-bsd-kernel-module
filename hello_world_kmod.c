/*
 * Step 1 - Add the four needed libraries to include
 */
#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>

/*
 * Step 2 - Handle the load/unload event
 */
static int EventHandler(struct module *inModule, int inEvent, void *inArg)
{
        // Set return code to 0
        int returnCode = 0;

        switch (inEvent)
        {
          case MOD_LOAD:
                uprintf("Hello, World! \n");
                break;
          case MOD_UNLOAD:
                uprintf("Bye, World! \n");
                break;
          default:
                returnCode = EOPNOTSUPP;
                break;
        }

        return(returnCode);
}

/*
 * Step 3 - Name the module and the event hander function
 *          This is done using a struct of type moduledata_T
 */
static moduledata_t  moduleData = {
        "hello_world_kmod",     // Module Name
        EventHandler,           // Event handler function name
        NULL                    // Extra data
};

/*
 * Step 4 - Declare the module
 *          This is done with the DECLARE_MODULE macro
 */
DECLARE_MODULE(hello_world_kmod, moduleData, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
