// DEFINES
#define _GNU_SOURCE


// INCLUDES

#include <unistd.h>
#include <sys/mman.h>
#include <sched.h>

#include <errno.h>


cpu_set_t *cpusetp;
