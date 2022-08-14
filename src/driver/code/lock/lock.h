#include "type.h"

#ifdef NEED_LOCK
#define SPINLOCK()	spin_lock()
#define SPINUNLOCK()	spin_unlock()
#else
#define SPINLOCK()
#define SPINUNLOCK()
#endif

void spin_lock();
void spin_unlock();
