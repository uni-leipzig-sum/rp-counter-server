#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "redpitaya/rp.h"


// Safe implementation of sprintf. buffer will be allocated by the function
// and must be freed by the caller.
static int safe_sprintf(char **buf, const char *format, ...);


#endif /* COMMON_H */
