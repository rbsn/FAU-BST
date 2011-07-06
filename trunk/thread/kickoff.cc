#include "coroutine.h"
void kickoff(Coroutine *object) {

    object->action();

    while(1) {}

}
