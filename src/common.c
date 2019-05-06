
#include "common.h"

// Safe implementation of sprintf. buffer will be allocated by the function
// and must be freed by the caller.
static int safe_sprintf(char **buf, const char *format, ...)
{
	va_list arguments;
	va_start(arguments, format);
	const int len = vsnprintf(NULL, 0, format, arguments) + 1;
	va_end(arguments);
	if (*buf)
		free(*buf);
	if (!(*buf = malloc(len * sizeof(char))))
		return -1;
	va_start(arguments, format);
	vsnprintf(*buf, (size_t)len, format, arguments);
	va_end(arguments);
	return len;
}
