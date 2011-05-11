#ifndef HAL_H
#define HAL_H


// DEFINES
#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#endif


// INCLUDES
#include <unistd.h>
#include <sys/syscall.h>
#include <sched.h>

#include <errno.h>
#include "cpu.h"

int start_cpus(void (*fn)(void), int);
int getcpuid();

#endif
