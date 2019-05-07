
#include <stdarg.h>
#include "common.h"


// Safe implementation of sprintf. buffer will be allocated by the function
// and must be freed by the caller.
// Returns the string length excluding the terminating zero char!
int safe_sprintf(char **buf, const char *format, ...)
{
	va_list arguments;
	va_start(arguments, format);
	const int len = vsnprintf(NULL, 0, format, arguments);
	va_end(arguments);
	if (*buf) {
		free(*buf);
		*buf = NULL;
	}
	if (!(*buf = malloc((len + 1) * sizeof(char)))) {
		*buf = NULL;
		return -1;
	}
	va_start(arguments, format);
	vsnprintf(*buf, (size_t)(len + 1), format, arguments);
	va_end(arguments);
	return len;
}
